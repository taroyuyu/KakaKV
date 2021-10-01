//
// Created by 凌宇 on 2021/10/1.
//

#ifndef KAKAKV_CLIENTSETLEADERCOMMAND_H
#define KAKAKV_CLIENTSETLEADERCOMMAND_H
#include <client/Command.h>
namespace kakakv {
    namespace client {
        class ClientSetLeaderCommand:public Command{
        public:
            std::string getName()override;
            void execute(std::string arguments,std::shared_ptr<CommandContext> context)override;
        };
    }
}


#endif //KAKAKV_CLIENTSETLEADERCOMMAND_H
