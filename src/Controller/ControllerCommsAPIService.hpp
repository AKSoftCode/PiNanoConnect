#include "Proto/Controller.grpc.pb.h"

#include <string>

#include <grpcpp/grpcpp.h>
#include <atomic>
#include <future>
#include "IDeviceActions.h"
#include "IQueryEngine.h"

using grpc::Server;
using grpc::ServerBuilder;
using grpc::ServerWriter;
using grpc::ServerContext;
using grpc::Status;

using namespace Controller;
using namespace Model;
using namespace DataAccess;

class ControllerCommsAPIServiceImpl final : public ControllerCommsAPIService::Service {
    std::atomic_bool bExitServer_ = false;

    std::future<void> getParamFuture_;
    std::future<void> alarmsFuture_;
    std::future<void> getDeviceStateFuture_;

    IDeviceActions& deviceAction_;
    IQueryEngine& queryMachineInstance_;

public:

    ControllerCommsAPIServiceImpl();
    virtual ~ControllerCommsAPIServiceImpl();
    virtual Status GetPing(ServerContext* context, const ::google::protobuf::Empty* request, ::PingReply* response);
    virtual Status GetDeviceParams(ServerContext* context, const ::google::protobuf::Empty* request, ServerWriter< ::ParameterPack>* writer) override ;
    virtual Status GetAlarms(ServerContext* context, const ::google::protobuf::Empty* request, ServerWriter< ::Alarm>* writer) override ;
    virtual Status GetSettings(ServerContext* context, const ::google::protobuf::Empty* request, ::Settings* response) override ;
};
