//
// Created by 凌宇 on 2021/9/27.
//

#include <net/ASIOChannel.h>

namespace kakakv{
    namespace net{
        // 发送RequestVote消息
        void ASIOChannel::writeRequestVote(const std::shared_ptr<message::RequestVote> message){
        }
        // 发送RequestVoteResponse消息
        void ASIOChannel::writeRequestVoteResponse(const std::shared_ptr<message::RequestVoteResponse> message){

        }
        // 发送AppendEntries消息
        void ASIOChannel::writeAppendEntries(const std::shared_ptr<message::AppendEntries> message){

        }
        // 发送AppendEntriesResponse消息
        void ASIOChannel::writeAppendEntriesResponse(const std::shared_ptr<message::AppendEntriesResponse> message){

        }
        // 关闭
        void ASIOChannel::close(){
        }
    }
}