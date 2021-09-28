//
// Created by 凌宇 on 2021/9/27.
//

#ifndef KAKAKV_OUTBOUNDCHANNELGROUP_H
#define KAKAKV_OUTBOUNDCHANNELGROUP_H

#include <net/ASIOChannel.h>
#include <cluster/NodeId.h>
#include <net/Endpoint.h>
#include <common/eventBus/EventBus.h>
#include <memory>
#include <map>
#include <task/IOServce.h>
#include <future>
namespace kakakv {
    namespace net {
        class OutboundChannelGroup {
        public:
            OutboundChannelGroup(std::shared_ptr<task::IOServce> ioService,std::shared_ptr<common::EventBus> eventBus,cluster::NodeId selfNodeId);
            std::shared_ptr<ASIOChannel> getOrConnect(cluster::NodeId nodeId,Endpoint endpoint);
            void closeAll();
        private:
            std::shared_ptr<ASIOChannel> connect(cluster::NodeId nodeId,Endpoint endpoint)throw(char *);
            const std::shared_ptr<task::IOServce> mIOService;
            const std::shared_ptr<common::EventBus> mEventBus;
            const cluster::NodeId mSelfNodeId;
            std::map<cluster::NodeId,std::shared_ptr<ASIOChannel>> channelMap;
        };
    }
}


#endif //KAKAKV_OUTBOUNDCHANNELGROUP_H
