#include "ControllerCommsAPIService.hpp"

#include <thread>
#include <chrono>
#include <spdlog/spdlog.h>

#include <iostream>
#include "exceptxx/TryCatch.h"

using namespace std::chrono_literals;
using namespace Controller;
using namespace Model;
using namespace DataAccess;


ControllerCommsAPIServiceImpl::~ControllerCommsAPIServiceImpl()
{
	bExitServer_ = false;
	getParamFuture_.get();
	alarmsFuture_.get();
	getDeviceStateFuture_.get();
}

Status ControllerCommsAPIServiceImpl::GetPing(ServerContext* context, const::google::protobuf::Empty* request, ::PingReply* response)
{
	response->set_isserveralive(true);
	return Status::OK;
}

ControllerCommsAPIServiceImpl::ControllerCommsAPIServiceImpl() : deviceAction_(getProcessActionInstance()), queryMachineInstance_(getQueryEngineInstance())
{

}

Status ControllerCommsAPIServiceImpl::GetDeviceParams(::grpc::ServerContext* context, const ::google::protobuf::Empty* request, ::grpc::ServerWriter< ::ParameterPack>* writer)
{
	//getParamFuture_ = std::async(std::launch::async, [&]()
	//	{

	//	});
	EX_TRY(ex)
	{
		while (!bExitServer_)
		{
			ParameterPack pack;
			pack.set_paramanalogval1(deviceAction_.getAnalogParam1Value());
			pack.set_paramanalogval2(deviceAction_.getAnalogParam2Value());
			pack.set_paramanalogval3(deviceAction_.getAnalogParam3Value());


			DeviceState deviceState;
			deviceState.set_paramstate1(deviceAction_.getParam1Status());
			deviceState.set_paramstate2(deviceAction_.getParam2Status());
			deviceState.set_paramstate3(deviceAction_.getParam3Status());
			deviceState.set_paramstate4(deviceAction_.getParam4Status());


			pack.mutable_devicestate()->CopyFrom(deviceState);

			writer->Write(pack);

			std::this_thread::sleep_for(1s);
		}
	}
	EX_CATCH(ex);

	if (ex)
	{
		SPDLOG_ERROR("Exception : {} ", ex->what());
	}


	return Status::OK;
}

Status ControllerCommsAPIServiceImpl::GetAlarms(::grpc::ServerContext* context, const::google::protobuf::Empty* request, ::grpc::ServerWriter<::Alarm>* writer)
{
	alarmsFuture_ = std::async(std::launch::async, [&]()
	{
		EX_TRY(ex)
		{
			while (!bExitServer_)
			{
				Alarm alarm;
				writer->Write(alarm);

				std::this_thread::sleep_for(1s);
			}
		}
		EX_CATCH(ex);

		if (ex)
		{
			SPDLOG_ERROR("Exception : {} ", ex->what());
		}
	});
	return Status::OK;
}

//
//Status ControllerCommsAPIServiceImpl::GetSettings(ServerContext* context, const ::google::protobuf::Empty* request, ::Settings* response)
//{
//	EX_TRY(ex)
//	{
//		
//	}
//	EX_CATCH(ex);
//
//	if (ex)
//	{
//		SPDLOG_ERROR("Exception : {} ", ex->what());
//	}
//
//	return Status::OK;
//}