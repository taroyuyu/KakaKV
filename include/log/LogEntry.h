//
// Created by 凌宇 on 2021/9/20.
//

#ifndef KAKAKV_LOGENTRY_H
#define KAKAKV_LOGENTRY_H
namespace kakakv {
    namespace log {
        class LogEntry {
        public:
            /**
             * 获取日志的索引
             * @return
             */
            unsigned int getIndex() const {
                return this->index;
            }

            /**
             * 获取日志产生时的纪元
             * @return
             */
            unsigned int getTerm() const {
                return this->term;
            }

        protected:
            LogEntry(unsigned int index, unsigned int term) : index(index), term(term) {
            }

            virtual ~LogEntry() {
            }

            /**
             * 日志的索引
             */
            const unsigned int index;
            /**
             * 日志产生时的纪元
             */
            const unsigned int term;
        };
    }
}
#endif //KAKAKV_LOGENTRY_H
