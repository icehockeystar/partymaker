//
// Copyright 2016 Roman Tuchin
//
#include <istream>
#include <iostream>
#include <fstream>
#include "partymaker/DownloadMeasureTask.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/StreamCopier.h"

using Poco::Thread;
using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using std::istream;
using std::ofstream;
using Poco::StreamCopier;

void DownloadMeasureTask::callback(TimerTask &task) {
  Application::instance().logger()
    .information("callback " + Thread::current()->name());
  HTTPClientSession download_client("www.speedtestx.de");
  const string file_name = "data_1mb.test";
  HTTPRequest download_request(HTTPRequest::HTTP_GET,
                               "/testfiles/" + file_name);
  download_client.sendRequest(download_request);
  HTTPResponse download_response;
  std::istream& download_stream =
          download_client.receiveResponse(download_response);
  Application::instance().logger().information(
          "Got status " + std::to_string(download_response.getStatus()));
  ofstream downloaded_file_stream;
  downloaded_file_stream.open(file_name);
  StreamCopier::copyStream(download_stream, downloaded_file_stream);
  downloaded_file_stream.close();
  Application::instance().logger().information("Download finished");
  // TODO(roman_tuchin) check md5 checksum
}
