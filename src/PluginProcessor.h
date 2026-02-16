/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

// #include <JuceHeader.h> // old Projucer method of pulling in JUCE files

// new CMake method of pulling in JUCE files
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_devices/juce_audio_devices.h>
#include <juce_gui_basics/juce_gui_basics.h>

#include "FractionalDelay.h"
#include "FixedAllPass.h"
#include "VariableAllPass.h"
#include "OnePoleFilter.h"
#include "FeedbackCombFilter.h"
#include "SchroederReverb.h"
#include <array>

//==============================================================================
/**
*/
class WevCMakeReverbPluginAudioProcessor  : public juce::AudioProcessor
{
public:
    //==============================================================================
    WevCMakeReverbPluginAudioProcessor();
    ~WevCMakeReverbPluginAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:

    juce::AudioProcessorValueTreeState apvts{ *this, nullptr, "Parameters", createParameterLayout() };

    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();

    std::array<FractionalDelay, 2> m_delays;
    // std::array<FixedAllPass, 2> m_allpass;
    std::array<VariableAllPass, 2> m_allpass;
    std::array<OnePoleFilter, 2> m_dampingFilters;
    std::array<FeedbackCombFilter, 2> m_combFilters;
    std::array<SchroederReverb, 2> m_reverbs;

    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WevCMakeReverbPluginAudioProcessor)
};
