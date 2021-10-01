//
// Created by 凌宇 on 2021/10/1.
//

#ifndef KAKAKV_COMMANDREQUEST_H
#define KAKAKV_COMMANDREQUEST_H

#include <memory>
#include <functional>
#include <net/ASIOChannel.h>

namespace kakakv {
    namespace service {
        namespace command {
            class Command;

            class Response;
        }

        class CommandRequestBase{
        public:
            virtual ~CommandRequestBase() = 0;
        };

        template<typename CommandType>
        class CommandRequest : public CommandRequestBase,private std::enable_shared_from_this<CommandRequest<CommandType>> {
        public:
            CommandRequest(std::shared_ptr<CommandType> command, std::shared_ptr<net::ASIOChannel> channel) :
                    command(command), channel(channel) {

            }

            void reply(std::shared_ptr<command::Response> response) {

            }

            void addCloseListener(
                    std::function<void(std::shared_ptr<CommandRequest<CommandType>> commandRequest)> callback) {
                this->channel->addCloseCallback([callback, this](std::shared_ptr<net::Channel> channel) {
                    callback(this->shared_from_this());
                });
            }

            std::shared_ptr<const CommandType> getCommand() {
                return this->command;
            }

        private:
            const std::shared_ptr<CommandType> command;
            const std::shared_ptr<net::ASIOChannel> channel;
        };
    }
}

#endif //KAKAKV_COMMANDREQUEST_H
