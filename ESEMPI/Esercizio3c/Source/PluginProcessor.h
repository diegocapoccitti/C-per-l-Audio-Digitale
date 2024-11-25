/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

//==============================================================================
/**
*/
class Esercizio3AudioProcessor  : public juce::AudioProcessor, public juce::AudioProcessorValueTreeState::Listener
{
public:
    //==============================================================================
    Esercizio3AudioProcessor();
    ~Esercizio3AudioProcessor() override;
    
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

private:
    //funzione per creare parametri
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    
    float cutoffFreq = 1000.f;
    float coefficient;  // Coefficiente del filtro float
    float previousSample[2]; // Valori dei campioni precedenti per i canali (due per stereo)
    bool bypassState; //memorizza parametro bypass
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Esercizio3AudioProcessor)
};
