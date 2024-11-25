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
class Esercizio3AudioProcessorEditor  : public juce::AudioProcessorEditor

{
public:
    Esercizio3AudioProcessorEditor (Esercizio3AudioProcessor&);
    ~Esercizio3AudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    
    Esercizio3AudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Esercizio3AudioProcessorEditor)
};
