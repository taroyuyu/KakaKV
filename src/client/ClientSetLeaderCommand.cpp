//
// Created by 凌宇 on 2021/10/1.
//

#include <client/ClientSetLeaderCommand.h>
#include <client/CommandContext.h>
namespace kakakv {
    namespace client {
        std::string ClientSetLeaderCommand::getName(){
            return "client-set-leader";
        }
        void ClientSetLeaderCommand::execute(std::string arguments,std::shared_ptr<CommandContext> context){
            // 判断后序参数是否为空
            if (arguments.empty()){
                throw "usage: "+this->getName()+" <node-id>";
            }
            // 设置新的Leader节点
            cluster::NodeId nodeId(arguments);
            try {
                context->setClientLeader(nodeId);
            } catch (...) {

            }
        }
    }
}