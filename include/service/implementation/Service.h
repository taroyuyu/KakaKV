//
// Created by 凌宇 on 2021/10/1.
//

#ifndef KAKAKV_SERVICE_H
#define KAKAKV_SERVICE_H
#include <map>
#include <mutex>
namespace kakakv {
    namespace server {
        class Node;
        class StateMachineContext;
    }
    namespace service {
        class CommandRequest;
        class Service :public std::enable_shared_from_this<Service> {
        public:
            Service(std::shared_ptr<server::Node> node);
        private:
            std::shared_ptr<server::Node> node;
            std::map<std::string,std::shared_ptr<CommandRequest>> pendingCommands;
            std::mutex pendingCommandsMutex;
            std::map<std::string,std::string> map;
        };
    }
}


#endif //KAKAKV_SERVICE_H
