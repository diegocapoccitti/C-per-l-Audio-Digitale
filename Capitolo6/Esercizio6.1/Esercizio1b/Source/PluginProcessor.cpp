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
                  ),
parameters(*this, nullptr, juce::Identifier("PARAMS"), createParameterLayout())

{
    parameters.addParameterListener("vol", this);
}

Esercizio1AudioProcessor::~Esercizio1AudioProcessor()
{
    // Deregistrazione dei listener
    parameters.removeParameterListener("vol", this);
}

juce::AudioProcessorValueTreeState::ParameterLayout Esercizio1AudioProcessor::createParameterLayout()
{
    // creiamo un vettore di unique_ptr<RangedAudioParameter>
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // Definizione del parametro di Volume
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("vol",1), "Vol", -60.0f, 0.0f, -20.f));

    return { params.begin(), params.end() };
}

void Esercizio1AudioProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    if (parameterID == "vol")
    {
        level = newValue;
    // Calcola la magnitudo a partire dal valore in dB di “level” e salva il risultato in "mult"
        mult = std::pow(10.0f, level / 20.0f);
    }
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
    return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void Esercizio1AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    std::unique_ptr<juce::XmlElement> xml(parameters.copyState().createXml());
    copyXmlToBinary(*xml, destData);
}

void Esercizio1AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    std::unique_ptr<juce::XmlElement> xml(getXmlFromBinary(data, sizeInBytes));
    if (xml != nullptr && xml->hasTagName(parameters.state.getType()))
    {
        parameters.replaceState(juce::ValueTree::fromXml(*xml));
    }
}


//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new Esercizio1AudioProcessor();
}
