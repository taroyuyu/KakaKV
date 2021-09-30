#include <server/NodeBuilder.h>
#include <server/Node.h>
#include <task/ASIOScheduler.h>
#include <task/ASIOIOService.h>
int main(){
    auto nodeId = kakakv::cluster::NodeId("A");
    kakakv::net::Endpoint endpoint("0.0.0.0",8686);
    kakakv::server::NodeBuilder builder({nodeId,endpoint});
    auto ioService = std::make_shared<kakakv::task::ASIOIOService>();
    auto eventBus = std::make_shared<kakakv::common::EventBus>();
    builder.setScheduler(std::make_shared<kakakv::task::ASIOScheduler>(ioService,500,800,500,500))
    .setTaskExecutor(std::make_shared<kakakv::task::ASIOIOService>())
    .setConnector(std::make_shared<kakakv::net::ASIOConnector>(nodeId,eventBus,endpoint.host,endpoint.port))
    .build()->start();
    return 0;
}