// VariableAllPass.cpp
// Created by Wev on 2026-02-11.

#include "VariableAllPass.h"

void VariableAllPass::prepare(double sampleRate, float maxDelayMs, float feedbackGain, float delayMs)
{
    m_feedbackGain = feedbackGain;
    float smoothingMs = maxDelayMs * 0.05;
    m_delayLine.prepare(sampleRate, maxDelayMs, smoothingMs);

    // If delayMs not specified, use maxDelayMs
    float actualDelay = (delayMs < 0.0f) ? maxDelayMs : delayMs;
    m_delayLine.setDelay(actualDelay);
}

float VariableAllPass::processSample(float input)
{
    float delayInput = input + (m_delayOutput * m_feedbackGain);

    m_delayOutput = m_delayLine.processSample(delayInput);

    return (delayInput * -m_feedbackGain) + m_delayOutput;
}

void VariableAllPass::clear()
{
    m_delayLine.clear();
    m_delayOutput = 0.0f; // Also reset the output
}