

#pragma once

class SmoothedParameter
{
public:
    SmoothedParameter() = default;
    ~SmoothedParameter() = default;

    // methods to be implemented
    void setTargetValue(float newValue);
    float getNextValue();
    void reset(float initialValue);
    void setSmoothingTime(float timeMs, float sampleRate);

private:
    float m_currentValue = 0.0f;
    float m_targetValue = 0.0f;
    float m_smoothingCoefficient = 0.0f; // Calculated based on smoothing time and sample rate
};
