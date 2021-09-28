//
// Created by 凌宇 on 2021/9/27.
//

#include <net/OutboundChannelGroup.h>
#include <boost/asio.hpp>
//#include <future>
namespace kakakv {
    namespace net {
        OutboundChannelGroup::OutboundChannelGroup(std::shared_ptr<task::IOServce> ioService,std::shared_ptr<common::EventBus> eventBus,cluster::NodeId selfNodeId):
        mIOService(ioService),mEventBus(eventBus), mSelfNodeId(selfNodeId){
        }
        std::shared_ptr<ASIOChannel> OutboundChannelGroup::connect(cluster::NodeId nodeId,Endpoint endpoint)throw(char *){
            // 1. 创建端口
            // 1.1  创建address
            boost::system::error_code ec;
            auto targetAddress = boost::asio::ip::address::from_string(endpoint.host,ec);
            if (ec){
                throw "Invalid Address";
            }
            // 1.2 创建端口
            auto targetEndpoint = boost::asio::ip::tcp::endpoint(targetAddress,endpoint.port);
            // 2. 创建socket
            auto socket = std::make_unique<boost::asio::ip::tcp::socket>(*this->mIOService->mIOService);
            // 3. 连接
            socket->connect(targetEndpoint,ec);
            if (ec){
                // 连接失败
                throw "Failed to connect";
            }
            // 4. TODO:将socket包装成ASIOChanel
//            auto channel = std::make_shared<net::ASIOChannel>(std::move(socket));
            std::shared_ptr<net::ASIOChannel> channel = nullptr;
            std::weak_ptr<net::ASIOChannel> channelWeakPtr = channel;
            channel->addCloseCallback([=](net::Channel* channel){
                auto channelPtr = channelWeakPtr.lock();
                if (!channelPtr || channelPtr.get() != channel){
                    return;
                }
                // 连接关闭后从组中移除
                auto it = this->channelMap.find(nodeId);
                if (it == this->channelMap.end()){
                    return;
                }
                this->channelMap.erase(it);
            });
            return channel;
        }
        std::shared_ptr<ASIOChannel> OutboundChannelGroup::getOrConnect(cluster::NodeId nodeId,Endpoint endpoint){
            auto it = this->channelMap.find(nodeId);
            // 如果连接不存在则创建连接
            if (it == this->channelMap.end()){
                this->channelMap.insert({nodeId,this->connect(nodeId,endpoint)});
                it = this->channelMap.find(nodeId);
            }
            if (it == this->channelMap.end()){
                assert(false);
                return nullptr;
            }else {
                return it->second;
            }

        }

        void OutboundChannelGroup::closeAll(){
        }
    }
}