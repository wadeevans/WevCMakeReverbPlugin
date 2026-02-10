// FixedAllPass.cpp
// Created by Wev on 10/02/2026

#include "FixedAllPass.h"

void FixedAllPass::prepare(double sampleRate, float delayMs, float feedbackGain)
{
    m_feedbackGain = feedbackGain;
    m_delayLine.prepare(sampleRate, delayMs, 0.0f);
    m_delayLine.setDelay(delayMs);
}

float FixedAllPass::processSample(float input)
{
    float delayInput = input + (m_delayOutput * m_feedbackGain);

    m_delayOutput = m_delayLine.processSample(delayInput);

    return (delayInput * -m_feedbackGain) + m_delayOutput;
}

void FixedAllPass::clear()
{
    m_delayLine.clear();
}