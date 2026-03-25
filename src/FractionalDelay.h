#pragma once

#include <vector>

#include "SmoothedParameter.h"

/**
 * A fractional delay line with linear interpolation.
 * Provides subsample-accurate delays using a circular buffer.
 * Delay times specified in milliseconds, converted internally to samples.
 */
class FractionalDelay
{
public:
    FractionalDelay() = default;
    ~FractionalDelay() = default;

    void prepare(double sampleRate, float maxDelayInMs, float smoothingMs);
    void setDelayInMs(float delayInMs);
    void setDelayInSamples(float delayInSamples);
    void setSmoothingTime(float timeMs);
    float processSample(float input);
    void clear();

private:
    std::vector<float> m_buffer;
    float m_bufferSize = 0.0f;
    int m_bufferSizeInt = 0;
    int m_writeIndex = 0;
    float m_delayInSamples = 0.0f;
    float m_sampleRate = 44100.0f;

    SmoothedParameter m_delayTimeSmoother;

    float linearInterpolate(float previousSample, float nextSample, float fraction)
    {
        return previousSample * (1.0f - fraction) + nextSample * fraction;
    }

    float lagrange3interpolate(float xminus1, float x0, float x1, float x2, float fraction)
    {
        // Lagrange interpolation formula for 4 points
        float cminus1 = (fraction - 0.0f) * (fraction - 1.0f) * (fraction - 2.0f) / -6.0f;
        float c0 = (fraction + 1.0f) * (fraction - 1.0f) * (fraction - 2.0f) / 2.0f;
        float c1 = (fraction + 1.0f) * (fraction - 0.0f) * (fraction - 2.0f) / -2.0f;
        float c2 = (fraction + 1.0f) * (fraction - 0.0f) * (fraction - 1.0f) / 6.0f;

        return (cminus1 * xminus1) + (c0 * x0) + (c1 * x1) + (c2 * x2);
    }
};