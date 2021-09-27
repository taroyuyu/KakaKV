//
// Created by 凌宇 on 2021/9/20.
//

#ifndef KAKAKV_LOGENTRYSEQUENCE_H
#define KAKAKV_LOGENTRYSEQUENCE_H

#include <log/LogEntry.h>
#include <memory>
namespace kakakv {
    namespace log {
        class LogEntrySequence {
        public:
            class EmptyLogEntrySequenceException {
            };

            /**
             * 判断日志条目序列是否为空
             * @return
             */
            bool isEmpty() const throw() {
                return this->logIndexOffset == this->nextLogIndex;
            }

            /**
             * 获取日志条目序列中第一条日志条目的索引
             * @return
             */
            unsigned long long getFirstLogIndex() const throw(EmptyLogEntrySequenceException) {
                if (this->isEmpty())
                    throw EmptyLogEntrySequenceException();
                return this->logIndexOffset;
            }

            /**
             * 获取日志条目序列中下一条日志条目的索引
             * @return
             */
            unsigned long long getNextLogIndex() const throw() {
                return this->nextLogIndex;
            }

            bool isLogEntryPresent(unsigned long long index) const throw() {
                return this->logIndexOffset <= index < this->nextLogIndex;
            }

            virtual std::shared_ptr<LogEntry> getEntry(unsigned long long index) const throw() = 0;

            virtual bool append(std::shared_ptr<LogEntry> entry) = 0;

            virtual std::shared_ptr<LogEntry> remove(unsigned long long index) throw() = 0;
            virtual ~LogEntrySequence() {
            }
        protected:
            /**
             * 构造一条空日志条目序列
             * @param logIndexOffset
             */
            LogEntrySequence(unsigned long long logIndexOffset) : logIndexOffset(logIndexOffset),
                                                                  nextLogIndex(logIndexOffset) {
            }

            LogEntrySequence(const LogEntrySequence &) = delete;

            LogEntrySequence &operator=(LogEntrySequence &) = delete;

            unsigned long long logIndexOffset;
            unsigned long long nextLogIndex;
        };
    }
}
#endif //KAKAKV_LOGENTRYSEQUENCE_H
