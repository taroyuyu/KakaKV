//
// Created by 凌宇 on 2021/10/1.
//

#include <client/Client.h>
#include <client/ServerRouter.h>
namespace kakakv {
    namespace client {
        const std::string Client::VERSION = "0.0.1";
        Client::Client(std::shared_ptr<ServerRouter> serverRouter):
        serverRouter(serverRouter){

        }

        void Client::addNode(cluster::NodeId nodeId,std::string host,unsigned short port){
//            this->serverRouter-send(std::make_shared<AddNodeCommand>(nodeId,host,port));
        }

        void Client::removeNode(cluster::NodeId nodeId){
//            this->serverRouter->send(std::make_shared<RemoveNodeCommand>(nodeId));
        }

        void Client::set(std::string key,std::string value){
//            this->serverRouter->send(std::make_shared<SetCommand>(key,value));
        }

        std::string Client::get(std::string key){
//            return this->serverRouter->send(std::make_shared<GetCommand>(key));
        }

        std::shared_ptr<const ServerRouter> Client::getServerRouter(){
            return this->serverRouter;
        }
    }
}