/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Esercizio3AudioProcessor::Esercizio3AudioProcessor()
: AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                       )

{
    coefficient = 0.f;
    previousSample[0] = 0.f ;// Canale sinistro (mono o stereo)
    previousSample[1] = 0.f ;// Canale destro (solo stereo)
}

Esercizio3AudioProcessor::~Esercizio3AudioProcessor()
{
}

//==============================================================================
const juce::String Esercizio3AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Esercizio3AudioProcessor::acceptsMidi() const
{
    return false;
}

bool Esercizio3AudioProcessor::producesMidi() const
{
    return false;
}

bool Esercizio3AudioProcessor::isMidiEffect() const
{
    return false;
}

double Esercizio3AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Esercizio3AudioProcessor::getNumPrograms()
{
    return 1;
}

int Esercizio3AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Esercizio3AudioProcessor::setCurrentProgram (int index)
{}

const juce::String Esercizio3AudioProcessor::getProgramName (int index)
{
    return {};
}

void Esercizio3AudioProcessor::changeProgramName (int index, const juce::String& newName)
{}

//==============================================================================
void Esercizio3AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Calcola il coefficiente per il filtro passa-basso di primo ordine
    coefficient = (2.0f * juce::MathConstants<float>::pi * cutoffFreq) /
                  (2.0f * juce::MathConstants<float>::pi * cutoffFreq + sampleRate);
}

void Esercizio3AudioProcessor::releaseResources()
{}

bool Esercizio3AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    // Accetta solo layout mono e stereo
     const int numInputChannels = layouts.getMainInputChannelSet().size();
     const int numOutputChannels = layouts.getMainOutputChannelSet().size();
     bool isMonoOrStereoInput = (numInputChannels == 1 || numInputChannels == 2);
     bool isMonoOrStereoOutput = (numOutputChannels == 1 || numOutputChannels == 2);
     return isMonoOrStereoInput && isMonoOrStereoOutput;
}

void Esercizio3AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    const int numChannels = buffer.getNumChannels();
    const int numSamples = buffer.getNumSamples();

    for (int channel = 0; channel < numChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);

        for (int sample = 0; sample < numSamples; ++sample)
        {
            // Applica il filtro passa-basso di primo ordine
            channelData[sample] = coefficient * channelData[sample] +
                                  (1.0f - coefficient) * previousSample[channel];

            // Salva il campione corrente come campione precedente per il prossimo ciclo
            previousSample[channel] = channelData[sample];
        }
    }
}

//==============================================================================
bool Esercizio3AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Esercizio3AudioProcessor::createEditor()
{
    return new Esercizio3AudioProcessorEditor (*this);
}

//==============================================================================
void Esercizio3AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
}

void Esercizio3AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
}


//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Esercizio3AudioProcessor();
}
