//
// Created by 凌宇 on 2021/9/20.
//

#ifndef KAKAKV_NOOPLOGENTRY_H
#define KAKAKV_NOOPLOGENTRY_H

#include <iostream>
#include <log/LogEntry.h>

namespace kakakv {
    namespace log {
        class NoOpLogEntry : public LogEntry {
            friend std::ostream &operator<<(std::ostream &cout, NoOpLogEntry &entry);

        public:
            NoOpLogEntry(int index, int term) : LogEntry(index, term) {
            }
        };

        std::ostream &operator<<(std::ostream &cout, NoOpLogEntry &entry);
    }
}

#endif //KAKAKV_NOOPLOGENTRY_H
