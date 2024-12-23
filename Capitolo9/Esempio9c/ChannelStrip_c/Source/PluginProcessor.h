/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "RNBO_CodeHandler.h"
#include "GENExport/GenHandler.h"

//==============================================================================
/**
*/
class ChannelStripAudioProcessor  : public juce::AudioProcessor, public juce::AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    ChannelStripAudioProcessor();
    ~ChannelStripAudioProcessor() override;
    
    // Dichiarazione dell’APVTS
    juce::AudioProcessorValueTreeState parameters;
    
    //dichiarazione funzione del Listener
    void parameterChanged(const juce::String& parameterID, float     newValue) override;
    
    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    float getAndResetPeakLevelIn()
    {
        float levelIn = peakLevelIn.load();
        peakLevelIn.store(0.f);
        return levelIn;
    }
    
    float getAndResetPeakLevelOut()
    {
        float levelOut = peakLevelOut.load();
        peakLevelOut.store(0.f);
        return levelOut;
    }

private:
    //funzione per creare parametri
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
    //Variabili patch di gen~ e rnbo~
    GenHandler hpObj, bellObj, lpObj;
    RNBOcodeHandler compressorObj;
    
    //Bypass e Gain
    bool bypassVal;
    float gainVal;
    
    //Variabili picchi thread-safe
    std::atomic<float> peakLevelIn { 0.0f };
    std::atomic<float> peakLevelOut { 0.0f };
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ChannelStripAudioProcessor)
};
