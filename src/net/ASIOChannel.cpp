//
// Created by 凌宇 on 2021/9/27.
//

#include <net/ASIOChannel.h>
#include <net/serialization/KakaKVRaftMessage.pb.h>
#include <log/GeneralLogEntry.h>
#include <log/NoOpLogEntry.h>
namespace kakakv{
    namespace net{
        ASIOChannel::ASIOChannel(std::unique_ptr<boost::asio::ip::tcp::socket> socket,std::shared_ptr<Decoder> decoder,std::shared_ptr<Encoder> encoder):
        Channel(decoder,encoder),mSocket(std::move(socket)),mDecoder(decoder),mEncoder(encoder),mCodecBuffer(std::make_shared<common::net::CircleBuffer>(1024)){

        }

        void ASIOChannel::addHandler(std::shared_ptr<AbstractHandler> handler){
            auto it = this->mHandlerSet.find(handler);
            if (it != this->mHandlerSet.end()) {
                return;
            }
            this->mHandlerSet.insert(handler);
        }
        void ASIOChannel::removeHandler(std::shared_ptr<AbstractHandler> handler){
            auto it = this->mHandlerSet.find(handler);
            if (it == this->mHandlerSet.end()) {
                return;
            }
            this->mHandlerSet.erase(it);
        }
        void ASIOChannel::writeMessage(std::shared_ptr<const Message> message){
            if (!message){
                return;
            }
            if (typeid(message.get()) == typeid(const kakakv::message::RequestVote*)){
                auto requestVoteMessage = std::dynamic_pointer_cast<const kakakv::message::RequestVote>(message);
                assert(requestVoteMessage);
                this->writeRequestVote(requestVoteMessage);
            }else if (typeid(message.get()) == typeid(const kakakv::message::RequestVoteResponse*)){
                auto requestVoteResponseMessage = std::dynamic_pointer_cast<const kakakv::message::RequestVoteResponse>(message);
                assert(requestVoteResponseMessage);
                this->writeRequestVoteResponse(requestVoteResponseMessage);
            }else if (typeid(message.get()) == typeid(const kakakv::message::AppendEntries*)){
                auto appendEntriesMessage = std::dynamic_pointer_cast<const kakakv::message::AppendEntries>(message);
                assert(appendEntriesMessage);
                this->writeAppendEntries(appendEntriesMessage);
            }else if (typeid(message.get()) == typeid(const kakakv::message::AppendEntriesResponse*)){
                auto appendEntriesResponseMessage = std::dynamic_pointer_cast<const kakakv::message::AppendEntriesResponse>(message);
                assert(appendEntriesResponseMessage);
                this->writeAppendEntriesResponse(appendEntriesResponseMessage);
            }else{
                //未知类型
                assert(false);
            }
        }
        // 发送RequestVote消息
        void ASIOChannel::writeRequestVote(const std::shared_ptr<const kakakv::message::RequestVote> message){
            //1. 将消息封装成Protobuf格式
            auto requestVoteMessage = std::make_shared<message::RequestVoteMessage>();
            requestVoteMessage->set_term(message->term);
            requestVoteMessage->set_candidateid(message->candidateId);
            requestVoteMessage->set_lastlogterm(message->lastLogTerm);
            requestVoteMessage->set_lastlogindex(message->lastLogIndex);
            assert(requestVoteMessage->IsInitialized());
            //2. 将消息封装成字节流
            {
                std::lock_guard<std::mutex> lock(this->mCodecBufferMutex);
                assert(this->mCodecBuffer->getUsed() == 0);
                this->mEncoder->encapsulateMessageToByteStream(*requestVoteMessage,this->mCodecBuffer);
            }
        }
        // 发送RequestVoteResponse消息
        void ASIOChannel::writeRequestVoteResponse(const std::shared_ptr<const kakakv::message::RequestVoteResponse> message){
            //1. 将消息封装成Protobuf格式
            auto requestVoteResponseMessage = std::make_shared<message::RequestVoteResponseMessage>();
            requestVoteResponseMessage->set_term(message->term);
            requestVoteResponseMessage->set_votegranted(message->voteGranted);
            assert(requestVoteResponseMessage->IsInitialized());
            //2. 将消息封装成字节流
            {
                std::lock_guard<std::mutex> lock(this->mCodecBufferMutex);
                assert(this->mCodecBuffer->getUsed() == 0);
                this->mEncoder->encapsulateMessageToByteStream(*requestVoteResponseMessage,this->mCodecBuffer);
            }
        }
        // 发送AppendEntries消息
        void ASIOChannel::writeAppendEntries(const std::shared_ptr<const kakakv::message::AppendEntries> message){
            //1. 将消息封装成Protobuf格式
            auto appendEntriesMessage = std::make_shared<message::AppendEntriesMessage>();
            appendEntriesMessage->set_term(message->term);
            appendEntriesMessage->set_leaderid(message->leaderId);
            appendEntriesMessage->set_prevlogterm(message->prevLogTerm);
            appendEntriesMessage->set_prevlogindex(message->prevLogIndex);
            appendEntriesMessage->set_leadercommit(message->leaderCommitIndex);
            for(auto entry : message->entryList){
                auto entryItem = appendEntriesMessage->add_entrylist();
                entryItem->set_index(entry->getIndex());
                entryItem->set_term(entry->getTerm());
                if (typeid(entry.get()) == typeid(log::GeneralLogEntry*)){
                    entryItem->set_kind(message::AppendEntriesMessage_Entry_Kind_GeneralLog);
                    auto generalLog = std::dynamic_pointer_cast<log::GeneralLogEntry>(entry);
                    assert(generalLog);
                    std::string data(generalLog->getPayload().first, generalLog->getPayload().second);
                    entryItem->set_data(data);
                }else if (typeid(entry.get()) == typeid(log::NoOpLogEntry*)){
                    entryItem->set_kind(message::AppendEntriesMessage_Entry_Kind_NoOpLog);
                }else{
                    assert(false);
                    continue;
                }
            }
            assert(appendEntriesMessage->IsInitialized());
            //2. 将消息封装成字节流
            {
                std::lock_guard<std::mutex> lock(this->mCodecBufferMutex);
                assert(this->mCodecBuffer->getUsed() == 0);
                this->mEncoder->encapsulateMessageToByteStream(*appendEntriesMessage,this->mCodecBuffer);
            }
        }
        // 发送AppendEntriesResponse消息
        void ASIOChannel::writeAppendEntriesResponse(const std::shared_ptr<const kakakv::message::AppendEntriesResponse> message){
            //1. 将消息封装成Protobuf格式
            auto appendEntriesResponseMessage = std::make_shared<message::AppendEntriesResponseMessage>();
            appendEntriesResponseMessage->set_term(message->term);
            appendEntriesResponseMessage->set_success(message->success);
            assert(appendEntriesResponseMessage->IsInitialized());
            //2. 将消息封装成字节流
            {
                std::lock_guard<std::mutex> lock(this->mCodecBufferMutex);
                assert(this->mCodecBuffer->getUsed() == 0);
                this->mEncoder->encapsulateMessageToByteStream(*appendEntriesResponseMessage,this->mCodecBuffer);
            }
        }
        // 关闭
        void ASIOChannel::close(){
            //1. 关闭连接
            boost::system::error_code ec;
            this->mSocket->shutdown(boost::asio::ip::tcp::socket::shutdown_both,ec);
            if (ec){

            }
            this->mSocket->close(ec);
            if (ec){

            }
            //2. 执行Close回掉函数
            for (auto callback : this->closeCallbackList){
                callback(this->shared_from_this());
            }
        }
        // 添加Close回掉函数
        void ASIOChannel::addCloseCallback(std::function<void(std::shared_ptr<Channel> channel)> callback){
            this->closeCallbackList.push_back(callback);
        }
    }
}