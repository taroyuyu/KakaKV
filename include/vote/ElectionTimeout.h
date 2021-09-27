//
// Created by 凌宇 on 2021/9/20.
//

#ifndef KAKAKV_ELECTIONTIMEOUT_H
#define KAKAKV_ELECTIONTIMEOUT_H

#include <iostream>

namespace kakakv{
    namespace vote{
        struct ElectionTimeout{
        };
        std::ostream & operator<<(std::ostream & cout,const ElectionTimeout & electionTimeout);
    }
}

#endif //KAKAKV_ELECTIONTIMEOUT_H
