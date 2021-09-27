//
// Created by 凌宇 on 2021/9/20.
//

#include <log/NoOpLogEntry.h>

namespace kakakv{
    namespace log{
        std::ostream &operator<<(std::ostream &cout, NoOpLogEntry &entry) {
            cout << "NoOpLogEntry{index=" << entry.index << ",term=" << entry.term << "}";
        }
    }
}