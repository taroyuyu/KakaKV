//
// Created by 凌宇 on 2021/9/21.
//

#ifndef KAKAKV_NODEIMPLTEST_H
#define KAKAKV_NODEIMPLTEST_H

#include <server//NodeBuilder.h>
#include <iostream>
#include <net/ASIOConnector.h>
namespace kakakv {
    namespace test {
        class NodeImplTest {
        public:
            void testStart(){
                std::cout << "Hello, World!" << std::endl;
            }
        };
    }
}

#endif //KAKAKV_NODEIMPLTEST_H
