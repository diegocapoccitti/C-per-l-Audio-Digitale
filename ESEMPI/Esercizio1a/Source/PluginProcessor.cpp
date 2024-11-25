/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Esercizio1AudioProcessor::Esercizio1AudioProcessor()
: AudioProcessor (BusesProperties()
                       .withOutput ("Output", juce::AudioChannelSet::mono(), true)
                  )

{
}

Esercizio1AudioProcessor::~Esercizio1AudioProcessor()
{
}

//==============================================================================
const juce::String Esercizio1AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Esercizio1AudioProcessor::acceptsMidi() const
{
    return false;
}

bool Esercizio1AudioProcessor::producesMidi() const
{
    return false;
}

bool Esercizio1AudioProcessor::isMidiEffect() const
{
    return false;
}

double Esercizio1AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Esercizio1AudioProcessor::getNumPrograms()
{
    return 1;
}

int Esercizio1AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Esercizio1AudioProcessor::setCurrentProgram (int index)
{}

const juce::String Esercizio1AudioProcessor::getProgramName (int index)
{
    return {};
}

void Esercizio1AudioProcessor::changeProgramName (int index, const juce::String& newName)
{}

//==============================================================================
void Esercizio1AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Calcola la magnitudo a partire dal valore in dB di “level” e salva il risultato in "mult"
    mult = std::pow(10.0f, level / 20.0f);
}

void Esercizio1AudioProcessor::releaseResources()
{}

bool Esercizio1AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    // Restituisce true solo output è mono
    return (layouts.getMainOutputChannelSet() == juce::AudioChannelSet::mono());
}

void Esercizio1AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    // Ottieni il numero di campioni nel buffer
    const int numSamples = buffer.getNumSamples();

    // Consideriamo solo il canale 0 perchè il plugin è mono
    float* channelData = buffer.getWritePointer(0);

    // Scorriamo tra i campioni del canale
    for (int sample = 0; sample < numSamples; ++sample)
     {

    // Per ogni campione calcoliamo il valore casuale
        float randNum = r.nextFloat() * 2.f - 1.f;
    
    //sostituiamo ogni campione con il numero casuale riscaldato di -20 dB
        channelData[sample] = randNum * mult;
     }

}

//==============================================================================
bool Esercizio1AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Esercizio1AudioProcessor::createEditor()
{
    return new Esercizio1AudioProcessorEditor (*this);
}

//==============================================================================
void Esercizio1AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
}

void Esercizio1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
}


//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Esercizio1AudioProcessor();
}
