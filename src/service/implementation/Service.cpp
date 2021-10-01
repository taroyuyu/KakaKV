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

        unsigned long long Service::getLastApplied(){
        }
        void Service::applyLog(std::shared_ptr<server::StateMachineContext> context,unsigned long long index,std::string commandBytes,unsigned long long firstLogIndex){
        }
        void Service::shutdown(){
        }
        void Service::applyEntry(std::shared_ptr<log::LogEntry> entry){

        }
    }
}