//
// Created by roman.tuchin on 14.08.16.
//

#include "Poco/Util/TimerTaskAdapter.h"
#include "partymaker/DaemonApplication.h"
#include "partymaker/DownloadMeasureTask.h"
#include "iostream"


using Poco::Util::Application;
using Poco::Thread;
using std::string;
using Poco::Util::TimerTask;
using Poco::Util::TimerTaskAdapter;

DaemonApplication::DaemonApplication() {
  logger().information("ctor calling...");
}

void DaemonApplication::initialize(Application &self) {
  logger().information("init sheduled tasks");
  DownloadMeasureTask task;
  TimerTask::Ptr ptr = new TimerTaskAdapter<DownloadMeasureTask>(task, &DownloadMeasureTask::onTimer);
  download_timer_.schedule(ptr, 1000, 3000);
}

int DaemonApplication::main(const std::vector<std::string> &args) {
  waitForTerminationRequest();
  return Application::EXIT_OK;
}

DaemonApplication::~DaemonApplication() {
  logger().information("dtor calling...");
}