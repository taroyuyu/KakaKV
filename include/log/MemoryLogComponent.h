//
// Created by 凌宇 on 2021/9/20.
//

#ifndef KAKAKV_MEMORYLOGCOMPONENT_H
#define KAKAKV_MEMORYLOGCOMPONENT_H

#include <log/LogComponent.h>
#include <log/MemoryLogEntrySequence.h>
namespace kakakv {
    namespace log {
        class MemoryLogComponent : public LogComponent {
        public:
            MemoryLogComponent(): LogComponent(std::make_unique<MemoryLogEntrySequence>()){
            }
            /**
             * 获取下一条日志的索引
             * @return
             */
            unsigned long long getNextIndex()override;
            /**
             * 获取当前的commitIndex
             * @return
             */
            unsigned long long getCommitIndex()override;
            /**
             * 判断对象的lastLogIndex和lastLogTerm是否比自己新
             * @param lastLogIndex
             * @param lastLogTerm
             * @return
             */
            bool isNewerThan(unsigned long long  lastLogIndex,unsigned long long lastLogTerm)override;
            /**
             * 增加一条NO-OP日志
             * @param term
             * @return
             */
            std::shared_ptr<NoOpLogEntry> appendEntry(unsigned long long term)override;
            /**
             * 增加一条普通日志
             * @param term
             * @param command
             * @param length
             * @return
             */
            std::shared_ptr<GeneralLogEntry> appendEntry(unsigned long long term,char * command,unsigned long long length)override;
            /**
             * 追加来自Leader的日志条目
             * @param prevLogIndex
             * @param prevLogTerm
             * @return
             */
            bool appendEntriesFromLeader(unsigned long long prevLogIndex,unsigned long long prevLogTerm,std::vector<std::shared_ptr<log::LogEntry>>)override;
            /**
             * 推进commitIndex
             * @param newCommitIndex
             * @param currentTerm
             */
            void advanceCommitIndex(unsigned long long newCommitIndex,unsigned long long currentTerm)override;
            /**
             * 关闭
             */
            void close()override;
        };
    }
}


#endif //KAKAKV_MEMORYLOGCOMPONENT_H
