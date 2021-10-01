//
// Created by 凌宇 on 2021/10/1.
//

#include <service/implementation/CommandRequest.h>
#include <net/ASIOChannel.h>
namespace kakakv{
    namespace service{
        CommandRequest::CommandRequest(std::shared_ptr<command::Command> command,std::shared_ptr<net::ASIOChannel> channel):
        command(command),channel(channel){

        }

        void CommandRequest::reply(std::shared_ptr<command::Response> response){
        }

        void CommandRequest::addCloseListener(std::function<void(std::shared_ptr<CommandRequest> commandRequest)> callback){
            this->channel->addCloseCallback([callback,this](std::shared_ptr<net::Channel> channel){
                callback(this->shared_from_this());
            });
        }

        std::shared_ptr<const command::Command> CommandRequest::getCommand(){
            return this->command;
        }

    }
}