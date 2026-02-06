#include "FractionalDelay.h"


void FractionalDelay::prepare(double sampleRate, float maxDelayInMs)
{
    m_sampleRate = static_cast<float>(sampleRate);
    // Convert max delay from milliseconds to samples
    m_bufferSize = (maxDelayInMs / 1000.0f) * m_sampleRate;
    m_buffer.resize(static_cast<int>(m_bufferSize));
    m_writeIndex = 0;

    // initialise smoothing parameter
    m_delayTimeSmoother.reset(0.0f);
    m_delayTimeSmoother.setSmoothingTime(50.0, m_sampleRate);

    clear();

}

void FractionalDelay::setDelay(float delayInMs)
{
    float delayInSamples = (delayInMs / 1000.0f) * m_sampleRate;
    
    // Ensure delay doesn't exceed buffer size
    if (delayInSamples > m_bufferSize) 
        delayInSamples = m_bufferSize;

    m_delayTimeSmoother.setTargetValue(delayInSamples);
    
}

float FractionalDelay::processSample(float input)
{
    float currentDelay = m_delayTimeSmoother.getNextValue();
    // Special case: zero or near-zero delay
    if (currentDelay < 0.5f)
    {
        // Still write to buffer to maintain state
        m_buffer[m_writeIndex] = input;
        m_writeIndex = (m_writeIndex + 1) % static_cast<int>(m_bufferSize);
        return input;
    }


    // create readPos as float ready for interpolation
    float readPos = m_writeIndex - currentDelay;

    if (readPos < 0.0f)
        readPos += m_bufferSize;


    // create previousReadIndex and nextReadIndex for interpolation
    int previousReadIndex = static_cast<int>(readPos);
    float fractionalPart = readPos - previousReadIndex;
    int nextReadIndex = (previousReadIndex + 1) % static_cast<int>(m_bufferSize);

    float output = linearInterpolate(m_buffer[previousReadIndex], m_buffer[nextReadIndex], fractionalPart);

    // write input into buffer and advance m_writeIndex
    m_buffer[m_writeIndex] = input;
    m_writeIndex = (m_writeIndex + 1) % static_cast<int>(m_bufferSize);

    return output;  
}

void FractionalDelay::clear()
{
    for (auto& sample : m_buffer) sample = 0.0f;
    m_writeIndex = 0;
}