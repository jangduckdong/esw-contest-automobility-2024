///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// Copyright, 2021 PopcornSAR Co., Ltd. All rights reserved.                                              
/// This software is copyright protected and proprietary to PopcornSAR Co., Ltd.                           
/// PopcornSAR Co., Ltd. grants to you only those rights as set out in the license conditions.             
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// AUTOSAR VERSION                   : R20-11
/// GENERATED BY                      : PARA, Adaptive Application Generator
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// GENERATED FILE NAME               : fusiondata.cpp
/// SOFTWARE COMPONENT NAME           : FusionData
/// GENERATED DATE                    : 2024-10-25 13:47:26
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "inference/aa/port/fusiondata.h"
 
namespace inference
{
namespace aa
{
namespace port
{
 
FusionData::FusionData()
    : m_logger(ara::log::CreateLogger("INFR", "PORT", ara::log::LogLevel::kVerbose))
    , m_running{false}
    , m_found{false}
{
}
 
FusionData::~FusionData()
{
}
 
void FusionData::Start()
{
    m_logger.LogVerbose() << "FusionData::Start";
    
    // regist callback
    ara::core::InstanceSpecifier specifier{"Inference/AA/FusionData"};
    auto handler = [this](ara::com::ServiceHandleContainer<deepracer::service::fusiondata::proxy::SvFusionDataProxy::HandleType> handles,
                          ara::com::FindServiceHandle findHandle) {
        this->Find(handles, findHandle);
    };
    
    // find service
    auto find = deepracer::service::fusiondata::proxy::SvFusionDataProxy::StartFindService(handler, specifier);
    if (find.HasValue())
    {
        m_logger.LogVerbose() << "FusionData::Start::StartFindService";
    }
    else
    {
        m_logger.LogError() << "FusionData::Start::StartFindService::" << find.Error().Message();
    }
    
    // run port
    m_running = true;
}
 
void FusionData::Terminate()
{
    m_logger.LogVerbose() << "FusionData::Terminate";
    
    // stop port
    m_running = false;
    
    // clear service proxy
    if (m_interface)
    {
        
        // stop find service
        m_interface->StopFindService(*m_findHandle);
        m_found = false;
        
        m_logger.LogVerbose() << "FusionData::Terminate::StopFindService";
    }
}
 
void FusionData::Find(ara::com::ServiceHandleContainer<deepracer::service::fusiondata::proxy::SvFusionDataProxy::HandleType> handles, ara::com::FindServiceHandle findHandle)
{
    // check finding handles
    if (handles.empty())
    {
        m_logger.LogVerbose() << "FusionData::Find::Service Instances not found";
        return;
    }
    else
    {
        for (auto& handle : handles)
        {
            m_logger.LogVerbose() << "FusionData::Find::Searched Instance::ServiceId =" << 
                                     handle.GetServiceHandle().serviceId << 
                                     ", InstanceId =" << 
                                     handle.GetServiceHandle().instanceId;
        }
    }
    
    // create proxy
    if (m_interface)
    {
        m_logger.LogVerbose() << "FusionData::Find::Proxy is already running";
    }
    else
    {
        m_logger.LogVerbose() << "FusionData::Find::Using Instance::ServiceId =" << 
                                 handles[0].GetServiceHandle().serviceId << 
                                 ", InstanceId =" << 
                                 handles[0].GetServiceHandle().instanceId;
        m_interface = std::make_shared<deepracer::service::fusiondata::proxy::SvFusionDataProxy>(handles[0]);
        m_findHandle = std::make_shared<ara::com::FindServiceHandle>(findHandle);
        m_found = true;
        
    }
}
 
void FusionData::RequestFMethod()
{
    if (m_found)
    {
        auto request = m_interface->FMethod();
        request.wait();
        auto response = request.GetResult();
        if (response.HasValue())
        {
            m_logger.LogVerbose() << "FusionData::RequestFMethod::Responded";
            
            auto result = response.Value();
            // put your logic
        }
        else
        {
            m_logger.LogError() << "FusionData::RequestFMethod::" << response.Error().Message();
        }
    }
}
 
} /// namespace port
} /// namespace aa
} /// namespace inference
 
/// EOF