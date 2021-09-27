//
// Created by 凌宇 on 2021/9/20.
//

#include <log/GeneralLogEntry.h>

namespace kakakv{
    namespace log{
        std::ostream & operator<<(std::ostream &cout, GeneralLogEntry &entry) {
            cout << "GeneralLogEntry{index=" << entry.index << ",term=" << entry.term << "}";
        }
    }
}