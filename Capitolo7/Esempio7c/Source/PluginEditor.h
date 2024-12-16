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
class Esempio7cAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Esempio7cAudioProcessorEditor (Esempio7cAudioProcessor&);
    ~Esempio7cAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider slider; // Dichiarazione dello slider
    juce::ToggleButton button {"Button"}; // Dichiarazione del toggle
    juce::ComboBox myComboBox; // Dichiarazione del combobox
    
    Esempio7cAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Esempio7cAudioProcessorEditor)
};
