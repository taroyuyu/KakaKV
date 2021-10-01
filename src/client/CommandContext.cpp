//
// Created by 凌宇 on 2021/10/1.
//

#include <client/CommandContext.h>
#include <client/Client.h>
#include <client/ServerRouter.h>
namespace kakakv {
    namespace client {
        CommandContext::CommandContext(std::map<cluster::NodeId,net::Endpoint> serverMap)
        :serverMap(serverMap),client(std::make_shared<Client>(buildServerRouter(serverMap))),running(false){
        }

        std::shared_ptr<ServerRouter> CommandContext::buildServerRouter(std::map<cluster::NodeId,net::Endpoint> serverMap){
            //auto router = std::make_shared<ServerRouter>();
            for(auto item : serverMap){
//                router->add(item->first,)
            }
//            return router;
        }

        void CommandContext::setClientLeader(cluster::NodeId nodeId){
//            this->client->getServerRouter()->setLeaderId(nodeId);
        }

    }
}