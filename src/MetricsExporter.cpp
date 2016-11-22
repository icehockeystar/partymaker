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
#include "Poco/URI.h"
#include "Poco/Logger.h"


using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;
using std::ostringstream;
using std::copy;
using std::pair;
using Poco::Util::Application;
using std::exception;
using Poco::URI;
using Poco::Logger;

const char MetricsExporter::METRICS_SERVER_URL[] =
        "localhost";

MetricsExporter::MetricsExporter() {

}

void MetricsExporter::export_measurement(const string &measurement,
                                 const unordered_map<string, string> &tags,
                                 const unordered_map<string, float> &fields) {
  string db_name = "pmdb";
  create_db(db_name);
  string metric_server = Application::instance().config()
          .getString("metrics.server");
  Logger& log = Application::instance().logger();
  HTTPClientSession metrics_client(metric_server, 8086);
  HTTPRequest insert_metric_request(HTTPRequest::HTTP_POST, "/write?db=" +
          db_name);
  string body = prepare_metrics_request_body(measurement, tags, fields);
  // it's very important for influxdb server to set content length
  insert_metric_request.setContentLength(body.length());
  try {
    metrics_client.sendRequest(insert_metric_request) << body;
    HTTPResponse insert_metric_response;
    metrics_client.receiveResponse(insert_metric_response);
    if (insert_metric_response.getStatus() !=
            HTTPResponse::HTTPStatus::HTTP_NO_CONTENT) {
      throw std::runtime_error(std::to_string(
              insert_metric_response.getStatus()));
    }
  } catch (exception &e) {
    log.warning("metric server is not avalable");
    log.warning(e.what());
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

void MetricsExporter::create_db(const string& db_name) {
  string metric_server = Application::instance().config()
          .getString("metrics.server");
  Logger& log = Application::instance().logger();
  HTTPClientSession metrics_client(metric_server, 8086);
  HTTPRequest create_db_request(HTTPRequest::HTTP_POST, "/query");
  string body = "";
  URI::encode("q=CREATE DATABASE " + db_name, "", body);
  create_db_request.setContentType("application/x-www-form-urlencoded");
  create_db_request.setContentLength(body.length());
  try {
    metrics_client.sendRequest(create_db_request) << body;
    HTTPResponse create_db_response;
    metrics_client.receiveResponse(create_db_response);
    log.information("Create db reponse code: " +
                            std::to_string(create_db_response.getStatus()));
    if (create_db_response.getStatus() !=
        HTTPResponse::HTTPStatus::HTTP_OK) {
      throw std::runtime_error("Create db metric response hasn't returned 200");
    }
  } catch (exception &e) {
    log.warning(e.what());
    return;
  }
  log.information("Db was created.");
}
