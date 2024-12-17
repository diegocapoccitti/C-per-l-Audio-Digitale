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
class Esercizio2AudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Timer


{
public:
    Esercizio2AudioProcessorEditor (Esercizio2AudioProcessor&);
    ~Esercizio2AudioProcessorEditor() override;
    
    void timerCallback() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //Bypass Button
    juce::ToggleButton bypassButton;
    //Attachment bypass
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> bypassAttachment;
    
    Esercizio2AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Esercizio2AudioProcessorEditor)
};
