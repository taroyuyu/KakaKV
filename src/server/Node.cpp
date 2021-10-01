//
// Created by 凌宇 on 2021/9/20.
//

#include <server/Node.h>
#include <log/MemoryLogComponent.h>
#include <role/Follower.h>
#include <role/Leader.h>
#include <role/Candidate.h>
#include <server/events/ElectionTimeout.h>
#include <server/events/ReceiveAppendEntries.h>
#include <server/events/ReceiveAppendEntriesResult.h>
#include <server/events/ReceiveRequestVote.h>
#include <server/events/ReceiveRequestVoteResponse.h>
#include <server/StateMachine.h>
namespace kakakv {
    namespace server {
        Node::Node(std::shared_ptr<NodeContext> context) : logger(std::make_unique<log::MemoryLogComponent>()),
                                                           context(context), started(false), role(
                        nullptr) {

        }

        void Node::start() {
            // 如果已经启动，则直接跳过
            if (this->started.load()) {
                return;
            }
            // 注册自己到EventBus
            this->registerToEventBus();
            // 初始化连接器
            this->context->connector()->initialize();
            // 启动时为Follower角色
            auto store = this->context->mStore;
            this->changeToRole(std::make_shared<role::Follower>(store->getTerm(),store->getVotedFor(),cluster::NULLNodeId,this->scheduleElectionTimeOut()));
            this->started = true;
        }

        void Node::registerToEventBus() {
            this->context->mEventBus->registerEvent(event::ElectionTimeout::eventType(), this);
            this->context->mEventBus->registerEvent(event::ReceiveRequestVote::eventType(), this);
            this->context->mEventBus->registerEvent(event::ReceiveRequestVoteResponse::eventType(), this);
            this->context->mEventBus->registerEvent(event::ReceiveAppendEntries::eventType(), this);
            this->context->mEventBus->registerEvent(event::ReceiveAppendEntriesResult::eventType(), this);
        }

        void Node::unregisterToEventBus() {
            this->context->mEventBus->unregister(this);
        }

        void Node::onEvent(std::shared_ptr<const common::Event> event) {
            if (event->getEventType() == event::ElectionTimeout::eventType()) {
                this->onElectionTimeout();
            } else if (event->getEventType() == event::ReceiveRequestVote::eventType()) {

            } else if (event->getEventType() == event::ReceiveRequestVoteResponse::eventType()) {

            } else if (event->getEventType() == event::ReceiveAppendEntries::eventType()) {

            } else if (event->getEventType() == event::ReceiveAppendEntriesResult::eventType()) {

            }
        }

        void Node::onElectionTimeout() {

        }

        std::shared_ptr<task::ElectionTimeout> Node::scheduleElectionTimeOut(){
            return this->context->scheduler()->scheduleElectionTimeout(std::bind(&Node::onElectionTimeout,this));
        }

        std::shared_ptr<task::LogReplicationTask> Node::scheduleLogReplicationTask(){
            return this->context->scheduler()->scheduleLogReplicationTask(std::bind(&Node::replicateLog,this));
        }

        /**
         * 执行线程：IO线程
         * @param request
         */
        void Node::onReceiveRequestVote(std::shared_ptr<message::RequestVote> request) {

            // TODO:检查执行线程是否是IO线程

            if (!request) {
                assert(request);
                return;
            }

            // 创建任务
            auto task = [=] {
                auto response = this->doProcessRequestVote(request);
                if (!response)
                    return;
                auto target = this->context->mGroup.findMember(request->candidateId);
                if (!target) {
                    //查找失败：检查程序逻辑问题
                    return;
                }
                this->context->mConnector->replyRequestVote(response, target->endpoint);
            };
            // 提交到任务队列
            this->context->mTaskExecutor->post([=] {
                task();
            });
        }

        /**
         * 执行线程：IO线程
         * @param response
         */
        void Node::onReceiveRequestVoteResponse(std::shared_ptr<message::RequestVoteResponse> response) {

            // TODO:检查执行线程是否是IO线程

            if (!response) {
                assert(response);
                return;
            }

            // 创建任务
            auto task = [=] {
                this->doProcessRequestVoteResponse(response);
            };
            // 提交到任务队列
            this->context->mTaskExecutor->post([=] {
                task();
            });
        }

        /**
         * 执行线程：IO线程
         * @param request
         */
        void Node::onReceiveAppendEntries(std::shared_ptr<message::AppendEntries> request) {

            // TODO:检查执行线程是否是IO线程

            if (!request) {
                assert(request);
                return;
            }

            // 创建任务
            auto task = [=] {
                auto response = this->doProcessAppendEntries(request);
                if (!response)
                    return;
                auto target = this->context->mGroup.findMember(request->leaderId);
                if (!target) {
                    //查找失败：检查程序逻辑问题
                    return;
                }
                this->context->mConnector->replyAppendEntries(response, target->endpoint);
            };
            // 提交到任务队列
            this->context->mTaskExecutor->post([=] {
                task();
            });
        }

        /**
         * 执行线程：IO线程
         * @param response
         */
        void Node::onReceiveAppendEntriesResult(std::shared_ptr<message::AppendEntriesResponse> response) {
            // TODO:检查执行线程是否是IO线程

            if (!response) {
                assert(response);
                return;
            }

            // 创建任务
            auto task = [=] {
                this->doProcessAppendEntriesResult(response);
            };
            // 提交到任务队列
            this->context->mTaskExecutor->post([=] {
                task();
            });
        }

        /**
         * 执行线程：任务线程
         * @param newRole
         */
        void Node::changeToRole(std::shared_ptr<role::Role> newRole) {

            // TODO:检查执行线程是否任务线程

            if (!newRole) {
                assert(newRole);
                return;
            }

            // 保存新的角色状态
            auto store = this->context->mStore;
            store->setTerm(newRole->getTerm());
            if (typeid(newRole.get()) == typeid(role::Follower *)) {
                auto follower = std::dynamic_pointer_cast<role::Follower>(newRole);
                store->setVotedFor(follower->getVotedFor());
            }
            // 更新角色
            this->role = newRole;
        }

        /**
         * 执行线程：任务线程
         */
        void Node::doProcessElectionTimeout() {

            // TODO:检查执行线程是否任务线程

            // Leader角色下不可能有选举超时
            if (typeid(this->role.get()) == typeid(role::Leader *)) {
                return;
            }
            // 对于follower节点来说是发起选举
            // 对于candidate节点来说是再次发起选举
            // 选举term + 1
            unsigned long long newTerm = this->role->getTerm() + 1;
            // 取消定时任务
            this->role->cancelTimeoutOrTask();
            // TODO:切换成Candidate角色
            // 发送RequestVote消息
            auto requestVoteMessage = std::make_shared<message::RequestVote>(newTerm, this->context->selfId(), 0, 0);
            std::vector<cluster::NodeEndpoint> destinationEndpoints;
            for (auto mem: this->context->mGroup.listReplicationTarget()) {
                destinationEndpoints.push_back(mem->endpoint);
            }
            this->context->connector()->sendRequestVote(requestVoteMessage, destinationEndpoints);
        }

        /**
         * 处理RequestVote
         * 执行线程：任务线程
         * @param request
         */
        std::shared_ptr<message::RequestVoteResponse>
        Node::doProcessRequestVote(const std::shared_ptr<message::RequestVote> request) {

            // TODO:检查执行线程是否任务线程

            if (!request) {
                assert(request);
                return nullptr;
            }
            // 如果对方的term比自己的小，则不投票并且返回自己的term给对方
            if (request->term < this->role->getTerm()) {
                // 发送消息
                return std::make_shared<message::RequestVoteResponse>(this->role->getTerm(), this->context->selfId(),
                                                                      false);
            }

            // 比较当前节点中最后一条日志与消息中的最后一条日志的元信息
            bool voteForCandidate = !(this->context->mLog->isNewerThan(request->lastLogIndex, request->lastLogTerm));

            // 如果对方的term比自己大，则切换为Follower角色
            if (request->term > this->role->getTerm()) {
                this->becomeFollower(request->term, (voteForCandidate ? request->candidateId : cluster::NULLNodeId),
                                     cluster::NULLNodeId, true);
                return std::make_shared<message::RequestVoteResponse>(request->term, this->context->selfId(),
                                                                      voteForCandidate);
            }

            // 本地的term与消息的term一致
            if (typeid(this->role.get()) == typeid(role::Follower *)) {
                std::shared_ptr<role::Follower> follower = std::dynamic_pointer_cast<role::Follower>(this->role);
                cluster::NodeId votedFor = follower->getVotedFor();
                /**
                 * 以下两种情况投票
                 * case 1.自己尚未投过票，并且对方的日志比自己新
                 * case 2.自己已经给对方投过票
                 */
                if ((votedFor == cluster::NULLNodeId && voteForCandidate)//case1
                    || votedFor == request->candidateId) {//case2.
                    this->becomeFollower(request->term, request->candidateId, cluster::NULLNodeId, true);
                    return std::make_shared<message::RequestVoteResponse>(this->role->getTerm(),
                                                                          this->context->selfId(), true);
                }
                return std::make_shared<message::RequestVoteResponse>(this->role->getTerm(), this->context->selfId(),
                                                                      false);
            } else if (typeid(this->role.get()) == typeid(role::Candidate)) {//已经给自己投过票，所以不会给其它节点投票
                return std::make_shared<message::RequestVoteResponse>(this->role->getTerm(), this->context->selfId(),
                                                                      false);
            } else if (typeid(this->role.get()) == typeid(role::Leader *)) {
                return std::make_shared<message::RequestVoteResponse>(this->role->getTerm(), this->context->selfId(),
                                                                      false);
            } else {
                assert(false);
                return nullptr;
            }
        }

        /**
         * 执行线程：任务线程
         * @param response
         */
        void Node::doProcessRequestVoteResponse(const std::shared_ptr<message::RequestVoteResponse> response) {

            // TODO:检查执行线程是否任务线程

            if (!response) {
                assert(response);
                return;
            }
            if (response->term > this->role->getTerm()) {
                this->becomeFollower(response->term, cluster::NULLNodeId, cluster::NULLNodeId, true);
                return;
            }

            // 如果自己不是Candidate角色，则忽略
            if (typeid(this->role.get()) != typeid(role::Candidate *)) {
                return;
            }

            // 如果对方的Term比自己小或者对方没有给自己投票，则忽略
            if (response->term < this->role->getTerm() || response->voteGranted == false) {
                return;
            }

            // 更新当前票数
            auto candidate = std::dynamic_pointer_cast<role::Candidate>(this->role);
            int currentVotesCount = candidate->getVotesCount() + 1;
            // 获取节点数
            int countOfMajor = this->context->mGroup.listReplicationTarget().size() + 1;
            // 取消选举超时定时器
            this->role->cancelTimeoutOrTask();
            if (currentVotesCount > countOfMajor/2){// 票数过半
                // 成为Leader角色
                this->changeToRole(std::make_shared<role::Leader>(this->role->getTerm(),this->scheduleLogReplicationTask()));
            }else{
                // 修改收到的票数，并重新创建选举超时定时器
                this->changeToRole(std::make_shared<role::Candidate>(this->role->getTerm(),this->scheduleElectionTimeOut(),currentVotesCount));
            }
        }

        /**
         * 执行线程：任务线程
         * @param appendEntriesMessage
         * @return
         */
        std::shared_ptr<message::AppendEntriesResponse>
        Node::doProcessAppendEntries(const std::shared_ptr<message::AppendEntries> appendEntriesMessage) {

            // TODO:检查执行线程是否任务线程

            if (!appendEntriesMessage) {
                assert(appendEntriesMessage);
                return nullptr;
            }

            // 如果对方的Term比自己小，则回复自己的Term
            if (appendEntriesMessage->term < this->role->getTerm()) {
                return std::make_shared<message::AppendEntriesResponse>(this->role->getTerm(), this->context->selfId(),
                                                                        false);
            }
            // 如果对方的Term比自己大，则退化为Follower角色
            if (appendEntriesMessage->term > this->role->getTerm()) {
                // 设置LeaderId并重置选举定时器
                this->becomeFollower(appendEntriesMessage->term, cluster::NULLNodeId, appendEntriesMessage->leaderId,
                                     true);
                // 尝试追加日志
                auto appendingResult = this->appendEntries(appendEntriesMessage);
                return std::make_shared<message::AppendEntriesResponse>(appendEntriesMessage->term,
                                                                        this->context->selfId(), appendingResult);
            }

            assert(appendEntriesMessage->term == this->role->getTerm());
            if (typeid(this->role.get()) == typeid(role::Follower *)) {
                auto follower = std::dynamic_pointer_cast<role::Follower>(this->role);
                // 设置LeaderId并重置选举定时器
                this->becomeFollower(appendEntriesMessage->term, follower->getVotedFor(),
                                     appendEntriesMessage->leaderId, true);
                // 尝试追加日志
                auto appendingResult = this->appendEntries(appendEntriesMessage);
                return std::make_shared<message::AppendEntriesResponse>(appendEntriesMessage->term,
                                                                        this->context->selfId(), appendingResult);
            } else if (typeid(this->role.get()) == typeid(role::Candidate *)) {
                // 设置LeaderId并重置选举定时器
                this->becomeFollower(appendEntriesMessage->term, cluster::NULLNodeId, appendEntriesMessage->leaderId,
                                     true);
                // 尝试追加日志
                auto appendingResult = this->appendEntries(appendEntriesMessage);
                return std::make_shared<message::AppendEntriesResponse>(appendEntriesMessage->term,
                                                                        this->context->selfId(), appendingResult);
            } else if (typeid(this->role.get()) == typeid(role::Leader *)) {
                return std::make_shared<message::AppendEntriesResponse>(appendEntriesMessage->term,
                                                                        this->context->selfId(), false);
            } else {
                assert(false);
                return nullptr;
            }
        }

        /**
         * 执行线程：任务线程
         * @param response
         */
        void Node::doProcessAppendEntriesResult(const std::shared_ptr<message::AppendEntriesResponse> response) {

            // TODO:检查执行线程是否任务线程

            if (!response) {
                assert(response);
                return;
            }
            // 如果对方的Term比自己大，则退化为Follower角色
            if (response->term > this->role->getTerm()) {
                this->becomeFollower(response->term, cluster::NULLNodeId, cluster::NULLNodeId, true);
                return;
            }
            // 检查自己的角色
            if (typeid(this->role.get()) != typeid(role::Leader *)) {
                return;
            }
        }

        /**
         * 执行线程：任务线程
         * @param term
         * @param votedFor
         * @param leaderId
         * @param scheduleElectionTimeout
         */
        void Node::becomeFollower(unsigned long long term, cluster::NodeId votedFor, cluster::NodeId leaderId,
                                  bool scheduleElectionTimeout) {
            // TODO:检查执行线程是否任务线程
            // 取消超时或者定时器
            this->role->cancelTimeoutOrTask();

            // 重新创建选举超时定时器或者空定时器
            std::shared_ptr<task::ElectionTimeout> electionTimeout = scheduleElectionTimeout ? this->scheduleElectionTimeOut(): nullptr;
            this->changeToRole(std::make_shared<role::Follower>(term,votedFor,leaderId,electionTimeout));
        }

        /**
         * 执行线程：定时器线程
         */
        void Node::replicateLog() {

            // 检查执行线程是否是定时器线程

            // 创建任务
            auto task = [=] {
                this->doReplicateLog();
            };
            // 提交到任务队列
            this->context->mTaskExecutor->post([=] {
                task();
            });
        }

        /**
         * 执行线程：任务线程
         */
        void Node::doReplicateLog() {

            // TODO:检查执行线程是否任务线程

            // 给日志复制对象节点发送AppendEntries消息
            for (auto member: this->context->mGroup.listReplicationTarget()) {
                this->doReplicateLog(member);
            }
        }

        /**
         * 执行线程：任务线程
         * @param groupMember
         */
        void Node::doReplicateLog(const std::shared_ptr<cluster::GroupMember> groupMember) {

            // TODO:检查执行线程是否任务线程

            if (!groupMember) {
                assert(groupMember);
                return;
            }

            // 创建消息
            auto appendEntriesMessage = std::make_shared<message::AppendEntries>(this->role->getTerm(),
                                                                                 this->context->selfId());
            // TODO:添加待复制的消息
            appendEntriesMessage->prevLogIndex = 0;
            appendEntriesMessage->prevLogTerm = 0;
            appendEntriesMessage->leaderCommitIndex = 0;
            // 发送消息
            this->context->connector()->sendAppendEntries(appendEntriesMessage, groupMember->endpoint);
        }

        /**
         * 执行线程：任务线程
         * @param appendEntriesMessage
         * @return
         */
        bool Node::appendEntries(const std::shared_ptr<message::AppendEntries> appendEntriesMessage) {

            // TODO:检查执行线程是否任务线程

            if (!appendEntriesMessage) {
                assert(appendEntriesMessage);
                return false;
            }

            // 追加来自Leader的日志条目
            bool result = this->context->mLog->appendEntriesFromLeader(appendEntriesMessage->prevLogIndex,
                                                                       appendEntriesMessage->prevLogTerm,
                                                                       appendEntriesMessage->entryList);
            // 如果追加成功，则根据Leader节点的commitIndex决定是否推进当前节点的commitIndex
            if (result) {
                unsigned long long lastEntryIndex = appendEntriesMessage->prevLogIndex;
                if (appendEntriesMessage->entryList.size() > 0) {
                    lastEntryIndex = appendEntriesMessage->entryList[appendEntriesMessage->entryList.size() -
                                                                     1]->getIndex();
                }
                unsigned long long newCommitIndex = std::min(appendEntriesMessage->leaderCommitIndex, lastEntryIndex);
                this->context->mLog->advanceCommitIndex(newCommitIndex, appendEntriesMessage->term);
            }
            return result;
        }

        void Node::registerStateMachine(std::shared_ptr<StateMachine> stateMachine){
            this->stateMachine = stateMachine;
        }

        void Node::advanceCommitIndex(){
//            this->stateMachine->apply()
        }
    }
}