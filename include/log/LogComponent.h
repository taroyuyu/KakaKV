//
// Created by 凌宇 on 2021/9/20.
//
#ifndef KAKAKV_LOGCOMPONENT_H
#define KAKAKV_LOGCOMPONENT_H

#include <log/LogEntrySequence.h>
#include <log/NoOpLogEntry.h>
#include <log/GeneralLogEntry.h>
namespace kakakv {
    namespace log {
    class LogComponent {
    public:
        virtual ~LogComponent() = 0;
        /**
         * 获取下一条日志的索引
         * @return
         */
        virtual unsigned long long getNextIndex() = 0;
        /**
         * 获取当前的commitIndex
         * @return
         */
        virtual unsigned long long getCommitIndex() = 0;
        /**
         * 判断对象的lastLogIndex和lastLogTerm是否比自己新
         * @param lastLogIndex
         * @param lastLogTerm
         * @return
         */
        virtual bool isNewerThan(unsigned long long  lastLogIndex,unsigned long long lastLogTerm) = 0;
        /**
         * 增加一条NO-OP日志
         * @param term
         * @return
         */
        virtual std::shared_ptr<NoOpLogEntry> appendEntry(unsigned long long term) = 0;
        /**
         * 增加一条普通日志
         * @param term
         * @param command
         * @param length
         * @return
         */
        virtual std::shared_ptr<GeneralLogEntry> appendEntry(unsigned long long term,char * command,unsigned long long length) = 0;
        /**
         * 追加来自Leader的日志条目
         * @param prevLogIndex
         * @param prevLogTerm
         * @return
         */
        virtual bool appendEntriesFromLeader(unsigned long long prevLogIndex,unsigned long long prevLogTerm,std::vector<std::shared_ptr<log::LogEntry>>) = 0;
        /**
         * 推进commitIndex
         * @param newCommitIndex
         * @param currentTerm
         */
        virtual void advanceCommitIndex(unsigned long long newCommitIndex,unsigned long long currentTerm) = 0;
        /**
         * 关闭
         */
        virtual void close() = 0;
    protected:
        LogComponent(std::unique_ptr<LogEntrySequence> logEntrySequence):logEntrySequence(std::move(logEntrySequence)){
        };
        std::unique_ptr<LogEntrySequence> logEntrySequence;
    };
    }
}

#endif //KAKAKV_LOGCOMPONENT_H
