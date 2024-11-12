#ifndef CONSTANTS_HPP
#define CONSTANTS_HPP

#include <string>
#include <map>
#include <vector>

enum class ActionSpaceTypes {
    DISCRETE = 1,
    CONTINUOUS = 2
};

class ModelMetadataKeys {
public:
    static const std::string ACTION_SPACE_TYPE;
    static const std::string CONTINUOUS_HIGH;
    static const std::string CONTINUOUS_LOW;
    static const std::string STEERING;
    static const std::string SPEED;
};

// 변수 초기화
const std::string ModelMetadataKeys::ACTION_SPACE_TYPE = "action_space_type";
const std::string ModelMetadataKeys::CONTINUOUS_HIGH = "high";
const std::string ModelMetadataKeys::CONTINUOUS_LOW = "low";
const std::string ModelMetadataKeys::STEERING = "steering_angle";
const std::string ModelMetadataKeys::SPEED = "speed";

// 기본 동작 공간
using ActionSpace = std::map<std::string, double>;  // 각 액션의 속성과 값을 나타내는 맵
const std::vector<ActionSpace> DEFAULT_ACTION_SPACE = {
    {{ModelMetadataKeys::SPEED, 0.8}, {ModelMetadataKeys::STEERING, 30.0}},
    {{ModelMetadataKeys::SPEED, 0.8}, {ModelMetadataKeys::STEERING, -30.0}},
    {{ModelMetadataKeys::SPEED, 0.8}, {ModelMetadataKeys::STEERING, 0.0}},
    {{ModelMetadataKeys::SPEED, 0.8}, {ModelMetadataKeys::STEERING, 15.0}},
    {{ModelMetadataKeys::SPEED, 0.8}, {ModelMetadataKeys::STEERING, -15.0}},
    {{ModelMetadataKeys::SPEED, 0.4}, {ModelMetadataKeys::STEERING, 0.0}}
};

// 기본 속도 스케일 값
const std::vector<double> DEFAULT_SPEED_SCALES = {1.0, 0.8};

#endif // CONSTANTS_HPP
