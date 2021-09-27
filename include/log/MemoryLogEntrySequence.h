//
// Created by 凌宇 on 2021/9/20.
//

#ifndef KAKAKV_MEMORYLOGENTRYSEQUENCE_H
#define KAKAKV_MEMORYLOGENTRYSEQUENCE_H

#include <iostream>
#include <vector>
#include <log/LogEntrySequence.h>
namespace kakakv {
    namespace log {
        class MemoryLogEntrySequence : public LogEntrySequence {
            friend std::ostream &operator<<(std::ostream &cout, const MemoryLogEntrySequence &logEntrySequence);

        public:
            /**
             * 创建基于内存的日志条目序列
             * @param logIndexOffset
             */
            MemoryLogEntrySequence(unsigned long long logIndexOffset = 0) : LogEntrySequence(logIndexOffset),
                                                                            commitIndex(logIndexOffset) {

            }

            std::shared_ptr<LogEntry> getEntry(unsigned long long index) const throw() {
                if (!this->isLogEntryPresent(index)) {
                    return nullptr;
                }
                return this->entryList[index - logIndexOffset];
            }

            bool append(std::shared_ptr<LogEntry> entry) {
                if (!entry) {
                    return false;
                }
                if (entry->getIndex() != this->nextLogIndex) {
                    return false;
                }
                this->entryList.push_back(entry);
                this->nextLogIndex++;
            }

            virtual std::shared_ptr<LogEntry> remove(unsigned long long index) throw() {
                if (!this->isLogEntryPresent(index)) {
                    return nullptr;
                }
                auto targetIt = this->entryList.begin();
                for (int i = this->logIndexOffset; i < this->nextLogIndex; ++i, ++targetIt) {
                    auto logEntry = this->entryList[i - logIndexOffset];
                    if (logEntry->getIndex() == index) {
                        break;
                    }
                }
                auto ret = *targetIt;
                this->entryList.erase(targetIt);
                return ret;
            }

            bool commit(unsigned long long index) throw() {
                if (!this->isLogEntryPresent(index)) {
                    return false;
                }
                this->commitIndex = index;
                return true;
            }

            unsigned long long getCommitIndex() const throw() {
                return this->commitIndex;
            }

        private:
            std::vector<std::shared_ptr<LogEntry>> entryList;
            unsigned long long commitIndex;

        };

        std::ostream &operator<<(std::ostream &cout, const MemoryLogEntrySequence &logEntrySequence);
    }
}

#endif //KAKAKV_MEMORYLOGENTRYSEQUENCE_H
