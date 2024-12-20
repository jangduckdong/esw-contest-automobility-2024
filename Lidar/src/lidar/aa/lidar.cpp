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
/// GENERATED FILE NAME               : lidar.cpp
/// SOFTWARE COMPONENT NAME           : Lidar
/// GENERATED DATE                    : 2024-10-25 13:47:26
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#include <vector>
#include <memory>
#include <chrono>
#include <thread>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <unistd.h>

#include "sl_lidar.h" 
#include "sl_lidar_driver.h"

#include "lidar/aa/lidar.h"

using namespace sl;
  
namespace lidar
{
namespace aa
{
 
Lidar::Lidar()
    : m_logger(ara::log::CreateLogger("LID", "SWC", ara::log::LogLevel::kVerbose))
    , m_workers(2)
{
}
 
Lidar::~Lidar()
{
}
 
bool Lidar::Initialize()
{
    m_logger.LogVerbose() << "Lidar::Initialize";
    m_LidarData = std::make_shared<lidar::aa::port::LidarData>();
    
    // const char* dev = "/dev/ttyUSB0";
    // uint32_t baudrate = 115200;
    // // 드라이버 인스턴스 생성
    // ILidarDriver * drv = *createLidarDriver();
    // if (!drv) {
    //     m_logger.LogError() << "Lidar::인스턴스 생성 실패";
    //     return false;
    // }else{
    //     m_logger.LogError() << "Lidar 인스턴스 생성 성공";
    // }
    // // 장치 연결
    // IChannel* channel = *createSerialPortChannel(dev, baudrate);
    // auto res = drv->connect(channel);
    // if (!SL_IS_OK(res)) {
    //     m_logger.LogError() << "Lidar::Failed to connect to device";
    //     return false;
    // }else{
    //     m_logger.LogError() << "Lidar::장치 연결 성공";
    // }
    // 드라이버 중지 및 정리
    // drv->stop();
    // drv = NULL;
    // std::this_thread::sleep_for(std::chrono::milliseconds(5000));

    return true;  // 초기화 성공 시 true 반환
}
 
void Lidar::Start()
{
    m_logger.LogVerbose() << "Lidar::Start";
    
    m_LidarData->Start();
    
    // run software component
    Run();
}
 
void Lidar::Terminate()
{
    m_logger.LogVerbose() << "Lidar::Terminate";
    
    m_LidarData->Terminate();

    // // 드라이버 중지 및 정리
    // drv->stop();
    // std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    // drv->setMotorSpeed(0);
    // drv.reset();
    // drv = NULL;
}
 
void Lidar::Run()
{
    m_logger.LogVerbose() << "Lidar::Run";
    
    // LidarData에서 데이터 캡처 및 전송을 비동기로 호출
    m_workers.Async([this] { TaskGenerateLEventValue(); });
    m_workers.Async([this] { m_LidarData->SendEventLEventCyclic(); });
    
    m_workers.Wait();
}

void Lidar::TaskGenerateLEventValue()
{
    while (m_running) 
    {
        m_LidarData->produceScanning();
        std::this_thread::sleep_for(std::chrono::seconds(1));  // 1초 대기 후 다음 프레임 캡처
    }
}
 
} /// namespace aa
} /// namespace lidar
