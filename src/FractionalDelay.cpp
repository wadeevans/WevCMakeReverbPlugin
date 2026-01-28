#include "FractionalDelay.h"

void FractionalDelay::prepare(double sampleRate, float maxDelayInMs)
{
    m_sampleRate = sampleRate;
    // Convert max delay from milliseconds to samples
    m_bufferSize = static_cast<int>((maxDelayInMs / 1000.0f) * m_sampleRate);
    m_buffer.resize(m_bufferSize);
    m_writeIndex = 0;
    clear();

}

void FractionalDelay::setDelay(float delayInMs)
{
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