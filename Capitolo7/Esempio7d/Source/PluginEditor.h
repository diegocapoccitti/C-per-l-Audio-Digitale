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
class Esempio7dAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Esempio7dAudioProcessorEditor (Esempio7dAudioProcessor&);
    ~Esempio7dAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    juce::Slider slider; // Dichiarazione dello slider
    juce::ToggleButton button {"Button"}; // Dichiarazione del toggle
    juce::ComboBox myComboBox; // Dichiarazione del combobox
    juce::Label myLabel; // Dichiarazione della Label
    
    Esempio7dAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Esempio7dAudioProcessorEditor)
};
