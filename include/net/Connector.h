//
// Created by 凌宇 on 2021/9/20.
//

#ifndef KAKAKV_CONNECTOR_H
#define KAKAKV_CONNECTOR_H

#include <cluster/NodeEndpoint.h>
#include <vector>
#include <memory>
namespace kakakv{

    namespace message{
        class Message;
        class AppendEntries;
        class AppendEntriesResponse;
        class RequestVote;
        class RequestVoteResponse;
    }

    namespace net{
        class Connector {
        public:
            Connector() = default;
            virtual virtual ~Connector() = 0;
            /**
             * 初始化
             */
            virtual void initialize()throw(char*) = 0;
            /**
             * 发送RequestVote给多个节点
             * @param requestVoteMessage
             * @param destinationEndpoints
             */
            virtual void sendRequestVote(std::shared_ptr<message::RequestVote> requestVoteMessage,const std::vector<cluster::NodeEndpoint> destinationEndpoints) = 0;
            /**
             * 回复RequestVote消息
             * @param destinationEndpoint
             */
            virtual void replyRequestVote(std::shared_ptr<message::RequestVoteResponse> requestVoteResponseMessage,const cluster::NodeEndpoint destinationEndpoint) = 0;
            /**
             * 发送AppendEntries
             * @param appendEntriesMessage
             * @param destinationEndpoint
             */
            virtual void sendAppendEntries(std::shared_ptr<message::AppendEntries> appendEntriesMessage,const cluster::NodeEndpoint destinationEndpoint) = 0;
            virtual void replyAppendEntries(std::shared_ptr<message::AppendEntriesResponse> appendEntriesResponseMessage,const cluster::NodeEndpoint destinationEndpoint) = 0;
            /**
             * 重置连接
             */
            virtual void resetChannels() = 0;
            /**
             * 关闭通信组件
             */
            virtual void close() = 0;
        };
    }
}


#endif //KAKAKV_CONNECTOR_H
