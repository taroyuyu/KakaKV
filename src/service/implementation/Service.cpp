//
// Created by 凌宇 on 2021/10/1.
//

#include <service/implementation/Service.h>
#include <server/Node.h>
namespace kakakv {
    namespace service {
        Service::Service(std::shared_ptr<server::Node> node){
            node->registerStateMachine(this->shared_from_this());
        }

        void Service::apply(std::shared_ptr<log::LogEntry> entry){

        }
    }
}