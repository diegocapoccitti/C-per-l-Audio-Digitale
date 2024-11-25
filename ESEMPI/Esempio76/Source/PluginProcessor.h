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
class Esempio76AudioProcessor  : public juce::AudioProcessor, public juce::AudioProcessorValueTreeState::Listener

{
public:
    //==============================================================================
    Esempio76AudioProcessor();
    ~Esempio76AudioProcessor() override;

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
    
    //APVTS
    juce::AudioProcessorValueTreeState parameters;
    //Funzione che restituisce i dB
    float getOutputdB();
    //funzione virtuale del Listener
    void parameterChanged(const juce::String& parameterID, float newValue) override;

private:
    //Funzione per creare i parametri
    juce::AudioProcessorValueTreeState::ParameterLayout createParameterLayout();
    //Variabili
    float level = -6.0f;
    float mult = 1.f;
    //Variabile atomica per comunicare con l'Editor
    std::atomic<float> outputLevel { 0.0f };
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Esempio76AudioProcessor)
};
