/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ChannelStripAudioProcessor::ChannelStripAudioProcessor()
: AudioProcessor (BusesProperties()
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                       ),
parameters(*this, nullptr, juce::Identifier("PARAMS"), createParameterLayout())

{
    parameters.addParameterListener("freq_hp", this);
    parameters.addParameterListener("freq_bell", this);
    parameters.addParameterListener("gain_bell", this);
    parameters.addParameterListener("q_bell", this);
    parameters.addParameterListener("freq_lp", this);
    parameters.addParameterListener("parallel_mix", this);
    parameters.addParameterListener("input_gain", this);
    parameters.addParameterListener("threshold", this);
    parameters.addParameterListener("ratio", this);
    parameters.addParameterListener("attack", this);
    parameters.addParameterListener("release", this);
    parameters.addParameterListener("output_gain", this);
    parameters.addParameterListener("bypass", this);
}

ChannelStripAudioProcessor::~ChannelStripAudioProcessor()
{
    parameters.removeParameterListener("freq_hp", this);
    parameters.removeParameterListener("freq_bell", this);
    parameters.removeParameterListener("gain_bell", this);
    parameters.removeParameterListener("q_bell", this);
    parameters.removeParameterListener("freq_lp", this);
    parameters.removeParameterListener("parallel_mix", this);
    parameters.removeParameterListener("input_gain", this);
    parameters.removeParameterListener("threshold", this);
    parameters.removeParameterListener("ratio", this);
    parameters.removeParameterListener("attack", this);
    parameters.removeParameterListener("release", this);
    parameters.removeParameterListener("output_gain", this);
    parameters.removeParameterListener("bypass", this);
}

juce::AudioProcessorValueTreeState::ParameterLayout ChannelStripAudioProcessor::createParameterLayout()
{
    //valore dello skew factor comune
    float skewfactor = 0.25f;
    
    //valore dello step
    float step = 0.01f;
    
    // creiamo un vettore di unique_ptr<RangedAudioParameter>
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;

    // Definizione del parametro della frequenza di taglio filtro HP
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("freq_hp", 1), "Freq_hp", juce::NormalisableRange<float>(20.0f, 20000.0f, step, skewfactor), 20.f, "Hz"));
 
    // Definizione del parametro della frequenza di taglio filtro Bell
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("freq_bell", 1), "Freq_bell", juce::NormalisableRange<float>(20.0f, 20000.0f, step, skewfactor), 1000.f, "Hz"));
    
    // Definizione del parametro gain filtro Bell
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("gain_bell", 1), "Gain_bell", juce::NormalisableRange<float>(0.01f, 20.0f, step, skewfactor), 1.f));
    
    // Definizione del parametro Q filtro Bell
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("q_bell", 1), "Q_bell", juce::NormalisableRange<float>(0.01f, 50.0f, step, skewfactor), 1.f));
    
    // Definizione del parametro della frequenza di taglio filtro HP
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("freq_lp", 1), "Freq_lp", juce::NormalisableRange<float>(20.0f, 20000.0f, step, skewfactor), 20000.f, "Hz"));
    
    // Definizione del parametro parallel del Compressore
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("parallel_mix", 1), "Parallel_mix", juce::NormalisableRange<float>(0.0f, 1.0f, step, 1.f), 1.f));
    
    // Definizione del parametro input gain del Compressore
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("input_gain", 1), "Input_gain", juce::NormalisableRange<float>(0.0f, 100.0f, step, 1.f), 0.f, "dB"));
    
    // Definizione del parametro threshold del Compressore
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("threshold", 1), "Threshold", juce::NormalisableRange<float>(-100.0f, 10.0f, step, 1.f), -30.f, "dB"));
    
    // Definizione del parametro ratio del Compressore
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("ratio", 1), "Ratio", juce::NormalisableRange<float>(0.0f, 100.0f, step, 1.f), 3.f));
    
    // Definizione del parametro attack del Compressore
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("attack", 1), "Attack", juce::NormalisableRange<float>(0.0f, 1000.0f, step, skewfactor), 5.f, "ms"));
    
    // Definizione del parametro release del Compressore
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("release", 1), "Release", juce::NormalisableRange<float>(0.0f, 1000.0f, step, skewfactor), 50.f, "ms"));
    
    // Definizione del parametro output gain
    params.push_back(std::make_unique<juce::AudioParameterFloat>(juce::ParameterID("output_gain", 1), "Output_gain", juce::NormalisableRange<float>(-60.0f, 12.0f, step, 2.f), 0.f, "dB"));
    
    // Definizione del parametro Bypass
    params.push_back(std::make_unique<juce::AudioParameterBool>(juce::ParameterID("bypass", 1), "Bypass", false));

    return { params.begin(), params.end() };
}

void ChannelStripAudioProcessor::parameterChanged(const juce::String& parameterID, float newValue)
{
    if (parameterID == "freq_hp")
    {
        //Recupera il valore del parametro
        float hpFreq = *parameters.getRawParameterValue("freq_hp");
        
        //Calcola i coefficienti
        float omega = hpFreq * juce::MathConstants<float>::twoPi /getSampleRate();
        float sn = std::sin(omega);
        float cs = std::cos(omega);
        float q = 1.f; //Fattore Q fissato a 1
        float alpha  = sn *0.5/ q;
        
        float b0 = 1.f/(1.f + alpha);
        float a2 = ((1.f + cs) * 0.5f) * b0;
        float a0 = a2;
        float a1 = -(1.f + cs) * b0;
        float b1 = (-2.f * cs) * b0;
        float b2 = (1.f - alpha) * b0;
        
        //Aggiorna i parametri interni
        hpObj.setParameter("a0", a0);
        hpObj.setParameter("a1", a1);
        hpObj.setParameter("a2", a2);
        hpObj.setParameter("b1", b1);
        hpObj.setParameter("b2", b2);
    }
    
    if (parameterID == "freq_bell" || parameterID == "gain_bell" || parameterID == "q_bell")
    {
        //Recupera i valori del filtro
        float bellFreq = *parameters.getRawParameterValue("freq_bell");
        float bellGain = *parameters.getRawParameterValue("gain_bell");
        float bellQ = *parameters.getRawParameterValue("q_bell");
        
        //Calcola i coefficienti
        float omega = bellFreq * juce::MathConstants<float>::twoPi /getSampleRate();
        float sn = std::sin(omega);
        float cs = std::cos(omega);
        float q = bellQ; //Fattore Q
        float alpha  = sn *0.5/ q;
        
        float A = sqrt(bellGain);
        float one_over_A = 1.f/A;
        
        float b0 = 1.f/(1.f + alpha*one_over_A);
        float a0 = (1.f + alpha*A) * b0;
        float b1 = (-2.f * cs) * b0;
        float a1 = b1;
        float a2 = (1.f - alpha*A) * b0;
        float b2 = (1.f - alpha*one_over_A) * b0;
        
        //Aggiorna i parametri interni
        bellObj.setParameter("a0", a0);
        bellObj.setParameter("a1", a1);
        bellObj.setParameter("a2", a2);
        bellObj.setParameter("b1", b1);
        bellObj.setParameter("b2", b2);
    }
    
    if (parameterID == "freq_lp")
    {
        //Recupera il valore del parametro
        float lpFreq = *parameters.getRawParameterValue("freq_lp");
        
        //Calcola i coefficienti
        float omega = lpFreq * juce::MathConstants<float>::twoPi /getSampleRate();
        float sn = std::sin(omega);
        float cs = std::cos(omega);
        float q = 1.f; //Fattore Q pari a 1
        float one_over_Q = 1.f/q;
        float alpha = sn * 0.5 * one_over_Q;
        
        float b0 = 1.f/(1.f + alpha);
        float a2 = ((1.f - cs) * 0.5f) * b0;
        float a0 = a2;
        float a1 = (1.f - cs) * b0;
        float b1 = (-2.f * cs) * b0;
        float b2 = (1.f - alpha) * b0;
        
        //Aggiorna i parametri interni
        lpObj.setParameter("a0", a0);
        lpObj.setParameter("a1", a1);
        lpObj.setParameter("a2", a2);
        lpObj.setParameter("b1", b1);
        lpObj.setParameter("b2", b2);
    }
    
    if (parameterID == "parallel_mix" || parameterID == "input_gain" || parameterID == "threshold" || parameterID == "ratio" || parameterID == "attack" || parameterID == "release")
    {
        compressorObj.setParameter(parameterID, newValue);
    }
    
    if (parameterID == "bypass")
    {
        bypassVal = newValue;
    }
    
    if (parameterID == "output_gain")
    {
        gainVal = juce::Decibels::decibelsToGain(newValue);
    }
}


//==============================================================================
const juce::String ChannelStripAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool ChannelStripAudioProcessor::acceptsMidi() const
{
    return false;
}

bool ChannelStripAudioProcessor::producesMidi() const
{
    return false;
}

bool ChannelStripAudioProcessor::isMidiEffect() const
{
    return false;
}

double ChannelStripAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int ChannelStripAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int ChannelStripAudioProcessor::getCurrentProgram()
{
    return 0;
}

void ChannelStripAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String ChannelStripAudioProcessor::getProgramName (int index)
{
    return {};
}

void ChannelStripAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void ChannelStripAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    //Preparazione oggetti gen~
    hpObj.prepareGen(sampleRate, samplesPerBlock);
    bellObj.prepareGen(sampleRate, samplesPerBlock);
    lpObj.prepareGen(sampleRate, samplesPerBlock);
    
    //Preparazione oggetto rnbo~
    compressorObj.prepareToPlay(sampleRate, samplesPerBlock);
}

void ChannelStripAudioProcessor::releaseResources()
{

}

bool ChannelStripAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;
    return true;
}

void ChannelStripAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    //Peak Meter IN
    float localPeakIn = 0.0f;
    // Trova il picco del buffer corrente
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        const float* channelData = buffer.getReadPointer(channel);
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            localPeakIn = std::max(localPeakIn, std::abs(channelData[sample]));
        }
    }
    // Aggiorna il picco globale In
    peakLevelIn = std::max(peakLevelIn.load(), localPeakIn);
//================================
    
    //Bypass
    if (bypassVal)
    {
        peakLevelOut = peakLevelIn.load();
        return;
    }
    
    //Equalizzatore
    hpObj.perform(buffer, buffer);
    bellObj.perform(buffer, buffer);
    lpObj.perform(buffer, buffer);
    
    //Compressore
    compressorObj.process(buffer);
    
    //Out Gain
    buffer.applyGain(gainVal);
    
 //================================
    //Peak Meter OUT
    float localPeakOut = 0.0f;
    // Trova il picco del buffer corrente
    for (int channel = 0; channel < buffer.getNumChannels(); ++channel)
    {
        const float* channelData = buffer.getReadPointer(channel);
        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            localPeakOut = std::max(localPeakOut, std::abs(channelData[sample]));
        }
    }
    // Aggiorna il picco globale In
    peakLevelOut = std::max(peakLevelOut.load(), localPeakOut);
}

//==============================================================================
bool ChannelStripAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* ChannelStripAudioProcessor::createEditor()
{
    return new ChannelStripAudioProcessorEditor (*this);
}

//==============================================================================
void ChannelStripAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    std::unique_ptr<juce::XmlElement> xml(parameters.copyState().createXml());
    copyXmlToBinary(*xml, destData);
}

void ChannelStripAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
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
    return new ChannelStripAudioProcessor();
}
