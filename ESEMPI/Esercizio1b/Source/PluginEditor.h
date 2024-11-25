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
class Esercizio1AudioProcessorEditor  : public juce::AudioProcessorEditor

{
public:
    Esercizio1AudioProcessorEditor (Esercizio1AudioProcessor&);
    ~Esercizio1AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    Esercizio1AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Esercizio1AudioProcessorEditor)
};
