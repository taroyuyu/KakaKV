//
// Created by 凌宇 on 2021/9/20.
//

#ifndef KAKAKV_REQUESTVOTE_H
#define KAKAKV_REQUESTVOTE_H

#include <message/Message.h>
#include <cluster/NodeId.h>
#include <ostream>
namespace kakakv {
    namespace message {

        class RequestVote:public Message{
            friend std::ostream & operator<<(std::ostream & cout,RequestVote & request);
        public:
            RequestVote(const unsigned long long term,cluster::NodeId candidateId,const unsigned long long  lastLogIndex,const unsigned long long lastLogTerm):
                    Message(term),candidateId(candidateId),lastLogIndex(lastLogIndex),lastLogTerm(lastLogTerm){

            }
            cluster::NodeId candidateId;//候选者Id
            unsigned long long lastLogIndex;//候选者最后一条日志的索引
            unsigned long long lastLogTerm;//候选者最后一条日志的term
        };

        std::ostream & operator<<(std::ostream & cout,RequestVote & request);
    }
}


#endif //KAKAKV_REQUESTVOTE_H
