//
// Created by roman.tuchin on 14.08.16.
//

#ifndef PARTYMAKER_DAEMONAPPLICATION_H
#define PARTYMAKER_DAEMONAPPLICATION_H

#include <string>
#include <vector>
#include "Poco/Util/ServerApplication.h"
#include "Poco/Timer.h"

using Poco::Timer;

class DaemonApplication: public Poco::Util::ServerApplication {
 public:
  DaemonApplication();
  virtual ~DaemonApplication();
 protected:
  int main(const std::vector<std::string> &args) override;
  void initialize(Application &self) override;
 private:
  Timer download_timer_{1000, 150000};
};


#endif //PARTYMAKER_DAEMONAPPLICATION_H
