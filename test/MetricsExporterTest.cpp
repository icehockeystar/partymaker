//
// Copyright 2016 Roman Tuchin
//
#include <gtest/gtest.h>
#include <string>
#include <partymaker/DownloadMeasureTask.h>

TEST(MetricsExporter, WriteSomeMetric) {
  MetricsExporter metrics_exporter;
  unordered_map<string, string> tags;
  tags.emplace("room", "детская_спальня");
  tags.emplace("device", "lenovo_notebook");
  unordered_map<string, float> fields;
  fields.emplace("value", 23.3);
  metrics_exporter.export_measurement(
          DownloadMeasureTask::WIFI_SPEED_MEASUREMENT, tags, fields);
}
