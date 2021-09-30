//
// Created by 凌宇 on 2021/9/26.
//

#ifndef KAKAKV_ASIOCONNECTOR_H
#define KAKAKV_ASIOCONNECTOR_H

#include <net/core/Connector.h>
#include <net/Selector.h>
#include <cluster/NodeEndpoint.h>
#include <net/OutboundChannelGroup.h>
#include <net/InboundChannelGroup.h>
namespace kakakv {

    namespace common{
        class EventBus;
    }

    namespace message{
        class RequestVote;
        class RequestVoteResponse;
        class AppendEntries;
        class AppendEntriesResponse;
    }

    namespace task{
        class ASIOIOService;
    }

    namespace net {

        class ASIOConnector : public net::Connector, public  Selector::Listener,private std::enable_shared_from_this<ASIOConnector> {
        public:
            ASIOConnector(cluster::NodeId selfNodeId, std::shared_ptr<common::EventBus> eventBus,
                          std::string listenIP = "0.0.0.0", unsigned short listenPort = 6000);

            void initialize() throw(char *) override;

            /**
             * 重置连接
             */
            void resetChannels() override;

            void close() override;

            /**
             * 发送RequestVote给多个节点
             * @param requestVoteMessage
             * @param destinationEndpoints
             */
            void sendRequestVote(std::shared_ptr<message::RequestVote> requestVoteMessage,
                                 const std::vector<cluster::NodeEndpoint> destinationEndpoints);

            /**
             * 回复RequestVote消息
             * @param destinationEndpoint
             */
            void replyRequestVote(std::shared_ptr<message::RequestVoteResponse> requestVoteResponseMessage,
                                  const cluster::NodeEndpoint destinationEndpoint);

            /**
             * 发送AppendEntries
             * @param appendEntriesMessage
             * @param destinationEndpoint
             */
            void sendAppendEntries(std::shared_ptr<message::AppendEntries> appendEntriesMessage,
                                   const cluster::NodeEndpoint destinationEndpoint);

            void
            replyAppendEntries(std::shared_ptr<message::AppendEntriesResponse> appendEntriesResponseMessage,
                               const cluster::NodeEndpoint destinationEndpoint);

        private:
            void onReceiveConnect(std::shared_ptr<ASIOChannel> channel) override;
            std::shared_ptr<ASIOChannel> getChannel(cluster::NodeEndpoint endpoint);

            std::unique_ptr<Selector> selector; // Selector 线程池
            std::shared_ptr<task::ASIOIOService> ioService; // IO 线程池
            bool ioExecutorShared; // 是否和上层服务等共享IO线程池
            std::shared_ptr<common::EventBus> eventBus;
            std::string ip;
            unsigned short port;
            std::unique_ptr<InboundChannelGroup> inboundChannelGroup;
            std::unique_ptr<OutboundChannelGroup> outboundChannelGroup;
        };
    }
}


#endif //KAKAKV_ASIOCONNECTOR_H
