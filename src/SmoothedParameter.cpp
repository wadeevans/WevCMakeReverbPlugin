#include "SmoothedParameter.h"



// methods to be implemented
void SmoothedParameter::setTargetValue(float newTarget)
{
    m_targetValue = newTarget;
}

float SmoothedParameter::getNextValue()
{
    m_currentValue += (m_targetValue - m_currentValue) * m_smoothingCoefficient;
    return m_currentValue;
}

void SmoothedParameter::reset(float initialValue)
{
    m_currentValue = initialValue;
    m_targetValue = initialValue;
}

void SmoothedParameter::setSmoothingTime(float timeMs, float sampleRate)
{
    // convert time in Ms to samples
    float numSamples = timeMs * sampleRate / 1000.0f;

    if (numSamples > 0.0f)
        m_smoothingCoefficient = 1.0f / numSamples;
    else
        m_smoothingCoefficient = 1.0f; // no smoothing
}
