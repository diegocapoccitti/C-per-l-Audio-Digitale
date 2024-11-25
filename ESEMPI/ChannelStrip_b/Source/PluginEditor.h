/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Meter.h"

//==============================================================================
/**
*/
class ChannelStripAudioProcessorEditor  : public juce::AudioProcessorEditor, public juce::Timer

{
public:
    ChannelStripAudioProcessorEditor (ChannelStripAudioProcessor&);
    ~ChannelStripAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    
    void timerCallback() override;

private:
    //Knob equalizzatore
    juce::Slider freqHpKnob, freqBellKnob, qBellKnob, gainBellKnob, freqLpKnob;
    //Attachment equalizzatore
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> freqHpAtt, freqBellAtt, qBellAtt, gainBellAtt, freqLpAtt;
    
    //Knob compressore
    juce::Slider paralMixKnob, inputGainKnob, threshKnob, ratioKnob, attackKnob, releaseKnob;
    //Attachment equalizzatore
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> paralMixAtt, inputGainAtt, threshAtt, ratioAtt, attackAtt, releaseAtt;
    
    //Knob output Gain
    juce::Slider outputGainKnob;
    //Attachment equalizzatore
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> outputGainAtt;
    
    //Bypass Button
    juce::ToggleButton bypassButton;
    //Attachment bypass
    std::unique_ptr<juce::AudioProcessorValueTreeState::ButtonAttachment> bypassAtt;
    
    void createSlider(juce::Slider& knob, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& att, juce::String id, juce::String unit);
    
    //Meters
    Meter meterIn, meterOut;
    
    ChannelStripAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChannelStripAudioProcessorEditor)
};
