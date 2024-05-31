#ifndef WEATHERSTATION_HTRECORDERCOMPONENT_H
#define WEATHERSTATION_HTRECORDERCOMPONENT_H

#include "rest/RESTComponent.h"

class HTRecorder;

class HTRecorderComponent : public RESTComponent {
public:
    explicit HTRecorderComponent(HTRecorder &recorder);

    void enableFor(RESTServer &server) override;

private:
    void get(Request &req) const;
    void post(Request &req);
    void getRecords(Request &req) const;

private:
    HTRecorder &m_recorder;
};

#endif //WEATHERSTATION_HTRECORDERCOMPONENT_H
