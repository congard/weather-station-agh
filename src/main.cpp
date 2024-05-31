#include "core/Application.h"

extern "C" void app_main() {
    ws::Application app;
    app.exec();
}
