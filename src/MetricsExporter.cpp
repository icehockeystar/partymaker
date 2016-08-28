//
// Copyright 2016 Roman Tuchin
//
#include <string>
#include <iostream>
#include <Poco/StreamCopier.h>
#include <sstream>
#include <fstream>
#include "Poco/Net/HTTPRequest.h"
#include "partymaker/MetricsExporter.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPResponse.h"

using Poco::Net::HTTPClientSession;
using Poco::Net::HTTPRequest;
using Poco::Net::HTTPResponse;

const char MetricsExporter::WIFI_SPEED_MEASUREMENT[] = "wifi_speed";
const char MetricsExporter::METRICS_SERVER_URL[] =
        "localhost";

void MetricsExporter::export_measurement(const string &measurement,
                                 const unordered_map<string, string> &tags,
                                 const unordered_map<string, int64_t> &fields) {
  HTTPClientSession metrics_client(METRICS_SERVER_URL, 8086);
  HTTPRequest insert_metric_request(HTTPRequest::HTTP_POST, "/write?db=mydb");
  string body = prepare_metrics_request_body(measurement, tags, fields);
  // it's very important for influxdb server to set content length
  insert_metric_request.setContentLength(body.length());
  metrics_client.sendRequest(insert_metric_request) << body;
  HTTPResponse insert_metric_response;
  metrics_client.receiveResponse(insert_metric_response);
  std::cout << std::to_string(insert_metric_response.getStatus());
  if (insert_metric_response.getStatus() !=
          HTTPResponse::HTTPStatus::HTTP_NO_CONTENT) {
    throw std::runtime_error("Insert metric response hasn't returned 204");
  }
}

string MetricsExporter::prepare_metrics_request_body(const string &measurement,
                                 const unordered_map<string, string> &tags,
                                 const unordered_map<string, int64_t> &fields) {
  return "cpu,host=serverA,region=us_east value=1.24";
}
