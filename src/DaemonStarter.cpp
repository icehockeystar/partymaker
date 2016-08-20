//
// Created by roman.tuchin on 14.08.16.
//
#include <iostream>
#include "partymaker/DaemonApplication.h"

using std::cout;

int main(int argc, char** argv) {
  DaemonApplication app;
  return app.run(argc, argv);
}
