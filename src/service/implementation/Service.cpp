//
// Created by 凌宇 on 2021/10/1.
//

#include <service/implementation/Service.h>
#include <server/Node.h>
#include <server/StateMachine.h>
namespace kakakv {
    namespace service {

        namespace {
            class StateMachineImpl : public server::StateMachine {
                unsigned long long getLastApplied()override;
                void applyLog(std::shared_ptr<server::StateMachineContext> context,unsigned long long index,std::string commandBytes,unsigned long long firstLogIndex)override;
                void shutdown()override;
                void applyEntry(std::shared_ptr<log::LogEntry> entry) override;
            };

            unsigned long long StateMachineImpl::getLastApplied() {
            }

            void StateMachineImpl::applyLog(std::shared_ptr<server::StateMachineContext> context, unsigned long long index,
                                   std::string commandBytes, unsigned long long firstLogIndex) {
            }

            void StateMachineImpl::shutdown() {
            }

            void StateMachineImpl::applyEntry(std::shared_ptr<log::LogEntry> entry) {

            }
        }

        Service::Service(std::shared_ptr<server::Node> node) {
            node->registerStateMachine(std::make_shared<StateMachineImpl>());
            this->node = node;
        }
    }
}