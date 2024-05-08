#include "TimedEvents.h"
#include <iomanip>

namespace seneca {

    TimedEvents::TimedEvents() : numRecords(0) {}

    void TimedEvents::startClock() {
        startTime = std::chrono::steady_clock::now();
    }

    void TimedEvents::stopClock() {
        endTime = std::chrono::steady_clock::now();
    }

    void TimedEvents::addEvent(const char* eventName) {
        if (numRecords < MAX_EVENTS) {
            events[numRecords].name = eventName;
            events[numRecords].units = "nanoseconds";
            events[numRecords].duration = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime);
            numRecords++;
        }
    }

    std::ostream& operator<<(std::ostream& os, const TimedEvents& te) {
        os << "--------------------------\n";
        os << "Execution Times:\n";
        os << "--------------------------\n";

        for (size_t i = 0; i < te.numRecords; ++i) {
            os << std::setw(23) << te.events[i].name << std::setw(13) << te.events[i].duration.count()
               << " " << te.events[i].units << '\n';
        }

        os << "--------------------------\n";

        return os;
    }

} // namespace seneca
