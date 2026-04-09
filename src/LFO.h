#pragma once

class LFO
{
public:
    LFO() = default;
    ~LFO() = default;

    void prepare(double sampleRate);
    void setFrequency(float frequency);
    float processSample();
    void clear();

private:
    float m_sampleRate = 44100.0f;
    float m_phase = 0.0f;
    float m_frequency = 0.5f; // Default to 0.5 Hz
    const float m_twoPi = 6.28318530717958647692f;
};