//
// Created by 凌宇 on 2021/10/1.
//

#ifndef KAKAKV_CLIENT_H
#define KAKAKV_CLIENT_H
#include <string>
#include <memory>
#include <cluster/NodeId.h>
namespace kakakv{
    namespace client{
        class ServerRouter;
        class Client {
        public:
            static const std::string VERSION;
            Client(std::shared_ptr<ServerRouter> serverRouter);
            void addNode(cluster::NodeId nodeId,std::string host,unsigned short port);
            void removeNode(cluster::NodeId nodeId);
            void set(std::string key,std::string value);
            std::string get(std::string key);
            std::shared_ptr<const ServerRouter> getServerRouter();
        private:
            std::shared_ptr<ServerRouter> serverRouter;
        };
    }
}


#endif //KAKAKV_CLIENT_H
