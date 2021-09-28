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
#include <cluster/NodeEndpoint.h>

namespace kakakv {
    namespace net {
        class ASIOConnector : public net::Connector {
        public:
            ASIOConnector(cluster::NodeId selfNodeId, std::shared_ptr<common::EventBus> eventBus,
                          std::string listenIP = "0.0.0.0", unsigned short listenPort = 6000);

            void initialize() throw(char *) override;

            void close() override;

            /**
             * 发送RequestVote给多个节点
             * @param requestVoteMessage
             * @param destinationEndpoints
             */
            void sendRequestVote(std::shared_ptr<message::RequestVote> requestVoteMessage,
                                 const std::vector<cluster::NodeEndpoint> destinationEndpoints) override;

            /**
             * 回复RequestVote消息
             * @param destinationEndpoint
             */
            void replyRequestVote(std::shared_ptr<message::RequestVoteResponse> requestVoteResponseMessage,
                                  const cluster::NodeEndpoint destinationEndpoint) override;

            /**
             * 发送AppendEntries
             * @param appendEntriesMessage
             * @param destinationEndpoint
             */
            void sendAppendEntries(std::shared_ptr<message::AppendEntries> appendEntriesMessage,
                                   const cluster::NodeEndpoint destinationEndpoint) override;

            void
            replyAppendEntries(std::shared_ptr<message::AppendEntriesResponse> appendEntriesResponseMessage,
                               const cluster::NodeEndpoint destinationEndpoint) override;

        private:
            std::shared_ptr<Channel> getChannel(cluster::NodeEndpoint endpoint);

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
