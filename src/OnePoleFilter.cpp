// OnePoleFilter.cpp

#include "OnePoleFilter.h"

#include <algorithm>
#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

void OnePoleFilter::prepare(double sampleRate)
{
    m_sampleRate = static_cast<float>(sampleRate);
    clear();
}

void OnePoleFilter::setFrequencyCutOffCoefficient(float frequencyHz)
{
    m_coefficient = std::exp(-2.0f * M_PI * frequencyHz / m_sampleRate);
    m_coefficient = std::clamp(m_coefficient, 0.0f, 0.999f);
}

float OnePoleFilter::processSample(float input)
{

    float output = ((1 - m_coefficient) * input) + (m_coefficient * m_previousOutput);
    m_previousOutput = output;

    return output;
}

void OnePoleFilter::clear()
{
    m_previousOutput = 0.0f;
}