//
// Created by 凌宇 on 2021/9/20.
//

#ifndef KAKAKV_APPENDENTRIES_H
#define KAKAKV_APPENDENTRIES_H

#include <message/Message.h>
#include <cluster/NodeId.h>
#include <ostream>
#include <vector>

namespace kakakv {

    namespace log{
        class LogEntry;
    }

    namespace message {
        class AppendEntries:public Message{
            friend std::ostream & operator<<(std::ostream & cout,const AppendEntries & appendEntries);
        public:
            AppendEntries(const unsigned long long term,cluster::NodeId leaderId): Message(term), leaderId(leaderId){
            }
            cluster::NodeId leaderId;//Leader的节点Id
            unsigned long long prevLogIndex;//entryList中第一条日志的前一条日志的索引
            unsigned long long prevLogTerm;//entryList中第一条日志的前一条日志的Term
            std::vector<std::shared_ptr<log::LogEntry>> entryList;//待复制的日志条目
            unsigned long long leaderCommitIndex;//Leader的commitIndex
        };
        std::ostream & operator<<(std::ostream & cout,const AppendEntries & appendEntries);
    }
}


#endif //KAKAKV_APPENDENTRIES_H
