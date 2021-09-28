//
// Created by 凌宇 on 2021/9/27.
//

#ifndef KAKAKV_ASIOCHANNEL_H
#define KAKAKV_ASIOCHANNEL_H

#include <net/Channel.h>
#include <boost/asio.hpp>
#include <memory>
namespace kakakv{
    namespace net{
        class ASIOChannel:public Channel{
        public:
            ASIOChannel(std::unique_ptr<boost::asio::ip::tcp::socket> socket);
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
            // 添加Close回掉函数
            void addCloseCallback(std::function<void(Channel * channel)> callback)override;
        private:
            const std::unique_ptr<boost::asio::ip::tcp::socket> mSocket;
        };
    }
}


#endif //KAKAKV_ASIOCHANNEL_H
