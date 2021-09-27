//
// Created by 凌宇 on 2021/9/20.
//

#include <log/MemoryLogComponent.h>

namespace kakakv {
    namespace log {
        /**
 * 获取下一条日志的索引
 * @return
 */
        unsigned long long MemoryLogComponent::getNextIndex() {

        }

        /**
         * 获取当前的commitIndex
         * @return
         */
        unsigned long long MemoryLogComponent::getCommitIndex() {

        }

        /**
         * 判断对象的lastLogIndex和lastLogTerm是否比自己新
         * @param lastLogIndex
         * @param lastLogTerm
         * @return
         */
        bool MemoryLogComponent::isNewerThan(unsigned long long lastLogIndex, unsigned long long lastLogTerm) {

        }

        /**
         * 增加一条NO-OP日志
         * @param term
         * @return
         */
        std::shared_ptr<NoOpLogEntry> MemoryLogComponent::appendEntry(unsigned long long term) {

        }

        /**
         * 增加一条普通日志
         * @param term
         * @param command
         * @param length
         * @return
         */
        std::shared_ptr<GeneralLogEntry>
        MemoryLogComponent::appendEntry(unsigned long long term, char *command, unsigned long long length) {

        }

        /**
         * 追加来自Leader的日志条目
         * @param prevLogIndex
         * @param prevLogTerm
         * @return
         */
        bool
        MemoryLogComponent::appendEntriesFromLeader(unsigned long long prevLogIndex, unsigned long long prevLogTerm,
                                                    std::vector<std::shared_ptr<log::LogEntry>>) {

        }

        /**
         * 推进commitIndex
         * @param newCommitIndex
         * @param currentTerm
         */
        void MemoryLogComponent::advanceCommitIndex(unsigned long long newCommitIndex, unsigned long long currentTerm) {

        }

        /**
         * 关闭
         */
        void MemoryLogComponent::close() {

        }
    }
}