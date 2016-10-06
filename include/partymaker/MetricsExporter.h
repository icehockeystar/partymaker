//
// Copyright 2016 Roman Tuchin
//
#ifndef INCLUDE_PARTYMAKER_METRICSEXPORTER_H_
#define INCLUDE_PARTYMAKER_METRICSEXPORTER_H_

#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

class MetricsExporter {
 public:
  MetricsExporter();
  void export_measurement(const string& measurement,
                          const unordered_map<string, string>& tags,
                          const unordered_map<string, float>& fields);
 private:
  static const char METRICS_SERVER_URL[];
  string prepare_metrics_request_body(const string& measurement,
                                  const unordered_map<string, string>& tags,
                                  const unordered_map<string, float>& fields);
  void create_db(const string& db_name);
};

#endif  //  INCLUDE_PARTYMAKER_METRICSEXPORTER_H_
