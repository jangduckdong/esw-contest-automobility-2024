///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// Copyright, 2021 PopcornSAR Co., Ltd. All rights reserved.                                              
/// This software is copyright protected and proprietary to PopcornSAR Co., Ltd.                           
/// PopcornSAR Co., Ltd. grants to you only those rights as set out in the license conditions.             
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// AUTOSAR VERSION                   : R20-11
/// GENERATED BY                      : PARA, ARA::COM Generator
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// GENERATED FILE NAME               : impl_type_lidardata.h
/// IMPLEMENTATION DATA TYPE NAME     : LidarData
/// GENERATED DATE                    : 2024-10-25 13:47:26
///////////////////////////////////////////////////////////////////////////////////////////////////////////
///                                                                                                        
/// CAUTION!! AUTOMATICALLY GENERATED FILE - DO NOT EDIT                                                   
///                                                                                                        
///////////////////////////////////////////////////////////////////////////////////////////////////////////
#ifndef PARA_ARA_COM_GEN_CPP_IMPL_TYPE_LIDARDATA_H
#define PARA_ARA_COM_GEN_CPP_IMPL_TYPE_LIDARDATA_H
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// INCLUSION HEADER FILES
///////////////////////////////////////////////////////////////////////////////////////////////////////////
/// @uptrace{SWS_CM_00402}
#include <ara/core/structure.h>

#include "deepracer/type/impl_type_floatvector.h"
/// @uptrace{SWS_CM_10375}
namespace deepracer
{
namespace type
{
struct LidarData
{
    float angle_min;
    float angle_max;
    float angle_increment;
    float time_increment;
    float scan_time;
    float range_min;
    float range_max;
    deepracer::type::FloatVector ranges;
    deepracer::type::FloatVector intensities;
    PARA_STRUCTURE(LidarData, angle_min, angle_max, angle_increment, time_increment, scan_time, range_min, range_max, ranges, intensities);
};
} /// namespace type
} /// namespace deepracer
#endif /// PARA_ARA_COM_GEN_CPP_IMPL_TYPE_LIDARDATA_H