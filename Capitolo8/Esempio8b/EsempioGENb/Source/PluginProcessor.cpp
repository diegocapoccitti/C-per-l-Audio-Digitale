/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EsempioGENAudioProcessor::EsempioGENAudioProcessor()
     : AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                       ),
parameters(*this, nullptr, juce::Identifier("PARAMS"), createParameterLayout())

{
    parameters.addParameterListener("dump", this);
    parameters.addParameterListener("drywet", this);
    parameters.addParameterListener("delay", this);
}

EsempioGENAudioProcessor::~EsempioGENAudioProcessor()
{
    // Deregistrazione dei listener
    parameters.removeParameterListener("dump", this);
    parameters.removeParameterListener("drywet", this);
    parameters.removeParameterListener("delay", this);
}

juce::AudioProcessorValueTreeState::ParameterLayout EsempioGENAudioProcessor::createParameterLayout()
{
    // creiamo un vettore di unique_ptr<RangedAudioParameter>
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // Definizione del parametro di dump
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("dump",1), "Dump", 0.0f, 1.0f, 0.25f));
    // Definizione del parametro di drywet
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("drywet",1), "Drywet", 0.0f, 1.0f, 0.5f));
    // Definizione del parametro di delay
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("delay", 1), "Delay", juce::NormalisableRange<float>(0.0f, 10000.0f, 0.0f, 0.25f), 1000.f)); //skewFactor 0.25

    return { params.begin(), params.end() };
}

void EsempioGENAudioProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    genObj.setParameter(parameterID, newValue);
}

//==============================================================================
const juce::String EsempioGENAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool EsempioGENAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool EsempioGENAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool EsempioGENAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double EsempioGENAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int EsempioGENAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int EsempioGENAudioProcessor::getCurrentProgram()
{
    return 0;
}

void EsempioGENAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String EsempioGENAudioProcessor::getProgramName (int index)
{
    return {};
}

void EsempioGENAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void EsempioGENAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    genObj.prepareGen(sampleRate, samplesPerBlock);
}

void EsempioGENAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool EsempioGENAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void EsempioGENAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    genObj.perform(buffer, buffer);
}

//==============================================================================
bool EsempioGENAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* EsempioGENAudioProcessor::createEditor()
{
    return new juce::GenericAudioProcessorEditor (*this);
}

//==============================================================================
void EsempioGENAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    std::unique_ptr<juce::XmlElement> xml(parameters.copyState().createXml());
    copyXmlToBinary(*xml, destData);
}

void EsempioGENAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
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
    return new EsempioGENAudioProcessor();
}
