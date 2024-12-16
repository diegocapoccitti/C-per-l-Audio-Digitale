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
class Esempio7bAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Esempio7bAudioProcessorEditor (Esempio7bAudioProcessor&);
    ~Esempio7bAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider slider; // Dichiarazione dello slider
    juce::ToggleButton button {"Button"}; // Dichiarazione del toggle
    
    Esempio7bAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Esempio7bAudioProcessorEditor)
};
