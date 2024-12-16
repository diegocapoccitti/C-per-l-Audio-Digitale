/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class Esempio7eAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Esempio7eAudioProcessorEditor (Esempio7eAudioProcessor&);
    ~Esempio7eAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider gainSlider;
    juce::TextButton bypassButton;
    
    Esempio7eAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Esempio7eAudioProcessorEditor)
};
