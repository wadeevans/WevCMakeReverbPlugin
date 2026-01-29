#pragma once

#include <vector>

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

    void prepare(double sampleRate, float maxDelayInMs);
    void setDelay(float delayInMs);
    float processSample(float input);
    void clear();

private:

    std::vector<float> m_buffer;
    float m_bufferSize = 0.0f;
    int m_writeIndex = 0;
    float m_delayInSamples = 0.0f;
    float m_sampleRate = 44100.0f;

    float linearInterpolate(float previousSample, float nextSample, float fraction)
    {
        return previousSample * (1.0f - fraction) + nextSample * fraction;
    }

};