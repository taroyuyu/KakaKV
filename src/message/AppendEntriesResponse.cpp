//
// Created by 凌宇 on 2021/9/20.
//

#include <message/AppendEntriesResponse.h>

namespace kakakv {
    namespace message {
        std::ostream & operator<<(std::ostream & cout,const AppendEntriesResponse & response){
            cout<<"AppendEntriesResponse{followerId="<<response.followerId
                <<",term="<<response.term
                <<",success="<<response.success
                <<"}";
            return cout;
        }
    }
}