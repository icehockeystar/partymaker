//
// Created by roman.tuchin on 15.08.16.
//

#ifndef INCLUDE_PARTYMAKER_DOWNLOADMEASURETASK_H_
#define INCLUDE_PARTYMAKER_DOWNLOADMEASURETASK_H_

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


#endif  //  INCLUDE_PARTYMAKER_DOWNLOADMEASURETASK_H_
