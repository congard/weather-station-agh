#ifndef WEATHERSTATION_DHT22SENSORCOMPONENT_H
#define WEATHERSTATION_DHT22SENSORCOMPONENT_H

#include "rest/RESTComponent.h"

class DHT22Sensor;

class DHT22SensorComponent : public RESTComponent {
public:
    explicit DHT22SensorComponent(DHT22Sensor &sensor);

    void enableFor(RESTServer &server) override;

private:
    void get(Request &req) const;
    void post(Request &req);

private:
    DHT22Sensor &m_sensor;
};

#endif //WEATHERSTATION_DHT22SENSORCOMPONENT_H
