//
// Created by 凌宇 on 2021/10/1.
//

#ifndef KAKAKV_SERVICE_H
#define KAKAKV_SERVICE_H

#include <server/StateMachine.h>

namespace kakakv {
    namespace server {
        class Node;
    }
    namespace service {
        class Service : public server::StateMachine, public std::enable_shared_from_this<Service> {
            Service(std::shared_ptr<server::Node> node);

            void apply(std::shared_ptr<log::LogEntry> entry) override;
        };
    }
}


#endif //KAKAKV_SERVICE_H
