#ifndef WEATHERSTATION_HELLOWORLDCOMPONENT_H
#define WEATHERSTATION_HELLOWORLDCOMPONENT_H

#include "RESTComponent.h"

class HelloWorldComponent : public RESTComponent {
public:
    void enableFor(RESTServer &server) override;
};

#endif //WEATHERSTATION_HELLOWORLDCOMPONENT_H
