//
// Created by 凌宇 on 2021/10/1.
//

#ifndef KAKAKV_COMMANDREQUEST_H
#define KAKAKV_COMMANDREQUEST_H

#include <memory>
#include <functional>
namespace kakakv {
    namespace net {
        class ASIOChannel;
    }
    namespace service {
        namespace command {
            class Command;

            class Response;
        }
    class CommandRequest:private std::enable_shared_from_this<CommandRequest>{
        public:
            CommandRequest(std::shared_ptr<command::Command> command,std::shared_ptr<net::ASIOChannel> channel);
            void reply(std::shared_ptr<command::Response> response);
            void addCloseListener(std::function<void(std::shared_ptr<CommandRequest> commandRequest)> callback);
            std::shared_ptr<const command::Command> getCommand();
        private:
            const std::shared_ptr<command::Command> command;
            const std::shared_ptr<net::ASIOChannel> channel;
        };
    }
}

#endif //KAKAKV_COMMANDREQUEST_H
