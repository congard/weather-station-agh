#ifndef WEATHERSTATION_DISPLAY_H
#define WEATHERSTATION_DISPLAY_H

#include "display/renderer/DisplayRenderer.h"
#include "core/Runner.h"

#include <ssd1306.h>
#include <memory>

class Application;

class Display : public Runner {
public:
    using DisplayRendererPtr = std::unique_ptr<DisplayRenderer>;

public:
    explicit Display(Application &application);

    Display(const Display&) = delete;
    Display(Display&&) = delete;

    Display& operator=(const Display&) = delete;
    Display& operator=(Display&&) = delete;

    void setRenderer(DisplayRendererPtr renderer);
    DisplayRenderer* getRenderer() const;

    SSD1306_t& getDev();

    Application& getApplication();

protected:
    [[noreturn]] void onRun() override;

private:
    void initDriver();

private:
    Application &m_application;
    DisplayRendererPtr m_renderer;
    SSD1306_t m_dev;
};

#endif //WEATHERSTATION_DISPLAY_H
