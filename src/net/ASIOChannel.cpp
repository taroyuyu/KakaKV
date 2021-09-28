//
// Created by 凌宇 on 2021/9/27.
//

#include <net/ASIOChannel.h>

namespace kakakv{
    namespace net{
        ASIOChannel::ASIOChannel(std::unique_ptr<boost::asio::ip::tcp::socket> socket,std::shared_ptr<Decoder> decoder,std::shared_ptr<Encoder> encoder):
        Channel(decoder,encoder),mSocket(std::move(socket)){

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
        // 添加Close回掉函数
        void ASIOChannel::addCloseCallback(std::function<void(Channel * channel)> callback){

        }
    }
}