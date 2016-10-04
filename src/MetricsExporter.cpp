//
// Copyright 2016 Roman Tuchin
//
#include <string>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <exception>
#include "Poco/Net/HTTPRequest.h"
#include "partymaker/MetricsExporter.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Util/Application.h"
#include "Poco/StreamCopier.h"


using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using std::ostringstream;
using std::copy;
using std::pair;
using Poco::Util::Application;
using std::exception;

const char MetricsExporter::METRICS_SERVER_URL[] =
        "localhost";

void MetricsExporter::export_measurement(const string &measurement,
                                 const unordered_map<string, string> &tags,
                                 const unordered_map<string, float> &fields) {
  Application &application = Application::instance();

  const string &metrics_server = application.config().getString(
            "metrics.server", METRICS_SERVER_URL);
  HTTPClientSession metrics_client(metrics_server, 8086);
  application.logger().information(metrics_server);
  HTTPRequest insert_metric_request(HTTPRequest::HTTP_POST, "/write?db=mydb");
  string body = prepare_metrics_request_body(measurement, tags, fields);
  // it's very important for influxdb server to set content length
  insert_metric_request.setContentLength(body.length());
  try {
    metrics_client.sendRequest(insert_metric_request) << body;
    HTTPResponse insert_metric_response;
    metrics_client.receiveResponse(insert_metric_response);
    if (insert_metric_response.getStatus() !=
            HTTPResponse::HTTPStatus::HTTP_NO_CONTENT) {
      throw std::runtime_error("Insert metric response hasn't returned 204");
    }
  } catch (exception &e) {
    application.logger().warning("metric server is not avalable");
    application.logger().warning(e.what());
  }
}

string MetricsExporter::prepare_metrics_request_body(const string &measurement,
                                 const unordered_map<string, string> &tags,
                                 const unordered_map<string, float> &fields) {
  std::ostringstream string_stream;
  string_stream << measurement;

  if (!tags.empty()) {
    string_stream << ",";
    for (auto it = tags.begin(); it != tags.end();) {
      string_stream << it->first << "=" << it->second;
      ++it;
      if (it != tags.end()) {
        string_stream << ",";
      }
    }
  }

  if (!fields.empty()) {
    string_stream << " ";
    for (auto it = fields.begin(); it != fields.end();) {
      string_stream << it->first << "=" << std::to_string(it->second);
      ++it;
      if (it != fields.end()) {
        string_stream << ",";
      }
    }
  }

  return string_stream.str();
}
