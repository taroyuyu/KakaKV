//
// Created by 凌宇 on 2021/9/20.
//

#ifndef KAKAKV_REQUESTVOTERESPONSE_H
#define KAKAKV_REQUESTVOTERESPONSE_H

#include <message/Message.h>
#include <ostream>
#include <cluster/NodeId.h>
namespace kakakv{
    namespace message{
        class RequestVoteResponse:public Message{
            friend std::ostream & operator<<(std::ostream & cout,const RequestVoteResponse & response);
        public:
            RequestVoteResponse(const unsigned long long term,const cluster::NodeId voterId,const bool voteGranted):
                    Message(term),voterId(voterId),voteGranted(voteGranted){

            }
            const cluster::NodeId voterId;//投票者Id
            const bool voteGranted;//是否选择投票
        };
        std::ostream & operator<<(std::ostream & cout,const RequestVoteResponse & response);
    }
}


#endif //KAKAKV_REQUESTVOTERESPONSE_H
