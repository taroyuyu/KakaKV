//
// Created by 凌宇 on 2021/10/1.
//

#ifndef KAKAKV_SERVICE_H
#define KAKAKV_SERVICE_H

#include <map>
#include <mutex>
#include <service/command/GetCommand.h>
#include <service/command/SetCommand.h>
#include <service/implementation/CommandRequest.h>
namespace kakakv {
    namespace server {
        class Node;

        class StateMachineContext;
    }
    namespace service {
        namespace command {
            class Redirect;
        }

        class Service : public std::enable_shared_from_this<Service> {
        public:
            Service(std::shared_ptr<server::Node> node);

        private:
            void set(std::shared_ptr<CommandRequest<command::SetCommand>> commandRequest);
            void get(std::shared_ptr<CommandRequest<command::GetCommand>> commandRequest);
            /**
             * 检查当前节点是不是Leader节点
             * @return
             */
            std::shared_ptr<command::Redirect> checkLeaderShip();
            std::shared_ptr<server::Node> node;
            std::map<std::string, std::shared_ptr<CommandRequestBase>> pendingCommands;
            std::mutex pendingCommandsMutex;
            std::map<std::string, std::string> db;
        };
    }
}


#endif //KAKAKV_SERVICE_H
