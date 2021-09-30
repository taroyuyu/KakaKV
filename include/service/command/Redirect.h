//
// Created by 凌宇 on 2021/9/30.
//

#ifndef KAKAKV_REDIRECT_H
#define KAKAKV_REDIRECT_H
#include <cluster/NodeId.h>
namespace kakakv {
    namespace service {
        namespace command {
            class Redirect {
            public:
                Redirect(cluster::NodeId leaderId):leaderId(leaderId){
                }
                cluster::NodeId getLeaderId(){
                    return this->leaderId;
                }
            private:
                cluster::NodeId leaderId;
            };

        }
    }
}


#endif //KAKAKV_REDIRECT_H
