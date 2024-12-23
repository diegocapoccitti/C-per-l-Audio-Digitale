/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EsempioRNBOAudioProcessor::EsempioRNBOAudioProcessor()
     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::mono(), true)
                       .withOutput ("Output", juce::AudioChannelSet::mono(), true)
                       ),
parameters(*this, nullptr, juce::Identifier("PARAMS"), createParameterLayout())
{
    parameters.addParameterListener("delaytime", this);
    parameters.addParameterListener("feedback", this);
}

EsempioRNBOAudioProcessor::~EsempioRNBOAudioProcessor()
{
    // Deregistrazione dei listener
    parameters.removeParameterListener("delaytime", this);
    parameters.removeParameterListener("feedback", this);
}

juce::AudioProcessorValueTreeState::ParameterLayout EsempioRNBOAudioProcessor::createParameterLayout()
{
    // creiamo un vettore di unique_ptr<RangedAudioParameter>
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // Definizione del parametro di dump
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("delaytime",1), "Delaytime", 1.0f, 2000.0f, 220.f));
    // Definizione del parametro di drywet
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("feedback",1), "Feedback", 0.0f, 1.0f, 0.5f));
    
    return { params.begin(), params.end() };
}

void EsempioRNBOAudioProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    rnboDelay.setParameter(parameterID, newValue);
}

//==============================================================================
const juce::String EsempioRNBOAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool EsempioRNBOAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool EsempioRNBOAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool EsempioRNBOAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double EsempioRNBOAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int EsempioRNBOAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int EsempioRNBOAudioProcessor::getCurrentProgram()
{
    return 0;
}

void EsempioRNBOAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String EsempioRNBOAudioProcessor::getProgramName (int index)
{
    return {};
}

void EsempioRNBOAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void EsempioRNBOAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    rnboDelay.prepareToPlay(sampleRate, samplesPerBlock);
}

void EsempioRNBOAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

bool EsempioRNBOAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono())
        return false;
    
    return true;
}

void EsempioRNBOAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    rnboDelay.process(buffer);
}

//==============================================================================
bool EsempioRNBOAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* EsempioRNBOAudioProcessor::createEditor()
{
    return new juce::GenericAudioProcessorEditor (*this);
}

//==============================================================================
void EsempioRNBOAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    std::unique_ptr<juce::XmlElement> xml(parameters.copyState().createXml());
    copyXmlToBinary(*xml, destData);
}

void EsempioRNBOAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
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
    return new EsempioRNBOAudioProcessor();
}
