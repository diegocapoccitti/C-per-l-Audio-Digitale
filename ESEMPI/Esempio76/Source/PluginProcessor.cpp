/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Esempio76AudioProcessor::Esempio76AudioProcessor()
        : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                          ),
parameters(*this, nullptr, juce::Identifier("PARAMS"), createParameterLayout())

{
    parameters.addParameterListener("gain", this);
}

Esempio76AudioProcessor::~Esempio76AudioProcessor()
{
    // Deregistrazione dei listener
    parameters.removeParameterListener("gain", this);

}

void Esempio76AudioProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    if (parameterID == "gain")
    {
        level = newValue;
        // Calcola la magnitudo a partire dal valore in dB di “level” e salva il risultato in "mult"
        mult = std::pow(10.0f, level / 20.0f);
    }

}

//==============================================================================
const juce::String Esempio76AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Esempio76AudioProcessor::acceptsMidi() const
{
    return false;
}

bool Esempio76AudioProcessor::producesMidi() const
{
    return false;
}

bool Esempio76AudioProcessor::isMidiEffect() const
{
    return false;
}

double Esempio76AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Esempio76AudioProcessor::getNumPrograms()
{
    return 1;
}

int Esempio76AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Esempio76AudioProcessor::setCurrentProgram (int index)
{}

const juce::String Esempio76AudioProcessor::getProgramName (int index)
{
    return {};
}

void Esempio76AudioProcessor::changeProgramName (int index, const juce::String& newName)
{}

//==============================================================================
void Esempio76AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{}

void Esempio76AudioProcessor::releaseResources()
{}

bool Esempio76AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    return true;
}

void Esempio76AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    // Ottieni il numero di canali e di campioni nel buffer
    const int numChannels = buffer.getNumChannels();
    const int numSamples = buffer.getNumSamples();
    
    //Azzera il outputLevel
    outputLevel.store(0.f);

    // Applica l'attenuazione a ciascun campione di ogni canale
    for (int channel = 0; channel < numChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);

        for (int sample = 0; sample < numSamples; ++sample)
        {
            channelData[sample] *= mult;  // applica il gain
            
            //Se il campione è più grande di outputLevel, outputLevel assume il suo valore
            if (channelData[sample] > outputLevel.load()) outputLevel.store(channelData[sample]);
        }
    }
}

float Esempio76AudioProcessor::getOutputdB()
{
    return juce::Decibels::gainToDecibels(outputLevel.load());
}

//==============================================================================
bool Esempio76AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Esempio76AudioProcessor::createEditor()
{
    return new Esempio76AudioProcessorEditor (*this);
}

//==============================================================================
void Esempio76AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    std::unique_ptr<juce::XmlElement> xml(parameters.copyState().createXml());
    copyXmlToBinary(*xml, destData);
}

void Esempio76AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    if (xml != nullptr && xml->hasTagName(parameters.state.getType()))
    {
        parameters.replaceState(juce::ValueTree::fromXml(*xml));
    }
}

juce::AudioProcessorValueTreeState::ParameterLayout Esempio76AudioProcessor::createParameterLayout()
{
    // creiamo un vettore di unique_ptr<RangedAudioParameter>
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // Definizione del parametro di Gain
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("gain", 1), "Gain", -60.0f, 12.0f, 0.f));

    return { params.begin(), params.end() };
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Esempio76AudioProcessor();
}
