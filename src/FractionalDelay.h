#pragma once

class FractionalDelay
{
public:
    FractionalDelay() = default;
    ~FractionalDelay() = default;

    void prepare(double sampleRate, int maxDelayInSamples);
    void setDelay(float delayMs);
    float processSample(float input);
    void clear();

private:
};