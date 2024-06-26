//
// Copyright 2016 Roman Tuchin
//
#include <iostream>
#include <string>
#include <vector>
#include "Poco/Util/TimerTaskAdapter.h"
#include "Poco/Logger.h"
#include "Poco/Process.h"
#include "partymaker/DaemonApplication.h"
#include "partymaker/DownloadMeasureTask.h"




using Poco::Util::Application;
using Poco::Thread;
using std::string;
using Poco::Util::TimerTask;
using Poco::Util::TimerTaskAdapter;
using Poco::Logger;
using Poco::Util::ServerApplication;
using Poco::Process;
using Poco::TimerCallback;

DaemonApplication::DaemonApplication() {
  logger().information("ctor calling...");
}

void DaemonApplication::initialize(Application &self) {
  loadConfiguration("/data/partymaker/conf/partymaker.properties");
  // log config is read only with next line
  ServerApplication::initialize(self);
  logger().information("init sheduled tasks");
  DownloadMeasureTask task;
  TimerCallback<DownloadMeasureTask> timer_callback(
          task, &DownloadMeasureTask::callback);
  download_timer_.start(timer_callback);
}

int DaemonApplication::main(const std::vector<std::string> &args) {
  waitForTerminationRequest();
  return Application::EXIT_OK;
}

DaemonApplication::~DaemonApplication() {
  logger().information("dtor calling...");
}
