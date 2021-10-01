//
// Created by 凌宇 on 2021/10/1.
//

#include <service/implementation/Service.h>
#include <server/Node.h>
#include <server/AbstractSingleThreadStateMachine.h>
#include <service/command/GetCommandResponse.h>
#include <service/command/Redirect.h>
namespace kakakv {
    namespace service {

        namespace {
            class StateMachineImpl : public server::AbstractSingleThreadStateMachine {
            public:
                void applyCommand(std::string commandBytes)override;
            };
            void StateMachineImpl::applyCommand(std::string commandBytes){
                // TODO:根据commandBytes恢复命令
                std::shared_ptr<command::SetCommand> command;
                // TODO:修改数据
                // TODO:查找连接
                // TODO:发送处理响应
            }
        }

        Service::Service(std::shared_ptr<server::Node> node) {
            node->registerStateMachine(std::make_shared<StateMachineImpl>());
            this->node = node;
        }

        void Service::set(std::shared_ptr<CommandRequest<command::SetCommand>> commandRequest){
            // 如果当前节点不是Leader节点，则返回REDIRECT
            auto redirect = this->checkLeaderShip();
            if (!redirect){
                commandRequest->reply(redirect);
                return;
            }
            auto command = commandRequest->getCommand();
            // 记录请求ID和CommandRequest之间的映射
            {
                std::lock_guard<std::mutex> lock(this->pendingCommandsMutex);
                this->pendingCommands.insert({command->getRequestId(),commandRequest});
            }
            // 客户端连接关闭时从映射中移除
            commandRequest->addCloseListener([this](std::shared_ptr<CommandRequest<command::SetCommand>> commandRequest){
                std::lock_guard<std::mutex> lock(this->pendingCommandsMutex);
                this->pendingCommands.erase(commandRequest->getCommand()->getRequestId());
            });
            // 追加日志
            this->node->appendLog(command->toBytes());

        }
        void Service::get(std::shared_ptr<CommandRequest<command::GetCommand>> commandRequest){
            std::string key = commandRequest->getCommand()->getKey();
            auto valueIt = this->db.find(key);
            std::string value;
            bool success = valueIt != this->db.end();
            if (success){
                value = valueIt->second;
            }
            commandRequest->reply(std::make_shared<command::GetCommandResponse>(success,value));
        }

        std::shared_ptr<command::Redirect> Service::checkLeaderShip(){
            auto state = this->node->getRoleTypeAndLeaderId();
            if (state.first != server::Node::RoleType::Leader){
                return std::make_shared<command::Redirect>(state.second);
            }
            return nullptr;
        }

    }
}