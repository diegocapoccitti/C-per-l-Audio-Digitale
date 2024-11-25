/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Esercizio2AudioProcessor::Esercizio2AudioProcessor()
: AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                       ),
parameters(*this, nullptr, juce::Identifier("PARAMS"), createParameterLayout())
{
    parameters.addParameterListener("bypass", this);
}

Esercizio2AudioProcessor::~Esercizio2AudioProcessor()
{
    // Deregistrazione dei listener
    parameters.removeParameterListener("bypass", this);
}

juce::AudioProcessorValueTreeState::ParameterLayout Esercizio2AudioProcessor::createParameterLayout()
{
    // creiamo un vettore di unique_ptr<RangedAudioParameter>
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // Definizione del parametro di Bypass
    params.push_back(std::make_unique<juce::AudioParameterBool>(juce::ParameterID("bypass",1), "Bypass", false));

    return { params.begin(), params.end() };
}

void Esercizio2AudioProcessor::parameterChanged(const juce::String& parameterID, float newValue) 
{
    if (parameterID == "bypass")
    {
        bypassState = newValue;
    }
}

//==============================================================================
const juce::String Esercizio2AudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool Esercizio2AudioProcessor::acceptsMidi() const
{
    return false;
}

bool Esercizio2AudioProcessor::producesMidi() const
{
    return false;
}

bool Esercizio2AudioProcessor::isMidiEffect() const
{
    return false;
}

double Esercizio2AudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int Esercizio2AudioProcessor::getNumPrograms()
{
    return 1;
}

int Esercizio2AudioProcessor::getCurrentProgram()
{
    return 0;
}

void Esercizio2AudioProcessor::setCurrentProgram (int index)
{}

const juce::String Esercizio2AudioProcessor::getProgramName (int index)
{
    return {};
}

void Esercizio2AudioProcessor::changeProgramName (int index, const juce::String& newName)
{}

//==============================================================================
void Esercizio2AudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
}

void Esercizio2AudioProcessor::releaseResources()
{}

bool Esercizio2AudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    // Verifica che l'input e l'output siano sia mono che stereo
    const int numInputChannels = layouts.getMainInputChannelSet().size();
    const int numOutputChannels = layouts.getMainOutputChannelSet().size();

    // Controlla che il numero di canali sia uno dei seguenti:
    // - Mono (1 canale)
    // - Stereo (2 canali)
    bool isMonoOrStereoInput = (numInputChannels == 1 || numInputChannels == 2);
    bool isMonoOrStereoOutput = (numOutputChannels == 1 || numOutputChannels == 2);

    // Accetta solo layout che siano mono o stereo sia per ingresso che uscita
    return isMonoOrStereoInput && isMonoOrStereoOutput;
}

void Esercizio2AudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    if (bypassState) return;

    // Ottieni il numero di canali e di campioni nel buffer
    const int numChannels = buffer.getNumChannels();
    const int numSamples = buffer.getNumSamples();

    // Applica l’inversione di segno a ciascun campione di ogni canale
    for (int channel = 0; channel < numChannels; ++channel)
    {
        float* channelData = buffer.getWritePointer(channel);

        for (int sample = 0; sample < numSamples; ++sample)
        {
            channelData[sample] *= -1.f;  // Inverte la fase del campione
        }
    }
}


//==============================================================================
bool Esercizio2AudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* Esercizio2AudioProcessor::createEditor()
{
    return new juce::GenericAudioProcessorEditor(*this);
}

//==============================================================================
void Esercizio2AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    std::unique_ptr<juce::XmlElement> xml(parameters.copyState().createXml());
    copyXmlToBinary(*xml, destData);
}

void Esercizio2AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
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
    return new Esercizio2AudioProcessor();
}
