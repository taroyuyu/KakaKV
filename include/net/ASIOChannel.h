//
// Created by 凌宇 on 2021/9/27.
//

#ifndef KAKAKV_ASIOCHANNEL_H
#define KAKAKV_ASIOCHANNEL_H

#include <net/core/Channel.h>
#include <boost/asio.hpp>
#include <memory>
#include <set>
#include <message/RequestVote.h>
#include <message/RequestVoteResponse.h>
#include <message/AppendEntries.h>
#include <message/AppendEntriesResponse.h>
namespace kakakv{
    namespace net{
        class Selector;
        class ASIOChannel:public Channel{
        public:
            friend Selector;
            ASIOChannel(std::unique_ptr<boost::asio::ip::tcp::socket> socket,std::shared_ptr<Decoder> decoder,std::shared_ptr<Encoder> encoder);
            void addHandler(std::shared_ptr<AbstractHandler> handler)override;
            void removeHandler(std::shared_ptr<AbstractHandler> handler)override;
            void writeMessage(std::shared_ptr<const Message> message)override;
            // 发送RequestVote消息
            void writeRequestVote(const std::shared_ptr<message::RequestVote> message);
            // 发送RequestVoteResponse消息
            void writeRequestVoteResponse(const std::shared_ptr<message::RequestVoteResponse> message);
            // 发送AppendEntries消息
            void writeAppendEntries(const std::shared_ptr<message::AppendEntries> message);
            // 发送AppendEntriesResponse消息
            void writeAppendEntriesResponse(const std::shared_ptr<message::AppendEntriesResponse> message);
            // 关闭
            void close()override;
            // 添加Close回掉函数
            void addCloseCallback(std::function<void(Channel * channel)> callback)override;
        private:
            const std::unique_ptr<boost::asio::ip::tcp::socket> mSocket;
            std::set<std::shared_ptr<AbstractHandler>> mHandlerSet;
        };
    }
}


#endif //KAKAKV_ASIOCHANNEL_H
