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
/// GENERATED DATE                    : 2024-11-07 14:01:17
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "sensorfusion/aa/port/fusiondata.h"
 
namespace deepracer
{
namespace service
{
namespace fusiondata
{
namespace skeleton
{
 
SvFusionDataSkeletonImpl::SvFusionDataSkeletonImpl(ara::core::InstanceSpecifier instanceSpec, ara::com::MethodCallProcessingMode mode)
    : SvFusionDataSkeleton(instanceSpec, mode)
    , m_logger(ara::log::CreateLogger("SSFU", "PORT", ara::log::LogLevel::kVerbose))
{
}
 
} /// namespace skeleton
} /// namespace fusiondata
} /// namespace service
} /// namespace deepracer

namespace sensorfusion
{
namespace aa
{
namespace port
{
 
FusionData::FusionData()
    : m_logger(ara::log::CreateLogger("SSFU", "PORT", ara::log::LogLevel::kVerbose))
    , m_running{false}
{
    // 카메라 데이터 크기 초기화
    m_FEventData.camera_data.resize(2);  
    // 라이다 데이터 초기화
    m_FEventData.lidar_data.clear();
    // 타임스탬프 초기화
    m_FEventData.timestamp = 0;
}
 
FusionData::~FusionData()
{
}
 
void FusionData::Start()
{
    m_logger.LogVerbose() << "FusionData::Start";
    
    // construct skeleton
    ara::core::InstanceSpecifier specifier{"SensorFusion/AA/FusionData"};
    m_interface = std::make_shared<deepracer::service::fusiondata::skeleton::SvFusionDataSkeletonImpl>(specifier);
    
    // offer service
    auto offer = m_interface->OfferService();
    if (offer.HasValue())
    {
        m_running = true;
        m_logger.LogVerbose() << "FusionData::Start::OfferService::성공!!";
    }
    else
    {
        m_running = false;
        m_logger.LogError() << "FusionData::Start::OfferService::실패!!!" << offer.Error().Message();
    }
}
 
void FusionData::Terminate()
{
    m_logger.LogVerbose() << "FusionData::Terminate";
    
    // stop port
    m_running = false;
    
    // stop offer service
    m_interface->StopOfferService();
    m_logger.LogVerbose() << "FusionData::Terminate::StopOfferService";
}

// 현재 CEvent 데이터를 갱신하는 함수
void FusionData::WriteDataFEventCamera(const deepracer::type::CameraDataNode& data)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_FEventData.camera_data[0] = data.camera_data0;
}
void FusionData::WriteDataFEventLidar(const deepracer::type::LidarDataNode& data)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_FEventData.lidar_data = data.lidar_data;
    m_FEventData.timestamp = data.timestamp;
}

void FusionData::SendEventFEventCyclic()
{
    while (m_running)
    {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            auto send = m_interface->FEvent.Send(m_FEventData);

            if (!m_FEventData.camera_data.empty()) {
                m_logger.LogVerbose() << "m_FEventData.camera_data에 데이터가 삽입됨.";
            } else {
                m_logger.LogVerbose() << "m_FEventData.camera_data가 비어 있음.";
            }
            if (!m_FEventData.lidar_data.empty()) {
                m_logger.LogVerbose() << "m_FEventData.lidar_data 삽입됨.";
            } else {
                m_logger.LogVerbose() << "m_FEventData.lidar_data 비어 있음.";
            }

            if (send.HasValue())
            {
                m_logger.LogVerbose() << "FusionData::SendEventFEventCyclic::Send";
                // << m_FEventData.camera_data[0][0]
                // << m_FEventData.camera_data[1][0]
                // << m_FEventData.lidar_data[0]
                // << m_FEventData.timestamp;
            }
            else
            {
                m_logger.LogError() << "FusionData::SendEventFEventCyclic::Send::실패" << send.Error().Message();
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200));
    }
}
 
} /// namespace port
} /// namespace aa
} /// namespace sensorfusion
 
/// EOF