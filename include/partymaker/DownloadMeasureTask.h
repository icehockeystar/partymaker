//
// Created by roman.tuchin on 15.08.16.
//

#ifndef PARTYMAKER_DOWNLOADMEASURETASK_H
#define PARTYMAKER_DOWNLOADMEASURETASK_H

#include <string>
#include "Poco/Util/TimerTask.h"
#include "Poco/Util/Application.h"

using Poco::Util::TimerTask;
using Poco::Util::Application;
using std::string;

class DownloadMeasureTask {
 private:
  const char* kDownloadHost = "www.speedtestx.de";
  const char* kDownloadResource = "/testfiles/data_256mb.test";
  void test_download_speed();
  void test_upload_speed();
 public:
  void callback(TimerTask &task);
};


#endif  //  PARTYMAKER_DOWNLOADMEASURETASK_H
