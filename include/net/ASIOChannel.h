//
// Created by 凌宇 on 2021/9/27.
//

#ifndef KAKAKV_ASIOCHANNEL_H
#define KAKAKV_ASIOCHANNEL_H

#include <net/Channel.h>

namespace kakakv{
    namespace net{
        class ASIOChannel:public Channel{
        public:
            // 发送RequestVote消息
            void writeRequestVote(const std::shared_ptr<message::RequestVote> message)override;
            // 发送RequestVoteResponse消息
            void writeRequestVoteResponse(const std::shared_ptr<message::RequestVoteResponse> message)override;
            // 发送AppendEntries消息
            void writeAppendEntries(const std::shared_ptr<message::AppendEntries> message)override;
            // 发送AppendEntriesResponse消息
            void writeAppendEntriesResponse(const std::shared_ptr<message::AppendEntriesResponse> message)override;
            // 关闭
            void close()override;
        };
    }
}


#endif //KAKAKV_ASIOCHANNEL_H
