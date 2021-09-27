//
// Created by 凌宇 on 2021/9/26.
//

#ifndef KAKAKV_ASIOCONNECTOR_H
#define KAKAKV_ASIOCONNECTOR_H

#include <net/Connector.h>
#include <string>
#include <net/Selector.h>
#include <task/IOServce.h>
#include <common/eventBus/EventBus.h>
#include <cluster/NodeId.h>
#include <net/InboundChannelGroup.h>
#include <net/OutboundChannelGroup.h>
namespace kakakv{
    namespace net{
        class ASIOConnector:public net::Connector{
        public:
            ASIOConnector(cluster::NodeId selfNodeId,std::shared_ptr<common::EventBus> eventBus,std::string listenIP = "0.0.0.0",unsigned short listenPort = 6000);
            void initialize()throw(char*)override;
            void close()override;
        private:
            const std::unique_ptr<Selector> selector; // Selector 线程池
            const std::shared_ptr<task::IOServce> ioService; // IO 线程池
            const bool ioExecutorShared; // 是否和上层服务等共享IO线程池
            const std::shared_ptr<common::EventBus> eventBus;
            const std::string ip;
            const unsigned short port;
            const std::unique_ptr<InboundChannelGroup> inboundChannelGroup;
            const std::unique_ptr<OutboundChannelGroup> outboundChannelGroup;
        };
    }
}


#endif //KAKAKV_ASIOCONNECTOR_H
