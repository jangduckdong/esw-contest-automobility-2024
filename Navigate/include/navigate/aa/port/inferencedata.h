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
/// GENERATED FILE NAME               : inferencedata.h
/// SOFTWARE COMPONENT NAME           : InferenceData
/// GENERATED DATE                    : 2024-10-25 13:47:26
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_AA_GEN_SOFTWARE_COMPONENT_RPORT_NAVIGATE_AA_INFERENCEDATA_H
#define PARA_AA_GEN_SOFTWARE_COMPONENT_RPORT_NAVIGATE_AA_INFERENCEDATA_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "deepracer/service/inferencedata/svinferencedata_proxy.h"
 
#include "ara/log/logger.h"
 
#include <mutex>
#include <thread>
 
namespace navigate
{
namespace aa
{
namespace port
{
 
class InferenceData
{
public:
    /// @brief Constructor
    InferenceData();
    
    /// @brief Destructor
    ~InferenceData();
    
    /// @brief Start port
    void Start();
    
    /// @brief Terminate port
    void Terminate();
    
    /// @brief Subscribe event, IEvent
    void SubscribeIEvent();
     
    /// @brief Stop event subscription, IEvent
    void StopSubscribeIEvent();
     
    /// @brief Event receive handler, IEvent
    void ReceiveEventIEventTriggered();
     
    /// @brief Event receive handler, IEvent
    void ReceiveEventIEventCyclic();
     
    /// @brief Read event data, IEvent
    void ReadDataIEvent(ara::com::SamplePtr<deepracer::service::inferencedata::proxy::events::IEvent::SampleType const> samplePtr);
    
    void SetReceiveEventIEventHandler(
        std::function<void(const deepracer::service::inferencedata::proxy::events::IEvent::SampleType&)> handler);

    
private:
    /// @brief Callback for find service
    void Find(ara::com::ServiceHandleContainer<deepracer::service::inferencedata::proxy::SvInferenceDataProxy::HandleType> handles,
              ara::com::FindServiceHandle findHandle);
    
    /// @brief Callback for event receiver, IEvent
    void RegistReceiverIEvent();
    
    
private:
    /// @brief Logger for this port
    ara::log::Logger& m_logger;
    
    /// @brief Flag of port status
    bool m_running;
    
    /// @brief Flag of find service status
    bool m_found;
    
    /// @brief Mutex for this port
    std::mutex m_mutex; 
    
    /// @brief AUTOSAR Port Interface
    std::shared_ptr<deepracer::service::inferencedata::proxy::SvInferenceDataProxy> m_interface;
    
    /// @brief Find service handle
    std::shared_ptr<ara::com::FindServiceHandle> m_findHandle;

    std::function<void(const deepracer::service::inferencedata::proxy::events::IEvent::SampleType&)> m_receiveEventIEventHandler;
};
 
} /// namespace port
} /// namespace aa
} /// namespace navigate
 
#endif /// PARA_AA_GEN_SOFTWARE_COMPONENT_RPORT_NAVIGATE_AA_INFERENCEDATA_H