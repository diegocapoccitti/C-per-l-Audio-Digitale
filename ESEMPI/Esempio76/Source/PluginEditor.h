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
class Esempio76AudioProcessorEditor  : public juce::AudioProcessorEditor, private juce::Timer

{
public:
    Esempio76AudioProcessorEditor (Esempio76AudioProcessor&);
    ~Esempio76AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void timerCallback() override;

private:
    //Dichiarazione oggetto slider
    juce::Slider gainKnob;
    //Attachment gain
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;
    
    juce::Label gainLabel;
    juce::Label meterLabel;
    
    Esempio76AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Esempio76AudioProcessorEditor)
};
