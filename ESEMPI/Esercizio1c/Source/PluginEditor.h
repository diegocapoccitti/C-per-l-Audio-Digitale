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
class Esercizio1AudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Timer

{
public:
    Esercizio1AudioProcessorEditor (Esercizio1AudioProcessor&);
    ~Esercizio1AudioProcessorEditor() override;
    
    void timerCallback() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    //Slider Volume
    juce::Slider volKnob;
    //Attachment gain
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> volAttachment;
    
    Esercizio1AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Esercizio1AudioProcessorEditor)
};
