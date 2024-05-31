#ifndef WEATHERSTATION_DISPLAY_H
#define WEATHERSTATION_DISPLAY_H

#include "display/renderer/DisplayRenderer.h"
#include "core/Runner.h"

#include <ssd1306.h>
#include <memory>
#include <tulz/util/noncopyable.h>

class Application;

class Display : public Runner, tulz::noncopyable {
public:
    using DisplayRendererPtr = std::unique_ptr<DisplayRenderer>;

    constexpr static auto MinRefreshPeriod = 1000;

public:
    explicit Display(Application &application);

    void setRenderer(DisplayRendererPtr renderer);
    DisplayRenderer* getRenderer() const;

    /**
     * @param ms The refresh period in ms
     */
    void setRefreshPeriod(int ms);

    /**
     * @return The refresh period in ms
     */
    int getRefreshPeriod() const;

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
    int m_refreshPeriod;
};

#endif //WEATHERSTATION_DISPLAY_H
