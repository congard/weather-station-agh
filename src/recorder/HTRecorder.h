#ifndef WEATHERSTATION_HTRECORDER_H
#define WEATHERSTATION_HTRECORDER_H

#include "core/Runner.h"
#include "sensor/DHT22Sensor.h"
#include "HTRecord.h"

#include <tulz/container/RingBuffer.h>
#include <mutex>

/**
 * Stands for Humidity Temperature Recorder
 */
class HTRecorder : public Runner {
public:
    using RecordBuffer = tulz::RingBuffer<HTRecord, true>;

public:
    explicit HTRecorder(DHT22Sensor &sensor);

    void setMaxRecordCount(int count);
    void setPeriod(int sec);

    int getMaxRecordCount() const;
    int getPeriod() const;

    template<typename R>
    void readRecords(R &&reader) const {
        static_assert(std::is_invocable_r_v<void, R, const RecordBuffer&>);
        std::lock_guard locker(m_mutex);
        reader(m_records);
    }

protected:
    [[noreturn]] void onRun() override;

private:
    DHT22Sensor &m_sensor;

    RecordBuffer m_records;
    int m_periodSec;

    // required for record buffer to prevent
    // the situation while during reading
    // writing occurs
    mutable std::mutex m_mutex;
};

#endif //WEATHERSTATION_HTRECORDER_H
