cmake_minimum_required(VERSION 3.19)
project(KakaKV)

set(CMAKE_CXX_STANDARD 14)

# Boost库配置相关
find_package(Boost 1.76.0 REQUIRED COMPONENTS system thread chrono)
include_directories(${Boost_INCLUDE_DIRS})

include_directories(include)

find_package(protobuf CONFIG REQUIRED)
add_library(Server src/server/MemoryNodeStore.cpp src/server/Node.cpp src/server/NodeBuilder.cpp src/server/NodeContext.cpp src/server/NodeStore.cpp src/server/RaftMessageHandler.cpp src/server/Scheduler.cpp)
add_library(NetWork src/net/core/AbstractHandler.cpp src/net/core/Channel.cpp src/net/core/Connector.cpp src/net/core/Decoder.cpp src/net/core/Encoder.cpp src/net/core/Message.cpp src/net/serialization/KakaKVRaftMessage.pb.cc src/net/ASIOChannel.cpp src/net/ASIOCodec.cpp src/net/ASIOConnector.cpp src/net/Endpoint.cpp src/net/FromRemoteHandler.cpp src/net/InboundChannelGroup.cpp src/net/OutboundChannelGroup.cpp src/net/Selector.cpp src/net/ToRemoteHandler.cpp)
target_link_libraries(NetWork PRIVATE protobuf::libprotoc protobuf::libprotobuf protobuf::libprotobuf-lite Boost::system Boost::thread Boost::chrono Common)
add_library(Role src/role/Candidate.cpp src/role/Follower.cpp src/role/Leader.cpp src/role/Role.cpp)
add_library(Task src/task/ASIOIOService.cpp src/task/ASIOScheduler.cpp src/task/ElectionTimeout.cpp src/task/IOService.cpp src/task/LogReplicationTask.cpp src/task/Scheduler.cpp src/task/TaskExecutor.cpp)
add_library(Message src/message/AppendEntries.cpp src/message/AppendEntriesResponse.cpp src/message/Message.cpp src/message/RequestVote.cpp src/message/RequestVoteResponse.cpp)
add_library(Log src/log/GeneralLogEntry.cpp src/log/LogComponent.cpp src/log/LogEntry.cpp src/log/LogEntrySequence.cpp src/log/MemoryLogComponent.cpp src/log/MemoryLogEntrySequence.cpp src/log/NoOpLogEntry.cpp)
add_library(Common src/common/eventBus/Event.cpp src/common/eventBus/EventBus.cpp src/common/net/buffer/Buffer.cpp src/common/net/buffer/CircleBuffer.cpp)
add_library(Cluster src/cluster/GroupMember.cpp src/cluster/NodeEndpoint.cpp src/cluster/NodeGroup.cpp src/cluster/NodeId.cpp src/cluster/ReplicatingState.cpp)

add_executable(KakaKV main.cpp)
target_link_libraries(KakaKV NetWork Role Task Message Log Common Cluster Server)