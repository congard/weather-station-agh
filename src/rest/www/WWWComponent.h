#ifndef WEATHERSTATION_WWWCOMPONENT_H
#define WEATHERSTATION_WWWCOMPONENT_H

#include "rest/RESTComponent.h"

namespace ws {
/**
 * Handles non-api endpoints and returns the corresponding files, e.g.
 * <br>GET /index.html
 * <br>GET /index.css
 * <br>GET /scripts/app.js
 * <br>etc. If the file cannot be found, 404 error will be returned.
 * All files will be read from the /www partition.
 */
class WWWComponent : public RESTComponent {
public:
    WWWComponent();

    void enableFor(RESTServer &server) override;

private:
    static void get(Request &req);
};
}

#endif //WEATHERSTATION_WWWCOMPONENT_H
