//
// Created by roman.tuchin on 15.08.16.
//

#ifndef INCLUDE_PARTYMAKER_DOWNLOADMEASURETASK_H_
#define INCLUDE_PARTYMAKER_DOWNLOADMEASURETASK_H_

#include <string>
#include "Poco/Util/TimerTask.h"
#include "Poco/Util/Application.h"
#include "partymaker/MetricsExporter.h"

using Poco::Util::TimerTask;
using Poco::Util::Application;
using std::string;

class DownloadMeasureTask {
 private:
  MetricsExporter metrics_exporter;
  void test_download_speed();
  void export_wifi_speed_metric(float speed_Mbps);
  void test_upload_speed();
 public:
  DownloadMeasureTask();
  static const char WIFI_SPEED_MEASUREMENT[];
  void callback(TimerTask &task);
};


#endif  //  INCLUDE_PARTYMAKER_DOWNLOADMEASURETASK_H_
