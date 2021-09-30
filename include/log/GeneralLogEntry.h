//
// Created by 凌宇 on 2021/9/20.
//

#ifndef KAKAKV_GENERALLOGENTRY_H
#define KAKAKV_GENERALLOGENTRY_H

#include <iostream>
#include <utility>
#include <log/LogEntry.h>
namespace kakakv {
    namespace log {
        class GeneralLogEntry : public LogEntry {
            friend std::ostream &operator<<(std::ostream &cout, GeneralLogEntry &entry);

        public:
            GeneralLogEntry(unsigned int index, unsigned int term, std::unique_ptr<std::string> payload)
                    : LogEntry(index, term), payload(std::move(payload)){
            }

            const std::string & getPayload() {
                return *this->payload;
            }

        protected:
            /**
             * 日志的有效负载
             */
            std::unique_ptr<std::string> payload;
        };

        std::ostream &operator<<(std::ostream &cout, GeneralLogEntry &entry);
    }
}

#endif //KAKAKV_GENERALLOGENTRY_H
