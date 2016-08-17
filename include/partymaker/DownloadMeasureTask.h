//
// Created by roman.tuchin on 15.08.16.
//

#ifndef PARTYMAKER_DOWNLOADMEASURETASK_H
#define PARTYMAKER_DOWNLOADMEASURETASK_H

#include <Poco/Util/TimerTask.h>
#include <Poco/Util/Application.h>

using Poco::Util::TimerTask;
using Poco::Util::Application;

class DownloadMeasureTask {
public:
  void onTimer(TimerTask& task);
};


#endif //PARTYMAKER_DOWNLOADMEASURETASK_H
