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
class TemplateAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    TemplateAudioProcessorEditor (TemplateAudioProcessor&);
    ~TemplateAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    TemplateAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TemplateAudioProcessorEditor)
};
