// LFO.cpp
#include "LFO.h"
#include <cmath>

// TODO: refactor OnePoleFilter.cpp to use const float m_twoPi instead of M_PI
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void LFO::prepare(double sampleRate)
{
    m_sampleRate = static_cast<float>(sampleRate);
    clear();
}

void LFO::setFrequency(float frequency)
{
    m_frequency = frequency;
}

float LFO::processSample()
{
    // Simple sine wave generation (replace with actual LFO waveform as needed)
    float output = std::sin(m_phase);
    m_phase += m_twoPi * m_frequency / m_sampleRate;
    if (m_phase >= m_twoPi)
        m_phase -= m_twoPi;
    return output;
}

void LFO::clear()
{
    m_phase = 0.0f;
}