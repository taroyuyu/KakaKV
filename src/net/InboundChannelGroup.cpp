//
// Created by 凌宇 on 2021/9/27.
//

#include <net/InboundChannelGroup.h>

namespace kakakv {
    namespace net {
        // 增加连接入口
        void InboundChannelGroup::add(cluster::NodeId remoteId,std::shared_ptr<ASIOChannel> channel){
            std::weak_ptr<ASIOChannel> channelWeakPtr = channel;
            channel->addCloseCallback([=](Channel * channel){
                auto channelPtr = channelWeakPtr.lock();
                if (!channelPtr || channelPtr.get() != channel){
                    return ;
                }
                this->channels.remove(channelPtr);
            });
        }
        // 移除连接
        void InboundChannelGroup::remove(std::shared_ptr<ASIOChannel> channel){
                this->channels.remove(channel);
        }
        // 关闭所有连接
        void InboundChannelGroup::closeAll(){
            for (auto channel : this->channels){
                channel->close();
            }
        }
    }
}