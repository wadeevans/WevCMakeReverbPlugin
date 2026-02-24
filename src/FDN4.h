#pragma once

#include <memory>

#include "FractionalDelay.h"
#include "OnePoleFilter.h"
#include "Hadamard4.h"

class FDN4
{
public:
    FDN4();
    ~FDN4() = default;

    void prepare(double sampleRate);
    float processSample(float input);
    void clear();

    void setDelayTimes(const std::array<float, 4>& delayTimes);

private:

    std::array<FractionalDelay, 4> m_delayLines;
    std::array<OnePoleFilter, 4> m_dampingFilters;

    std::array<float, 4> m_delayOutputs;

    std::unique_ptr<MixingMatrix4> m_mixingMatrix;

    float m_feedbackGain = 0.9f;

    

};