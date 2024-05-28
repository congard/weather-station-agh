#ifndef WEATHERSTATION_RESTMODULE_H
#define WEATHERSTATION_RESTMODULE_H

#include "RESTServer.h"

#include <tulz/util/noncopyable.h>

class Application;

/**
 * Starts RESTServer and enables all necessary components
 */
class RESTModule : tulz::noncopyable {
public:
    explicit RESTModule(Application &application);

    void run();

private:
    RESTServer m_server;
};

#endif //WEATHERSTATION_RESTMODULE_H
