//
// Created by 凌宇 on 2021/10/1.
//

#ifndef KAKAKV_SERVICE_H
#define KAKAKV_SERVICE_H

#include <server/StateMachine.h>

namespace kakakv {
    namespace server {
        class Node;
        class StateMachineContext;
    }
    namespace service {
        class Service : public server::StateMachine, public std::enable_shared_from_this<Service> {
        public:
            Service(std::shared_ptr<server::Node> node);
            unsigned long long getLastApplied()override;
            void applyLog(std::shared_ptr<server::StateMachineContext> context,unsigned long long index,std::string commandBytes,unsigned long long firstLogIndex)override;
            void shutdown()override;
            void applyEntry(std::shared_ptr<log::LogEntry> entry) override;
        };
    }
}


#endif //KAKAKV_SERVICE_H
