//
// Created by 凌宇 on 2021/10/1.
//

#ifndef KAKAKV_COMMANDCONTEXT_H
#define KAKAKV_COMMANDCONTEXT_H
#include <map>
#include <cluster/NodeId.h>
#include <net/core/Endpoint.h>
#include <memory>
namespace kakakv {
    namespace client {
        class Client;
        class ServerRouter;
        class CommandContext {
        public:
            CommandContext(std::map<cluster::NodeId,net::Endpoint> serverMap);
            void setClientLeader(cluster::NodeId nodeId);
        private:
            static std::shared_ptr<ServerRouter> buildServerRouter(std::map<cluster::NodeId,net::Endpoint> serverMap);
            std::map<cluster::NodeId,net::Endpoint> serverMap;
            std::shared_ptr<Client> client;
            bool running;
        };
    }
}


#endif //KAKAKV_COMMANDCONTEXT_H
