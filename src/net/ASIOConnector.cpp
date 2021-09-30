//
// Created by 凌宇 on 2021/9/26.
//

#include <net/ASIOConnector.h>
#include <task/ASIOIOService.h>
#include <net/InboundChannelGroup.h>
#include <net/OutboundChannelGroup.h>
#include <common/eventBus/EventBus.h>

namespace kakakv {
    namespace net {
        ASIOConnector::ASIOConnector(cluster::NodeId selfNodeId, std::shared_ptr<common::EventBus> eventBus,
                                     std::string listenIP, unsigned short listenPort) {

        }


        void ASIOConnector::initialize() throw(char *) {
            //1. 监听Selector
            this->selector->addListener(shared_from_this());
            //2. 启动Selector
            this->selector->start();
        }

        void ASIOConnector::close() {
            this->inboundChannelGroup->closeAll();
            this->outboundChannelGroup->closeAll();
            this->selector->shutdownGracefully();
            this->selector->removeListener(shared_from_this());
            if (!this->ioExecutorShared) {
                // 关闭IO线程池
                this->ioService->shutdownGracefully();
            }// 如果IO线程池被共享，则按约定由上层服务关闭
        }

        /**
         * 重置连接
         */
        void ASIOConnector::resetChannels() {
        }

        /**
         * 发送RequestVote给多个节点
         * @param requestVoteMessage
         * @param destinationEndpoints
         */
        void ASIOConnector::sendRequestVote(std::shared_ptr<message::RequestVote> requestVoteMessage,
                                            const std::vector<cluster::NodeEndpoint> destinationEndpoints) {
            for (auto endpoint: destinationEndpoints) {
                try {
                    this->getChannel(endpoint)->writeRequestVote(requestVoteMessage);
                } catch (...) {
                    // 打印日志：发送失败
                }
            }
        }

        /**
         * 回复RequestVote消息
         * @param destinationEndpoint
         */
        void ASIOConnector::replyRequestVote(std::shared_ptr<message::RequestVoteResponse> requestVoteResponseMessage,
                                             const cluster::NodeEndpoint destinationEndpoint) {
            try {
                this->getChannel(destinationEndpoint)->writeRequestVoteResponse(requestVoteResponseMessage);
            } catch (...) {
                // 打印日志：发送失败
            }
        }

        /**
         * 发送AppendEntries
         * @param appendEntriesMessage
         * @param destinationEndpoint
         */
        void ASIOConnector::sendAppendEntries(std::shared_ptr<message::AppendEntries> appendEntriesMessage,
                                              const cluster::NodeEndpoint destinationEndpoint) {
            try {
                this->getChannel(destinationEndpoint)->writeAppendEntries(appendEntriesMessage);
            } catch (...) {
                // 打印日志：发送失败
            }
        }

        void
        ASIOConnector::replyAppendEntries(std::shared_ptr<message::AppendEntriesResponse> appendEntriesResponseMessage,
                                          const cluster::NodeEndpoint destinationEndpoint) {
            try {
                this->getChannel(destinationEndpoint)->writeAppendEntriesResponse(appendEntriesResponseMessage);
            } catch (...) {
                // 打印日志：发送失败
            }
        }

        void ASIOConnector::onReceiveConnect(std::shared_ptr<ASIOChannel> channel) {
        }

        std::shared_ptr<ASIOChannel> ASIOConnector::getChannel(cluster::NodeEndpoint endpoint) {
            return this->outboundChannelGroup->getOrConnect(endpoint.nodeId, endpoint.endpoint);
        }
    }
}