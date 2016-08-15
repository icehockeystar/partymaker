//
// Created by roman.tuchin on 14.08.16.
//

#include "partymaker/DaemonApplication.h"

using Poco::Util::Application;

int DaemonApplication::main(const std::vector<std::string> &args) {
  waitForTerminationRequest();
  return Application::EXIT_OK;
}
