#ifndef WEATHERSTATION_RESTCOMPONENT_H
#define WEATHERSTATION_RESTCOMPONENT_H

#include <memory>
#include <tulz/util/noncopyable.h>

class Application;
class RESTServer;

class RESTComponent : tulz::noncopyable {
public:
    virtual ~RESTComponent() = default;

    virtual void enableFor(RESTServer &server) = 0;
};

using RESTComponentPtr = std::unique_ptr<RESTComponent>;

#endif //WEATHERSTATION_RESTCOMPONENT_H
