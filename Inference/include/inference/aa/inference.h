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
/// GENERATED FILE NAME               : inference.h
/// SOFTWARE COMPONENT NAME           : Inference
/// GENERATED DATE                    : 2024-10-25 13:47:26
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_AA_GEN_SOFTWARE_COMPONENT_INFERENCE_AA_H
#define PARA_AA_GEN_SOFTWARE_COMPONENT_INFERENCE_AA_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include "inference/aa/port/fusiondata.h"
#include "inference/aa/port/simulatordata.h"
#include "inference/aa/port/inferencedata.h"
 
#include "para/swc/port_pool.h"
 
namespace inference
{
namespace aa
{
 
class Inference
{
public:
    /// @brief Constructor
    Inference();
    
    /// @brief Destructor
    ~Inference();
    
    /// @brief Initialize software component
    bool Initialize();
    
    /// @brief Start software component
    void Start();
    
    /// @brief Terminate software component
    void Terminate();
 
private:
    /// @brief Run software component
    void Run();
 
private:
    /// @brief Pool of port
    ::para::swc::PortPool m_workers;
    
    /// @brief Logger for software component
    ara::log::Logger& m_logger;
    
    /// @brief Instance of Port {Inference.FusionData}
    std::shared_ptr<inference::aa::port::FusionData> m_FusionData;
    
    /// @brief Instance of Port {Inference.SimulatorData}
    std::shared_ptr<inference::aa::port::SimulatorData> m_SimulatorData;
    
    /// @brief Instance of Port {Inference.InferenceData}
    std::shared_ptr<inference::aa::port::InferenceData> m_InferenceData;
};
 
} /// namespace aa
} /// namespace inference
 
#endif /// PARA_AA_GEN_SOFTWARE_COMPONENT_INFERENCE_AA_H