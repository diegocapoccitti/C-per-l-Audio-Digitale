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
class Esercizio3AudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Timer

{
public:
    Esercizio3AudioProcessorEditor (Esercizio3AudioProcessor&);
    ~Esercizio3AudioProcessorEditor() override;
    
    void timerCallback() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //Knob frequenza di taglio
    juce::Slider freqKnob;
    //Attachment freq di taglio
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> freqAttachment;
    //Bypass Button
    juce::ToggleButton bypassButton;
    //Attachment bypass
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> bypassAttachment;
    
    Esercizio3AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Esercizio3AudioProcessorEditor)
};
