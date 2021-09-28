//
// Created by 凌宇 on 2021/9/28.
//

#include <server/RaftMessageHandler.h>
#include <message/RequestVote.h>
#include <message/RequestVoteResponse.h>
#include <message/AppendEntries.h>
#include <message/AppendEntriesResponse.h>
#include <server/events/ElectionTimeout.h>
#include <server/events/ReceiveAppendEntries.h>
#include <server/events/ReceiveAppendEntriesResult.h>
#include <server/events/ReceiveRequestVote.h>
#include <server/events/ReceiveRequestVoteResponse.h>

namespace kakakv {
    namespace server {
        RaftMessageHandler::RaftMessageHandler(std::shared_ptr<common::EventBus> eventBus) :
                mEventBus(eventBus) {
        }

        void RaftMessageHandler::channelRead(std::weak_ptr<const net::Channel> channel,
                                             std::shared_ptr<net::Message> message) {
            if (!this->mEventBus)
                return;
            if (typeid(message.get()) == typeid(message::RequestVote *)) {
                auto requestVoteMessage = std::dynamic_pointer_cast<message::RequestVote>(message);
                assert(requestVoteMessage);
                this->mEventBus->Post(std::make_shared<event::ReceiveRequestVote>(requestVoteMessage));
            } else if (typeid(message.get()) == typeid(message::RequestVoteResponse *)) {
                auto requestVoteResponseMessage = std::dynamic_pointer_cast<message::RequestVoteResponse>(message);
                assert(requestVoteResponseMessage);
                this->mEventBus->Post(std::make_shared<event::ReceiveRequestVoteResponse>(requestVoteResponseMessage));
            } else if (typeid(message.get()) == typeid(message::AppendEntries *)) {
                auto appendEntriesMessage = std::dynamic_pointer_cast<message::AppendEntries>(message);
                assert(appendEntriesMessage);
                this->mEventBus->Post(std::make_shared<event::ReceiveAppendEntries>(appendEntriesMessage));
            } else if (typeid(message.get()) == typeid(message::AppendEntriesResponse *)) {
                auto appendEntriesResponseMessage = std::dynamic_pointer_cast<message::AppendEntriesResponse>(message);
                assert(appendEntriesResponseMessage);
                this->mEventBus->Post(std::make_shared<event::ReceiveAppendEntriesResult>(appendEntriesResponseMessage));
            }
        }
    }
}