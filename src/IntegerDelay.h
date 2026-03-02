#pragma once

#include <vector>

class IntegerDelay
{
public:
    IntegerDelay() = default;
    ~IntegerDelay() = default;

    void prepare(int delayInSamples);
    float processSample(float input);
    void clear();


private:
    std::vector<float> m_buffer;
    int m_bufferSize = 0;
    int m_writeIndex = 0;
    
};