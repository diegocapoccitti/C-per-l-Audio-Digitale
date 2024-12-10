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
class Esercizio2AudioProcessorEditor  : public juce::AudioProcessorEditor

{
public:
    Esercizio2AudioProcessorEditor (Esercizio2AudioProcessor&);
    ~Esercizio2AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    Esercizio2AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Esercizio2AudioProcessorEditor)
};
