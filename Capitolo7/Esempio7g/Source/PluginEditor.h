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
class TESTAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                   private juce::Timer
{
public:
    TESTAudioProcessorEditor (TESTAudioProcessor&);
    ~TESTAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // Callback del Timer: viene chiamata ogni ~30 ms per aggiornare il meter
    void timerCallback() override;

    // Riferimento al processor (necessario per leggere i parametri e il livello output)
    TESTAudioProcessor& audioProcessor;

    // Knob per il controllo del Gain
    juce::Slider gainKnob;
    juce::Label  gainLabel;

    // Attachment: collega automaticamente il Slider al parametro "gain" dell'APVTS
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> gainAttachment;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (TESTAudioProcessorEditor)
};
