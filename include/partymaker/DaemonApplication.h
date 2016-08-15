//
// Created by roman.tuchin on 14.08.16.
//

#ifndef PARTYMAKER_DAEMONAPPLICATION_H
#define PARTYMAKER_DAEMONAPPLICATION_H

#include "Poco/Util/ServerApplication.h"

class DaemonApplication: public Poco::Util::ServerApplication {
protected:
  virtual int main(const std::vector<std::string> &args) override;

};


#endif //PARTYMAKER_DAEMONAPPLICATION_H
