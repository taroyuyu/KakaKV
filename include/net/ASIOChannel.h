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
#include <common/net/buffer/CircleBuffer.h>
#include <mutex>
#include <list>
namespace kakakv {
    namespace net {
        class Selector;

        class ASIOChannel : public Channel, private std::enable_shared_from_this<ASIOChannel> {
        public:
            friend Selector;

            ASIOChannel(std::unique_ptr<boost::asio::ip::tcp::socket> socket, std::shared_ptr<Decoder> decoder,
                        std::shared_ptr<Encoder> encoder);

            void addHandler(std::weak_ptr<AbstractHandler> handler) override;

            void removeHandler(std::weak_ptr<AbstractHandler> handler) override;

            void writeMessage(std::shared_ptr<const Message> message) override;

            // 发送RequestVote消息
            void writeRequestVote(const std::shared_ptr<const message::RequestVote> message);

            // 发送RequestVoteResponse消息
            void writeRequestVoteResponse(const std::shared_ptr<const message::RequestVoteResponse> message);

            // 发送AppendEntries消息
            void writeAppendEntries(const std::shared_ptr<const message::AppendEntries> message);

            // 发送AppendEntriesResponse消息
            void writeAppendEntriesResponse(const std::shared_ptr<const message::AppendEntriesResponse> message);

            // 关闭
            void close() override;

            // 添加Close回调函数
            void addCloseCallback(std::function<void(std::shared_ptr<Channel> channel)> callback) override;

        private:
            void sendByteStream();
            void onSend(const boost::system::error_code & ec,std::list<std::shared_ptr<std::vector<boost::uint8_t>>>::iterator itr);
            void waitForReceive();
            void onRecv(const boost::system::error_code & ec,size_t bytesTransferred);
            std::shared_ptr<kakakv::message::Message> convertExternalMessageToInternalMessage(std::shared_ptr<::google::protobuf::Message> externalMessage);
            std::mutex mMutex;
            const std::unique_ptr<boost::asio::ip::tcp::socket> mSocket;
            std::list<std::vector<boost::uint8_t> > mInputBuffer;
            const std::unique_ptr<char[]> mTmpInputBuffer;
            const unsigned long mTmpInputBufferLength;
            std::list<std::shared_ptr<std::vector<boost::uint8_t>>> mOutputBuffer;
            std::unique_ptr<char[]> mTmpoutputBuffer;
            unsigned long mTmpOutputBufferLength;
            std::set<std::weak_ptr<AbstractHandler>,std::owner_less<std::weak_ptr<AbstractHandler>>> mHandlerSet;
            std::shared_ptr<Decoder> mDecoder;
            std::shared_ptr<Encoder> mEncoder;
            const std::shared_ptr<common::net::CircleBuffer> mOutputCodecBuffer;
            const std::shared_ptr<common::net::CircleBuffer> mInputCodecBuffer;
            cluster::NodeId nodeId;
        };
    }
}


#endif //KAKAKV_ASIOCHANNEL_H
