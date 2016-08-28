//
// Copyright 2016 Roman Tuchin
//
#include <gtest/gtest.h>
#include <string>
#include "partymaker/MetricsExporter.h"

TEST(MetricsExporter, WriteSomeMetric) {
  MetricsExporter metrics_exporter;
  unordered_map<string, string> tags;
  unordered_map<string, int64_t> fields;
  metrics_exporter.export_measurement(MetricsExporter::WIFI_SPEED_MEASUREMENT,
                                      tags, fields);
}