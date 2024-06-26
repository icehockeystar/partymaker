//
// Copyright 2016 Roman Tuchin
//
#include <istream>
#include <ostream>
#include <iostream>
#include <fstream>
#include <string>
#include "partymaker/DownloadMeasureTask.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/StreamCopier.h"
#include "Poco/Stopwatch.h"
#include "Poco/Logger.h"

using Poco::Thread;
using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using std::istream;
using std::ostream;
using std::ofstream;
using std::ifstream;
using Poco::StreamCopier;
using Poco::Stopwatch;
using Poco::Logger;

const char DownloadMeasureTask::WIFI_SPEED_MEASUREMENT[] = "wifi_speed";

DownloadMeasureTask::DownloadMeasureTask() {
  Application::instance().logger()
          .information("DownloadMeasureTask ctor calling...");
}

void DownloadMeasureTask::callback(Timer &timer) {
  Application::instance().logger()
          .information("Measuring download/upload speed...");
  test_download_speed();
  // test_upload_speed();
}

void DownloadMeasureTask::test_download_speed() {
  Logger& logger = Application::instance().logger();
  logger.information("Testing download...");
  HTTPClientSession download_client("www.speedtestx.de");
  const float kDataSizeMb = 50.9;
  const string file_name = "data_50mb.test";
  HTTPRequest download_request(HTTPRequest::HTTP_GET,
                               "/testfiles/" + file_name);
  std::ostream &upload_stream = download_client.sendRequest(download_request);
  logger.debug("Upload stream: bad = %b, fail = %b",
                                         upload_stream.bad(),
                                         upload_stream.fail());
  HTTPResponse download_response;
  istream& download_stream =
          download_client.receiveResponse(download_response);
  logger.debug("Got status "
                       + std::to_string(download_response.getStatus()));
  ofstream downloaded_file_stream;
  // todo файл может не открыться без эксепшона
  downloaded_file_stream.open("/data/partymaker/tmp/" + file_name);
  Stopwatch stopwatch;
  stopwatch.start();
  StreamCopier::copyStream(download_stream, downloaded_file_stream);
  stopwatch.stop();
  downloaded_file_stream.close();
  int elapsed = stopwatch.elapsedSeconds();
  float speed_Mbps;
  try {
    speed_Mbps = kDataSizeMb * 8 / elapsed;
  } catch (std::exception& e) {
    logger.warning("Error during calculating speed: ");
    logger.warning(e.what());
  }

  logger.information("Download finished. Downloaded in "
                       + std::to_string(stopwatch.elapsedSeconds())
                       + "s (" + std::to_string(speed_Mbps) + " Mbps)");
  export_wifi_speed_metric(speed_Mbps);
  // TODO(roman_tuchin) check md5 checksum
}

void DownloadMeasureTask::export_wifi_speed_metric(float speed_Mbps) {
  unordered_map<string, string> wifi_speed_tags_map;
  unordered_map<string, float> wifi_speed_fields_map;
  wifi_speed_tags_map.emplace("room", "детская_спальня");
  wifi_speed_tags_map.emplace("device", "lenovo_laptop");
  wifi_speed_fields_map.emplace("value", speed_Mbps);
  metrics_exporter.export_measurement(WIFI_SPEED_MEASUREMENT,
                                      wifi_speed_tags_map,
                                      wifi_speed_fields_map);
}

void DownloadMeasureTask::test_upload_speed() {
  Application::instance().logger()
          .information("Testing upload...");
  HTTPClientSession upload_client("www.speedtestx.de");
  const string file_name = "data_1mb.test";
  HTTPRequest upload_request(HTTPRequest::HTTP_POST,
                               "/testfiles/" + file_name);
  ifstream file_stream;
  file_stream.open(file_name);
  StreamCopier::copyStream(file_stream,
                           upload_client.sendRequest(upload_request));
  file_stream.close();
  HTTPResponse upload_response;
  upload_client.receiveResponse(upload_response);
  Application::instance()
          .logger().information("Got status "
                                + std::to_string(upload_response.getStatus()));
}
