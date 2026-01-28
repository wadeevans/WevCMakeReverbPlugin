#pragma once

#include <vector>

class FractionalDelay
{
public:
    FractionalDelay() = default;
    ~FractionalDelay() = default;

    void prepare(double sampleRate, int maxDelayInSamples);
    void setDelay(float delayMs);
    float processSample(float input);
    void clear();

private:

    std::vector<float> m_buffer;
    int m_writeIndex = 0;
    float m_delayInSamples = 0.0f;
    double sampleRate = 44100.0;

};