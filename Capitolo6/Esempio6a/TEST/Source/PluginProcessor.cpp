/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TESTAudioProcessor::TESTAudioProcessor()
         : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true) ),
                     parameters(*this, nullptr, juce::Identifier("PARAMS"), createParameterLayout())
                           
{
    parameters.addParameterListener("gain", this);
}

TESTAudioProcessor::~TESTAudioProcessor()
{
    // Deregistrazione dei listener
    parameters.removeParameterListener("gain", this);
}

juce::AudioProcessorValueTreeState::ParameterLayout TESTAudioProcessor::createParameterLayout()
{
   // creiamo un vettore di unique_ptr<RangedAudioParameter>
   std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

   // Definizione del parametro di Gain
params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("gain", 1), "Gain", -60.0f, 12.0f, 0.f));

   return { params.begin(), params.end() };
}

void TESTAudioProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    if (parameterID == "gain")
    {
        level = newValue;
    // Calcola la magnitudo a partire dal valore in dB di “level” e salva il risultato in "mult"
            mult = std::pow(10.0f, level / 20.0f);
    }

}

//==============================================================================
const juce::String TESTAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool TESTAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool TESTAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool TESTAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double TESTAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int TESTAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int TESTAudioProcessor::getCurrentProgram()
{
    return 0;
}

void TESTAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String TESTAudioProcessor::getProgramName (int index)
{
    return {};
}

void TESTAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void TESTAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Calcola la magnitudo a partire dal valore in dB di “level” e salva il risultato in "mult"
    mult = std::pow(10.0f, level / 20.0f);
}

void TESTAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool TESTAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    // Verifica che l'input e l'output abbiano entrambi esattamente due canali (stereo)
    const bool isStereoInput = (layouts.getMainInputChannelSet() == juce::AudioChannelSet::stereo());
    const bool isStereoOutput = (layouts.getMainOutputChannelSet() == juce::AudioChannelSet::stereo());

    // Restituisce true solo se entrambi i bus sono stereo
    return isStereoInput && isStereoOutput;
}
#endif

void TESTAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    // Ottieni il numero di canali e di campioni nel buffer
    const int numChannels = buffer.getNumChannels();
    const int numSamples = buffer.getNumSamples();

    // Applica l'attenuazione di 6 dB a ciascun campione di ogni canale
    for (int channel = 0; channel < numChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);

        for (int sample = 0; sample < numSamples; ++sample)
        {
            channelData[sample] *= mult;  // Riduce il segnale di 6 dB
        }
    }
}

//==============================================================================
bool TESTAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* TESTAudioProcessor::createEditor()
{
    return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void TESTAudioProcessor::getStateInformation(juce::MemoryBlock& destData)
{
    std::unique_ptr<juce::XmlElement> xml(parameters.copyState().createXml());
    copyXmlToBinary(*xml, destData);
}

void TESTAudioProcessor::setStateInformation(const void* data, int sizeInBytes)
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
    return new TESTAudioProcessor();
}
