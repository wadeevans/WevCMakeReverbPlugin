/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

// #include <JuceHeader.h> // old Projucer method of pulling in JUCE files
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class WevCMakeReverbPluginAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    WevCMakeReverbPluginAudioProcessorEditor (WevCMakeReverbPluginAudioProcessor&);
    ~WevCMakeReverbPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    WevCMakeReverbPluginAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (WevCMakeReverbPluginAudioProcessorEditor)
};
