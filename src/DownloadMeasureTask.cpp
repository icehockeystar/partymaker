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

void DownloadMeasureTask::callback(TimerTask &task) {
  Application::instance().logger()
          .information("Measuring download/upload speed...");
  test_download_speed();
  // test_upload_speed();
}

void DownloadMeasureTask::test_download_speed() {
  Application::instance().logger()
          .information("Testing download...");
  HTTPClientSession download_client("www.speedtestx.de");
  const float kDataSizeMb = 50.9;
  const string file_name = "data_50mb.test";
  HTTPRequest download_request(HTTPRequest::HTTP_GET,
                               "/testfiles/" + file_name);
  download_client.sendRequest(download_request);
  HTTPResponse download_response;
  istream& download_stream =
          download_client.receiveResponse(download_response);
  Application::instance().logger().information("Got status "
                       + std::to_string(download_response.getStatus()));
  ofstream downloaded_file_stream;
  downloaded_file_stream.open(file_name);
  Stopwatch stopwatch;
  stopwatch.start();
  StreamCopier::copyStream(download_stream, downloaded_file_stream);
  stopwatch.stop();
  downloaded_file_stream.close();

  float speedMbps = kDataSizeMb * 8 / stopwatch.elapsedSeconds();
  Application::instance().logger()
          .information("Download finished. Downloaded in "
                       + std::to_string(stopwatch.elapsedSeconds())
                       + "s (" + std::to_string(speedMbps) + " Mbps)");
  // TODO(roman_tuchin) check md5 checksum
}

void DownloadMeasureTask::test_upload_speed() {
  Application::instance().logger()
          .information("Testing upload...");
  HTTPClientSession upload_client("www.speedtestx.de");
  const int kDataSizeMb = 50;
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
