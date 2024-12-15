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
class Esempio7aAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Esempio7aAudioProcessorEditor (Esempio7aAudioProcessor&);
    ~Esempio7aAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider slider; // Dichiarazione dello slider
    
    Esempio7aAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Esempio7aAudioProcessorEditor)
};
