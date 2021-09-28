//
// Created by 凌宇 on 2021/9/27.
//

#ifndef KAKAKV_CHANNEL_H
#define KAKAKV_CHANNEL_H

#include <message/RequestVote.h>
#include <message/RequestVoteResponse.h>
#include <message/AppendEntries.h>
#include <message/AppendEntriesResponse.h>
#include <net/AbstractHandler.h>
#include <net/Decoder.h>
#include <net/Encoder.h>
namespace kakakv {
    namespace net {
        class Channel;
        class Channel {
        public:
            Channel(std::shared_ptr<Decoder> decoder,std::shared_ptr<Encoder> encoder);
            virtual ~Channel() = 0;
            virtual void addHandler(std::shared_ptr<AbstractHandler> handler) = 0;
            virtual void removeHandler(std::shared_ptr<AbstractHandler> handler) = 0;
            // 发送RequestVote消息
            virtual void writeRequestVote(const std::shared_ptr<message::RequestVote> message) = 0;
            // 发送RequestVoteResponse消息
            virtual void writeRequestVoteResponse(const std::shared_ptr<message::RequestVoteResponse> message) = 0;
            // 发送AppendEntries消息
            virtual void writeAppendEntries(const std::shared_ptr<message::AppendEntries> message) = 0;
            // 发送AppendEntriesResponse消息
            virtual void writeAppendEntriesResponse(const std::shared_ptr<message::AppendEntriesResponse> message) = 0;
            bool isOpen()const;
            // 关闭
            virtual void close() = 0;
            // 添加Close回掉函数
            virtual void addCloseCallback(std::function<void(Channel * channel)> callback) = 0;
        protected:
            std::shared_ptr<Decoder> mDecoder;
            std::shared_ptr<Encoder> mEncoder;
            mutable bool openStatus;
        };
    }
}


#endif //KAKAKV_CHANNEL_H
