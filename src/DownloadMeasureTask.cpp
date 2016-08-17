//
// Created by roman.tuchin on 15.08.16.
//
#include "partymaker/DownloadMeasureTask.h"

using Poco::Thread;

void DownloadMeasureTask::onTimer(TimerTask &task) {
  Application::instance().logger().information("onTimer " + Thread::current()->name());
}