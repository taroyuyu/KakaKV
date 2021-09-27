//
// Created by 凌宇 on 2021/9/20.
//

#ifndef KAKAKV_APPENDENTRIESRESPONSE_H
#define KAKAKV_APPENDENTRIESRESPONSE_H

#include <message/Message.h>
#include <cluster/NodeId.h>
#include <ostream>
namespace kakakv {
    namespace message {
        class AppendEntriesResponse:public Message{
            friend std::ostream & operator<<(std::ostream & cout,const AppendEntriesResponse & response);
        public:
            AppendEntriesResponse(const unsigned long long term,const cluster::NodeId followerId,const bool success):
                    Message(term),followerId(followerId),success(success){
            }
            const cluster::NodeId followerId;//Follower节点Id
            const bool success;//追加是否成功
        };
        std::ostream & operator<<(std::ostream & cout,const AppendEntriesResponse & response);
    }
}


#endif //KAKAKV_APPENDENTRIESRESPONSE_H
