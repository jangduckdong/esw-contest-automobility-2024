///////////////////////////////////////////////////////////////////////////////////
//   Copyright Amazon.com, Inc. or its affiliates. All Rights Reserved.          //
//                                                                               //
//   Licensed under the Apache License, Version 2.0 (the "License").             //
//   You may not use this file except in compliance with the License.            //
//   You may obtain a copy of the License at                                     //
//                                                                               //
//       http://www.apache.org/licenses/LICENSE-2.0                              //
//                                                                               //
//   Unless required by applicable law or agreed to in writing, software         //
//   distributed under the License is distributed on an "AS IS" BASIS,           //
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.    //
//   See the License for the specific language governing permissions and         //
//   limitations under the License.                                              //
///////////////////////////////////////////////////////////////////////////////////

#ifndef IMAGE_PROCESS_HPP
#define IMAGE_PROCESS_HPP

#include "inference/aa/port/fusiondata.h"
#include "inference/aa/port/simulatordata.h"
#include "inference/aa/port/inferencedata.h"
#include <unordered_map>

namespace inference
{
namespace aa
{

namespace InferTask {
    class ImgProcessBase
    {
    public:
        ImgProcessBase() = default;
        ~ImgProcessBase() = default;
        virtual void processImage(const deepracer::service::fusiondata::proxy::events::FEvent::SampleType& fusiondata, cv::Mat& retImg,
                                  const std::unordered_map<std::string, int> &params) = 0;
        virtual void processImageVec(const deepracer::service::fusiondata::proxy::events::FEvent::SampleType& fusiondata, cv::Mat& retImg,
                                     const std::unordered_map<std::string, int> &params) = 0;
        virtual void reset() = 0;
        virtual const std::string getEncode() const = 0;
    };

    class RGB : public ImgProcessBase
    {
    /// Algorithm for down sampling RGB images.
    public:
        RGB() = default;
        virtual ~RGB() = default;
        virtual void processImage(const deepracer::service::fusiondata::proxy::events::FEvent::SampleType& fusiondata, cv::Mat& retImg,
                                  const std::unordered_map<std::string, int> &params) override;
        virtual void processImageVec(const deepracer::service::fusiondata::proxy::events::FEvent::SampleType& fusiondata, cv::Mat& retImg,
                                     const std::unordered_map<std::string, int> &params) override {(void)frameDataArr;(void)retImg;(void)params;}
        virtual void reset() override {}
        virtual const std::string getEncode() const;
    };

    class Grey : public ImgProcessBase
    {
    public:
        Grey(bool isThreshold, bool isMask);
        virtual ~Grey() = default;
        virtual void processImage(const deepracer::service::fusiondata::proxy::events::FEvent::SampleType& fusiondata, cv::Mat& retImg,
                                  const std::unordered_map<std::string, int> &params) override;
        virtual void processImageVec(const deepracer::service::fusiondata::proxy::events::FEvent::SampleType& fusiondata, cv::Mat& retImg,
                                     const std::unordered_map<std::string, int> &params);
        virtual void reset() override;
        virtual const std::string getEncode() const;
    private:
        std::vector<cv::Mat> imageStack_;
        const bool isThreshold_;
        const bool isMask_;
    };

    class GreyDiff : public ImgProcessBase
    {
    public:
        GreyDiff() = default;
        virtual ~GreyDiff() = default;
        virtual void processImage(const deepracer::service::fusiondata::proxy::events::FEvent::SampleType& fusiondata, cv::Mat& retImg,
                                  const std::unordered_map<std::string, int> &params) override;
        virtual void processImageVec(const deepracer::service::fusiondata::proxy::events::FEvent::SampleType& fusiondata, cv::Mat& retImg,
                                     const std::unordered_map<std::string, int> &params) override {(void)frameDataArr;(void)retImg;(void)params;}
        virtual void reset() override;
        virtual const std::string getEncode() const;
    private:
        cv::Mat prevImage_;


    };
}
#endif

}

}