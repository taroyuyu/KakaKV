//
// Created by 凌宇 on 2021/10/1.
//

#ifndef KAKAKV_COMMAND_H
#define KAKAKV_COMMAND_H
#include <string>
#include <memory>
namespace kakakv {
    namespace client {

        class CommandContext;

        class Command {
        public:
            virtual ~Command() = 0;
            virtual std::string getName() = 0;
            virtual void execute(std::string arguments,std::shared_ptr<CommandContext> context) = 0;
        };
    }
}


#endif //KAKAKV_COMMAND_H
