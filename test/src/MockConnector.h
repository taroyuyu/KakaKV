//
// Created by 凌宇 on 2021/9/21.
//

#ifndef KAKAKV_MOCKCONNECTOR_H
#define KAKAKV_MOCKCONNECTOR_H

#include <net/core/Connector.h>
#include <list>
namespace kakakv{
    namespace test{
        class MockConnector:public net::Connector{
        public:
            /**
             * 初始化
             */
            void initialize()throw(char*)override;
            /**
             * 发送RequestVote给多个节点
             * @param requestVoteMessage
             * @param destinationEndpoints
             */
//            void sendRequestVote(std::shared_ptr<message::RequestVote> requestVoteMessage,const const std::vector<cluster::NodeEndpoint> destinationEndpoints)override;
            /**
             * 回复RequestVote消息
             * @param destinationEndpoint
             */
//            void replyRequestVote(std::shared_ptr<message::RequestVoteResponse> requestVoteResponseMessage,const cluster::NodeEndpoint destinationEndpoint)override;
            /**
             * 回复AppendEntries
             * @param appendEntriesMessage
             * @param destinationEndpoint
             */
//            void sendAppendEntries(std::shared_ptr<message::AppendEntries> appendEntriesMessage,const cluster::NodeEndpoint destinationEndpoint)override;
            /**
             * 重置连接
             */
            void resetChannels()override;
            /**
             * 关闭通信组件
             */
            void close()override;

        private:
            class Message{
            public:
                Message(cluster::NodeId destinationNodeId):destinationNodeId(destinationNodeId){

                }
                std::shared_ptr<message::Message> message;
                cluster::NodeId destinationNodeId;// 目标节点
                std::shared_ptr<message::Message> result;
                operator std::string(){
                    return "Message{}";
                }
            };
            std::list<std::shared_ptr<Message>> messageList;
        public:
            std::shared_ptr<Message> getLastMessage();
            std::shared_ptr<Message> getLastMessageOrDefault();
            std::shared_ptr<message::Message> getRPC();
            std::shared_ptr<message::Message> getResult();
            cluster::NodeId getDestinationNodeId();
            unsigned int getMessageCount();
            std::list<std::shared_ptr<Message>> getMessages();
            void clearMessage();
        };
    }
}


#endif //KAKAKV_MOCKCONNECTOR_H
