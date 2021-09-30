//
// Created by 凌宇 on 2021/9/27.
//

#include <net/ASIOChannel.h>
#include <net/serialization/KakaKVRaftMessage.pb.h>
#include <log/GeneralLogEntry.h>
#include <log/NoOpLogEntry.h>
#include <boost/bind.hpp>

namespace kakakv {
    namespace net {
        ASIOChannel::ASIOChannel(std::unique_ptr<boost::asio::ip::tcp::socket> socket, std::shared_ptr<Decoder> decoder,
                                 std::shared_ptr<Encoder> encoder) :
                Channel(decoder, encoder), mSocket(std::move(socket)), mDecoder(decoder), mEncoder(encoder),
                mOutputCodecBuffer(std::make_shared<common::net::CircleBuffer>(1024)),
                mInputCodecBuffer(std::make_shared<common::net::CircleBuffer>(1024)), mTmpInputBufferLength(1024),
                mTmpInputBuffer(new char[1024]),
                mTmpOutputBufferLength(0), nodeId(cluster::NULLNodeId) {

        }

        void ASIOChannel::addHandler(std::weak_ptr<AbstractHandler> handler) {
            auto it = this->mHandlerSet.find(handler);
            if (it != this->mHandlerSet.end()) {
                return;
            }
            this->mHandlerSet.insert(handler);
        }

        void ASIOChannel::removeHandler(std::weak_ptr<AbstractHandler> handler) {
            auto it = this->mHandlerSet.find(handler);
            if (it == this->mHandlerSet.end()) {
                return;
            }
            this->mHandlerSet.erase(it);
        }

        void ASIOChannel::writeMessage(std::shared_ptr<const Message> message) {
            if (!message) {
                return;
            }
            if (typeid(message.get()) == typeid(const kakakv::message::RequestVote *)) {
                auto requestVoteMessage = std::dynamic_pointer_cast<const kakakv::message::RequestVote>(message);
                assert(requestVoteMessage);
                this->writeRequestVote(requestVoteMessage);
            } else if (typeid(message.get()) == typeid(const kakakv::message::RequestVoteResponse *)) {
                auto requestVoteResponseMessage = std::dynamic_pointer_cast<const kakakv::message::RequestVoteResponse>(
                        message);
                assert(requestVoteResponseMessage);
                this->writeRequestVoteResponse(requestVoteResponseMessage);
            } else if (typeid(message.get()) == typeid(const kakakv::message::AppendEntries *)) {
                auto appendEntriesMessage = std::dynamic_pointer_cast<const kakakv::message::AppendEntries>(message);
                assert(appendEntriesMessage);
                this->writeAppendEntries(appendEntriesMessage);
            } else if (typeid(message.get()) == typeid(const kakakv::message::AppendEntriesResponse *)) {
                auto appendEntriesResponseMessage = std::dynamic_pointer_cast<const kakakv::message::AppendEntriesResponse>(
                        message);
                assert(appendEntriesResponseMessage);
                this->writeAppendEntriesResponse(appendEntriesResponseMessage);
            } else {
                //未知类型
                assert(false);
            }
        }

        // 发送RequestVote消息
        void ASIOChannel::writeRequestVote(const std::shared_ptr<const kakakv::message::RequestVote> message) {
            //1. 将消息封装成Protobuf格式
            auto requestVoteMessage = std::make_shared<message::RequestVoteMessage>();
            requestVoteMessage->set_term(message->term);
            requestVoteMessage->set_candidateid(message->candidateId);
            requestVoteMessage->set_lastlogterm(message->lastLogTerm);
            requestVoteMessage->set_lastlogindex(message->lastLogIndex);
            assert(requestVoteMessage->IsInitialized());
            //2. 将消息封装成字节流
            std::lock_guard<std::mutex> lock(this->mMutex);
            assert(this->mOutputCodecBuffer->getUsed() == 0);
            this->mEncoder->encapsulateMessageToByteStream(*requestVoteMessage, this->mOutputCodecBuffer);
            //3. 发送字节流
            this->sendByteStream();
        }

        // 发送RequestVoteResponse消息
        void ASIOChannel::writeRequestVoteResponse(
                const std::shared_ptr<const kakakv::message::RequestVoteResponse> message) {
            //1. 将消息封装成Protobuf格式
            auto requestVoteResponseMessage = std::make_shared<message::RequestVoteResponseMessage>();
            requestVoteResponseMessage->set_term(message->term);
            requestVoteResponseMessage->set_votegranted(message->voteGranted);
            assert(requestVoteResponseMessage->IsInitialized());
            //2. 将消息封装成字节流
            std::lock_guard<std::mutex> lock(this->mMutex);
            assert(this->mOutputCodecBuffer->getUsed() == 0);
            this->mEncoder->encapsulateMessageToByteStream(*requestVoteResponseMessage, this->mOutputCodecBuffer);
            //3. 发送字节流
            this->sendByteStream();
        }

        // 发送AppendEntries消息
        void ASIOChannel::writeAppendEntries(const std::shared_ptr<const kakakv::message::AppendEntries> message) {
            //1. 将消息封装成Protobuf格式
            auto appendEntriesMessage = std::make_shared<message::AppendEntriesMessage>();
            appendEntriesMessage->set_term(message->term);
            appendEntriesMessage->set_leaderid(message->leaderId);
            appendEntriesMessage->set_prevlogterm(message->prevLogTerm);
            appendEntriesMessage->set_prevlogindex(message->prevLogIndex);
            appendEntriesMessage->set_leadercommit(message->leaderCommitIndex);
            for (auto entry: message->entryList) {
                auto entryItem = appendEntriesMessage->add_entrylist();
                entryItem->set_index(entry->getIndex());
                entryItem->set_term(entry->getTerm());
                if (typeid(entry.get()) == typeid(log::GeneralLogEntry *)) {
                    entryItem->set_kind(message::AppendEntriesMessage_Entry_Kind_GeneralLog);
                    auto generalLog = std::dynamic_pointer_cast<log::GeneralLogEntry>(entry);
                    assert(generalLog);
                    std::string data = generalLog->getPayload();
                    entryItem->set_data(data);
                } else if (typeid(entry.get()) == typeid(log::NoOpLogEntry *)) {
                    entryItem->set_kind(message::AppendEntriesMessage_Entry_Kind_NoOpLog);
                } else {
                    assert(false);
                    continue;
                }
            }
            assert(appendEntriesMessage->IsInitialized());
            //2. 将消息封装成字节流
            std::lock_guard<std::mutex> lock(this->mMutex);
            assert(this->mOutputCodecBuffer->getUsed() == 0);
            this->mEncoder->encapsulateMessageToByteStream(*appendEntriesMessage, this->mOutputCodecBuffer);
            //3. 发送字节流
            this->sendByteStream();
        }

        // 发送AppendEntriesResponse消息
        void ASIOChannel::writeAppendEntriesResponse(
                const std::shared_ptr<const kakakv::message::AppendEntriesResponse> message) {
            //1. 将消息封装成Protobuf格式
            auto appendEntriesResponseMessage = std::make_shared<message::AppendEntriesResponseMessage>();
            appendEntriesResponseMessage->set_term(message->term);
            appendEntriesResponseMessage->set_success(message->success);
            assert(appendEntriesResponseMessage->IsInitialized());
            //2. 将消息封装成字节流
            std::lock_guard<std::mutex> lock(this->mMutex);
            assert(this->mOutputCodecBuffer->getUsed() == 0);
            this->mEncoder->encapsulateMessageToByteStream(*appendEntriesResponseMessage, this->mOutputCodecBuffer);
            //3. 发送字节流
            this->sendByteStream();
        }

        void ASIOChannel::sendByteStream() {
            //1. 判断是否需要更新临时输出缓冲区
            if (this->mOutputCodecBuffer->getUsed() > this->mTmpOutputBufferLength) {
                this->mTmpOutputBufferLength = this->mOutputCodecBuffer->getUsed();
                this->mTmpoutputBuffer.reset(new char[mTmpOutputBufferLength]);
            }
            //2. 将字节流放入临时输出缓冲区中
            auto length = this->mOutputCodecBuffer->retrive(mTmpoutputBuffer.get(), mTmpOutputBufferLength);
            assert(this->mOutputCodecBuffer->getUsed() == 0);
            //3. 将临时输出缓冲区中的数据拷贝到输出缓冲区
            auto output = std::make_shared<std::vector<boost::uint8_t>>();
            std::copy((const boost::uint8_t *) mTmpoutputBuffer.get(),
                      (const boost::uint8_t *) mTmpoutputBuffer.get() + length, std::back_inserter(*output));
            this->mOutputBuffer.push_back(output);
            //4. 准备发送
            bool canSendNow = this->mOutputBuffer.empty();
            if (canSendNow) {
                boost::asio::async_write(*this->mSocket, boost::asio::buffer(*this->mOutputBuffer.front()),
                                         boost::bind(&ASIOChannel::onSend, this->shared_from_this(),
                                                     boost::asio::placeholders::error, this->mOutputBuffer.begin()));
            }
        }

        void ASIOChannel::onSend(const boost::system::error_code &ec,
                                 std::list<std::shared_ptr<std::vector<boost::uint8_t>>>::iterator itr) {
            if (ec) {
                //发送失败
                this->close();
                return;
            }
            this->mOutputBuffer.erase(itr);
            if (this->mOutputBuffer.empty()) {
                return;
            }
            boost::asio::async_write(*this->mSocket, boost::asio::buffer(*this->mOutputBuffer.front()),
                                     boost::bind(&ASIOChannel::onSend, this->shared_from_this(),
                                                 boost::asio::placeholders::error, this->mOutputBuffer.begin()));
        }

        void ASIOChannel::waitForReceive() {
            std::lock_guard<std::mutex> lock(this->mMutex);
            this->mSocket->async_read_some(
                    boost::asio::buffer(this->mTmpInputBuffer.get(), this->mTmpInputBufferLength),
                    std::bind(&ASIOChannel::onRecv, this->shared_from_this(), std::placeholders::_1,
                              std::placeholders::_2));
        }

        void ASIOChannel::onRecv(const boost::system::error_code &ec, size_t bytesTransferred) {
            if (ec) {
                this->close();
                return;
            }
            // 将数据放入mInputCodecBuffer中
            this->mInputCodecBuffer->append(this->mTmpInputBuffer.get(), bytesTransferred);
            // 尝试提取数据
            std::shared_ptr<::google::protobuf::Message> message;
            while (this->mDecoder->tryToretriveMessage(this->mInputCodecBuffer, message)) {
                // 将消息转换成内部格式
                auto internalMessage = convertExternalMessageToInternalMessage(message);
                if (!internalMessage) {
                    assert(internalMessage);
                    continue;
                }
                //分发消息
                for (auto handlerWeakPtr: this->mHandlerSet) {
                    auto handler = handlerWeakPtr.lock();
                    if (!handler) {
                        continue;
                    }
                    handler->channelRead(this->shared_from_this(), internalMessage);
                }
            }
            // 继续等待数据
            this->waitForReceive();
        }

        std::shared_ptr<kakakv::message::Message> ASIOChannel::convertExternalMessageToInternalMessage(
                std::shared_ptr<::google::protobuf::Message> message) {
            assert(this->nodeId != cluster::NULLNodeId);
            std::string messageType = message->GetTypeName();
            if (messageType == message::RequestVoteMessage::default_instance().GetTypeName()) {
                auto externalMessage = std::dynamic_pointer_cast<message::RequestVoteMessage>(message);
                if (!externalMessage){
                    assert(externalMessage);
                    return nullptr;
                }
                auto internalMessage = std::make_shared<kakakv::message::RequestVote>(externalMessage->term(),cluster::NodeId(externalMessage->candidateid()),externalMessage->lastlogindex(),externalMessage->lastlogterm());
                return internalMessage;
            } else if (messageType == message::RequestVoteResponseMessage::default_instance().GetTypeName()) {
                auto externalMessage = std::dynamic_pointer_cast<message::RequestVoteResponseMessage>(message);
                if (!externalMessage){
                    assert(externalMessage);
                    return nullptr;
                }
                auto internalMessage = std::make_shared<kakakv::message::RequestVoteResponse>(externalMessage->term(),this->nodeId,externalMessage->votegranted());
                return internalMessage;
            } else if (messageType == message::AppendEntriesMessage::default_instance().GetTypeName()) {
                auto externalMessage = std::dynamic_pointer_cast<message::AppendEntriesMessage>(message);
                if (!externalMessage){
                    assert(externalMessage);
                    return nullptr;
                }
                auto internalMessage = std::make_shared<kakakv::message::AppendEntries>(externalMessage->term(),cluster::NodeId(externalMessage->leaderid()));
                internalMessage->prevLogTerm = externalMessage->prevlogterm();
                internalMessage->prevLogIndex = externalMessage->prevlogindex();
                internalMessage->leaderCommitIndex = externalMessage->leadercommit();
                for (auto item : externalMessage->entrylist()){
                    auto entry = std::shared_ptr<log::LogEntry>();
                    if (item.kind() == message::AppendEntriesMessage_Entry_Kind_GeneralLog){
                        entry = std::make_shared<log::GeneralLogEntry>(item.index(),item.term(),std::unique_ptr<std::string>(item.release_data()));
                    }else if (item.kind() == message::AppendEntriesMessage_Entry_Kind_NoOpLog){
                        entry = std::make_shared<log::NoOpLogEntry>(item.index(),item.term());
                    }
                    internalMessage->entryList.push_back(entry);
                }
                return internalMessage;
            } else if (messageType == message::AppendEntriesResponseMessage::default_instance().GetTypeName()) {
                auto externalMessage = std::dynamic_pointer_cast<message::AppendEntriesResponseMessage>(message);
                if (!externalMessage){
                    assert(externalMessage);
                    return nullptr;
                }
                auto internalMessage = std::make_shared<kakakv::message::AppendEntriesResponse>(externalMessage->term(),this->nodeId,externalMessage->success());
                return internalMessage;
            } else {
                return nullptr;
            }

        }

        // 关闭
        void ASIOChannel::close() {
            //1. 关闭连接
            boost::system::error_code ec;
            this->mSocket->shutdown(boost::asio::ip::tcp::socket::shutdown_both, ec);
            if (ec) {

            }
            this->mSocket->close(ec);
            if (ec) {

            }
            //2. 执行Close回掉函数
            for (auto callback: this->closeCallbackList) {
                callback(this->shared_from_this());
            }
        }

        // 添加Close回掉函数
        void ASIOChannel::addCloseCallback(std::function<void(std::shared_ptr<Channel> channel)> callback) {
            this->closeCallbackList.push_back(callback);
        }
    }
}