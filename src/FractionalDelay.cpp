#include "FractionalDelay.h"

void FractionalDelay::prepare(double sampleRate, float maxDelayInMs)
{
    m_sampleRate = static_cast<float>(sampleRate);
    // Convert max delay from milliseconds to samples
    m_bufferSize = (maxDelayInMs / 1000.0f) * m_sampleRate;
    m_buffer.resize(static_cast<int>(m_bufferSize));
    m_writeIndex = 0;
    clear();

}

void FractionalDelay::setDelay(float delayInMs)
{
    m_delayInSamples = (delayInMs / 1000.0f) * m_sampleRate;
    // Ensure delay doesn't exceed buffer size
    if (m_delayInSamples > m_bufferSize) 
        m_delayInSamples = m_bufferSize;

}

float FractionalDelay::processSample(float input)
{
    return input;  // Pass-through for now
}

void FractionalDelay::clear()
{
    for (auto& sample : m_buffer) sample = 0.0f;
    m_writeIndex = 0;
}