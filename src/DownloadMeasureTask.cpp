//
// Copyright 2016 Roman Tuchin
//
#include <istream>
#include <iostream>
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
using Poco::StreamCopier;

void DownloadMeasureTask::callback(TimerTask &task) {
  Application::instance().logger()
    .information("callback " + Thread::current()->name());
  HTTPClientSession download_client("www.speedtestx.de");
  HTTPRequest download_request(HTTPRequest::HTTP_GET, "/testfiles/data_1mb.test");
  download_client.sendRequest(download_request);
  HTTPResponse download_response;
  std::istream& download_stream =
          download_client.receiveResponse(download_response);
  Application::instance().logger().information("Got status " + std::to_string(download_response.getStatus()));
  StreamCopier::copyStream(download_stream, std::cout);
  Application::instance().logger().information("Download finished ");
}
