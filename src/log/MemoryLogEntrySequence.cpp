//
// Created by 凌宇 on 2021/9/20.
//

#include <log/MemoryLogEntrySequence.h>

namespace kakakv{
    namespace log{
            std::ostream &operator<<(std::ostream &cout, const MemoryLogEntrySequence &logEntrySequence){
                cout << "MemoryLogEntrySequence{logIndexOffset=" << logEntrySequence.logIndexOffset << ",nextLogIndex="
                     << logEntrySequence.nextLogIndex << ",entryList.size=" << logEntrySequence.entryList.size() << "}";
                return cout;
            }
    }
}