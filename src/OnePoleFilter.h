#pragma once

class OnePoleFilter
{
public:
    OnePoleFilter() = default;
    ~OnePoleFilter() = default;

    void prepare(double sampleRate);
    void setFrequencyCutOffCoefficient(float frequencyHz);
    float processSample(float input);
    void clear();


private:
    float m_coefficient = 0.0f;
    float m_previousOutput = 0.0f;
    float m_sampleRate = 44100.0f;

};