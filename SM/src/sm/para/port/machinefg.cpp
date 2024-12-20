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
/// GENERATED FILE NAME               : machinefg.cpp
/// SOFTWARE COMPONENT NAME           : MachineFG
/// GENERATED DATE                    : 2024-11-07 14:01:17
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "sm/para/port/machinefg.h"
 
namespace ara
{
namespace sm
{
namespace machinefg
{
namespace skeleton
{
 
TriggerInOut_MachineFGSkeletonImpl::TriggerInOut_MachineFGSkeletonImpl(ara::core::InstanceSpecifier instanceSpec, ara::com::MethodCallProcessingMode mode)
    : TriggerInOut_MachineFGSkeleton(instanceSpec, mode)
    , m_logger(ara::log::CreateLogger("SM", "PORT", ara::log::LogLevel::kVerbose))
    , m_MachineFGState{ara::sm::MachineStateType::kOff}
{
    // create state client
    m_stateClient = std::make_unique<ara::exec::StateClient>(m_undefinedStateCallback);
    
    // initial machine state
    auto initState = m_stateClient->GetInitialMachineStateTransitionResult();
    initState.wait();
    auto response = initState.GetResult();
    if (response.HasValue())
    {
        m_logger.LogVerbose() << "MachineFG::Ctor::GetInitialMachineStateTransitionResult";
        // set MachineFG.Startup
        m_MachineFGState = ara::sm::MachineStateType::kStartup;
    }
    else
    {
        m_logger.LogError() << "MachineFG::Ctor::GetInitialMachineStateTransitionResult::" << response.Error().Message();
    }
    
    // regist get handler, Notifier
    auto notifier_get_handler = [this]() {
        return GetNotifier();
    };
    Notifier.RegisterGetHandler(notifier_get_handler);
    
    // regist set handler, Trigger
    auto trigger_set_handler = [this](const fields::Trigger::FieldType& value) {
        return SetTrigger(value);
    };
    Trigger.RegisterSetHandler(trigger_set_handler);
}
 
ara::core::Future<fields::Notifier::FieldType> TriggerInOut_MachineFGSkeletonImpl::GetNotifier()
{
    m_logger.LogVerbose() << "MachineFG::GetNotifier::Requested";
    
    ara::core::Promise<fields::Notifier::FieldType> promise;
    
    promise.set_value(m_MachineFGState);
    return promise.get_future();
}
 
void TriggerInOut_MachineFGSkeletonImpl::NotifyMachineFG()
{
    auto notify = Notifier.Update(m_MachineFGState);
    if (notify.HasValue())
    {
        m_logger.LogVerbose() << "MachineFG::NotifyNotifier::Update";
    }
    else
    {
        m_logger.LogError() << "MachineFG::NotifyNotifier::Update::" << notify.Error().Message();
    }
}
 
void TriggerInOut_MachineFGSkeletonImpl::UpdateMachineFG(const fields::Notifier::FieldType& value)
{
    m_MachineFGState = value;
}
 
ara::core::Future<fields::Trigger::FieldType> TriggerInOut_MachineFGSkeletonImpl::SetTrigger(const fields::Trigger::FieldType& value)
{
    m_logger.LogVerbose() << "MachineFG::SetTrigger::Requested";
    
    ara::core::Promise<fields::Trigger::FieldType> promise;
    
    // try to set field value
    RequestTransitFunctionGroupState(value);
    
    promise.set_value(m_MachineFGState);
    return promise.get_future();
}
 
void TriggerInOut_MachineFGSkeletonImpl::RequestTransitFunctionGroupState(const fields::Trigger::FieldType& value)
{
    ara::core::StringView functionGroupIdentifier{};
    switch (value)
    {
        case ara::sm::MachineStateType::kOff :
        {
            functionGroupIdentifier = "MachineFG/Off";
            break;
        }
        case ara::sm::MachineStateType::kStartup :
        {
            functionGroupIdentifier = "MachineFG/Startup";
            break;
        }
        case ara::sm::MachineStateType::kShutdown :
        {
            functionGroupIdentifier = "MachineFG/Shutdown";
            break;
        }
        case ara::sm::MachineStateType::kRestart :
        {
            functionGroupIdentifier = "MachineFG/Restart";
            break;
        }
        case ara::sm::MachineStateType::kVerify :
        {
            functionGroupIdentifier = "MachineFG/Verify";
            break;
        }
    }
    // initialize function group
    auto preFunctionGroup = ara::exec::FunctionGroup::Preconstruct("MachineFG");
    ara::exec::FunctionGroup::CtorToken tokenFunctionGroup(preFunctionGroup.ValueOrThrow());
    ara::exec::FunctionGroup functionGroup(std::move(tokenFunctionGroup));
    
    // initialize function group state
    auto preFunctionGroupState = ara::exec::FunctionGroupState::Preconstruct(functionGroup, functionGroupIdentifier);
    ara::exec::FunctionGroupState::CtorToken tokenFunctionGroupState(preFunctionGroupState.ValueOrThrow());
    ara::exec::FunctionGroupState functionGroupState(std::move(tokenFunctionGroupState));
    
    // request set state to EM
    auto request = m_stateClient->SetState(functionGroupState);
    request.wait();
    auto response = request.GetResult();
    if (response.HasValue())
    {
        m_logger.LogVerbose() << "MachineFG::RequestChangeFunctionGroupState::SetState";
        m_MachineFGState = value;
    }
    else
    {
        m_logger.LogError() << "MachineFG::RequestChangeFunctionGroupState::SetState::" << response.Error().Message();
    }
}
 
void TriggerInOut_MachineFGSkeletonImpl::UndefinedStateHandler(ara::exec::FunctionGroup& /*functionGroup*/)
{
    // put your logic
}
 
} /// namespace skeleton
} /// namespace machinefg
} /// namespace sm
} /// namespace ara

namespace sm
{
namespace para
{
namespace port
{
 
MachineFG::MachineFG()
    : m_logger(ara::log::CreateLogger("SM", "PORT", ara::log::LogLevel::kVerbose))
    , m_running{false}
{
}
 
MachineFG::~MachineFG()
{
}
 
void MachineFG::Start()
{
    m_logger.LogVerbose() << "MachineFG::Start";
    
    // construct skeleton
    ara::core::InstanceSpecifier specifier{"SM/PARA/MachineFG"};
    m_interface = std::make_shared<ara::sm::machinefg::skeleton::TriggerInOut_MachineFGSkeletonImpl>(specifier);
    
    // offer service
    auto offer = m_interface->OfferService();
    if (offer.HasValue())
    {
        m_running = true;
        m_logger.LogVerbose() << "MachineFG::Start::OfferService";
    }
    else
    {
        m_running = false;
        m_logger.LogError() << "MachineFG::Start::OfferService::" << offer.Error().Message();
    }
}
 
void MachineFG::Terminate()
{
    m_logger.LogVerbose() << "MachineFG::Terminate";
    
    // stop port
    m_running = false;
    
    // stop offer service
    m_interface->StopOfferService();
    m_logger.LogVerbose() << "MachineFG::Terminate::StopOfferService";
}
 
void MachineFG::WriteValueMachineFG(const ara::sm::machinefg::skeleton::fields::Notifier::FieldType& value)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_interface->UpdateMachineFG(value);
}
 
void MachineFG::NotifyMachineFGCyclic()
{
    while (m_running)
    {
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_interface->NotifyMachineFG();
        }
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
 
void MachineFG::NotifyMachineFGTriggered()
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_interface->NotifyMachineFG();
}
 
void MachineFG::NotifyMachineFGTriggered(const ara::sm::machinefg::skeleton::fields::Notifier::FieldType& value)
{
    std::lock_guard<std::mutex> lock(m_mutex);
    m_interface->UpdateMachineFG(value);
    m_interface->NotifyMachineFG();
}
 
} /// namespace port
} /// namespace para
} /// namespace sm
 
/// EOF