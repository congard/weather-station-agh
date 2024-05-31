#ifndef WEATHERSTATION_APPLICATIONCOMPONENT_H
#define WEATHERSTATION_APPLICATIONCOMPONENT_H

#include "rest/RESTComponent.h"

class ApplicationComponent : public RESTComponent {
public:
    ApplicationComponent();

    void enableFor(RESTServer &server) override;

private:
    static void getUptime(Request &req);
    static void getTime(Request &req);
    static void setTime(Request &req);
};

#endif //WEATHERSTATION_APPLICATIONCOMPONENT_H
