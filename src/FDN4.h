#pragma once

#include <memory>
#include <array>

#include "FractionalDelay.h"
#include "OnePoleFilter.h"
#include "MixingMatrix4.h"

class FDN4
{
public:
    FDN4();
    ~FDN4() = default;

    void prepare(double sampleRate);
    float processSample(float input);
    void setDampingEnabled(bool dampingEnabled) { m_dampingEnabled = dampingEnabled; }
    void setDampingCutOffFrequency(float frequencyHz);
    void clear();

    void setDelayTimesInMs(const std::array<float, 4> &delayTimesInMs);
    void setDelayTimesInSamples(const std::array<float, 4> &delayTimesInSamples);

    void setMatrixType(MatrixType4 matrixType);

private:
    std::array<float, 4> m_feedbackGains{0.84f, 0.82f, 0.80f, 0.78f}; // move this to reverb implementation eventually
    bool m_dampingEnabled = false;

    std::array<FractionalDelay, 4> m_delayLines;
    std::array<OnePoleFilter, 4> m_dampingFilters;
    std::array<float, 4> m_delayOutputs{0.0f, 0.0f, 0.0f, 0.0f};

    std::unique_ptr<MixingMatrix4> m_mixingMatrix;
};