//
// Created by 凌宇 on 2021/9/21.
//

#include <message/RequestVote.h>
#include <message/RequestVoteResponse.h>
#include <message/AppendEntries.h>
#include <message/AppendEntriesResponse.h>
#include "MockConnector.h"

namespace kakakv {
    namespace test {
        void MockConnector::initialize()throw(char*){
        }

//        void MockConnector::sendRequestVote(std::shared_ptr<message::RequestVote> requestVoteMessage,const std::vector<cluster::NodeEndpoint> destinationEndpoints){
//            for (auto destination : destinationEndpoints){
//                auto m = std::make_shared<Message>(destination.nodeId);
//                m->message = requestVoteMessage;
//                this->messageList.push_back(m);
//            }
//        }


//        void MockConnector::replyRequestVote(std::shared_ptr<message::RequestVoteResponse> requestVoteResponseMessage,const cluster::NodeEndpoint destinationEndpoint){
//            auto m = std::make_shared<Message>(destinationEndpoint.nodeId);
//            m->result = requestVoteResponseMessage;
//            this->messageList.push_back(m);
//        }

//        void MockConnector::sendAppendEntries(std::shared_ptr<message::AppendEntries> appendEntriesMessage,const cluster::NodeEndpoint destinationEndpoint){
//            auto m = std::make_shared<Message>(destinationEndpoint.nodeId);
//            m->message = appendEntriesMessage;
//            this->messageList.push_back(m);
//        }

        void MockConnector::resetChannels(){
        }

        void MockConnector::close(){

        }

        std::shared_ptr<MockConnector::Message> MockConnector::getLastMessage(){

            return this->messageList.empty() ? nullptr : this->messageList.back();
        }
        std::shared_ptr<MockConnector::Message> MockConnector::getLastMessageOrDefault(){
            auto emptyMessage = std::make_shared<MockConnector::Message>(cluster::NULLNodeId);
            return this->messageList.empty() ? emptyMessage : this->messageList.back();
        }
        std::shared_ptr<message::Message> MockConnector::getRPC(){
            return this->getLastMessageOrDefault()->message;
        }
        std::shared_ptr<message::Message> MockConnector::getResult(){
            return this->getLastMessageOrDefault()->result;
        }
        cluster::NodeId MockConnector::getDestinationNodeId(){
            return this->getLastMessageOrDefault()->destinationNodeId;
        }
        unsigned int MockConnector::getMessageCount(){
            return this->messageList.size();
        }
        std::list<std::shared_ptr<MockConnector::Message>> MockConnector::getMessages(){
            return this->messageList;
        }
        void MockConnector::clearMessage(){
            this->messageList.clear();
        }
    }
}