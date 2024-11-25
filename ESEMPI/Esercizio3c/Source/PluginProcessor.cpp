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
                       ),
parameters(*this, nullptr, juce::Identifier("PARAMS"), createParameterLayout())
{
    coefficient = 0.f;
    previousSample[0] = 0.f ;// Canale sinistro (mono o stereo)
    previousSample[1] = 0.f ;// Canale destro (solo stereo)
    
    parameters.addParameterListener("bypass", this);
    parameters.addParameterListener("cutoffF", this);
}

Esercizio3AudioProcessor::~Esercizio3AudioProcessor()
{
    parameters.removeParameterListener("bypass", this);
    parameters.removeParameterListener("cutoffF", this);
}

juce::AudioProcessorValueTreeState::ParameterLayout Esercizio3AudioProcessor::createParameterLayout()
{
    // creiamo un vettore di unique_ptr<RangedAudioParameter>
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // Definizione del parametro di Bypass
    params.push_back(std::make_unique<juce::AudioParameterBool>(juce::ParameterID("bypass", 1), "Bypass", false));

    // Definizione del parametro della frequenza di taglio
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("cutoffF", 1), "CutoffF", juce::NormalisableRange<float>(20.0f, 20000.0f, 0.0f, 0.25f), 1000.f)); //NormalisableRange: min: 20, max: 20000, step: 0.f (continuo), skew: 0.25

    return { params.begin(), params.end() };
}

void Esercizio3AudioProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    if (parameterID == "bypass")
    {
        bypassState = newValue;
    }

    if (parameterID == "cutoffF")
    {
        cutoffFreq = newValue;
       // Calcola il coefficiente per il filtro passa-basso di primo ordine
       coefficient = (2.0f * juce::MathConstants<float>::pi * cutoffFreq) /
        (2.0f * juce::MathConstants<float>::pi * cutoffFreq + getSampleRate());
    }
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
    //Se il bypass è attivo il codice di processBlock si fermerà quiQ
    if (bypassState) return;
    
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
    return new Esercizio3AudioProcessorEditor(*this);
}

//==============================================================================
void Esercizio3AudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    std::unique_ptr<juce::XmlElement> xml(parameters.copyState().createXml());
    copyXmlToBinary(*xml, destData);
}

void Esercizio3AudioProcessor::setStateInformation (const void* data, int sizeInBytes)
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
    return new Esercizio3AudioProcessor();
}
