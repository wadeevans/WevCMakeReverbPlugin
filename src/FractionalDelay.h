#pragma once

#include <vector>

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
    int m_bufferSize = 0;
    int m_writeIndex = 0;
    float m_delayInSamples = 0.0f;
    double m_sampleRate = 44100.0;

    float linearInterpolate(float previousSample, float nextSample, float fraction)
    {
        return previousSample * (1.0f - fraction) + nextSample * fraction;
    }

};