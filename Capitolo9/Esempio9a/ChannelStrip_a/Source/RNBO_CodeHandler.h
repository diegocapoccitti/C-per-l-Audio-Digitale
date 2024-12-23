/*
  ==============================================================================

    RNBO_CodeHandler.h
    Created: 11 Nov 2024 10:16:32pm
    Author:  Diego Capoccitti

  ==============================================================================
*/

#include <JuceHeader.h>
#include "RNBO.h"

class RNBOcodeHandler
{
public:
    RNBOcodeHandler()
    {
        //Crea l'oggetto RNBO
        rnboObj = new RNBO::CoreObject();
    }
    
    ~RNBOcodeHandler()
    {
        //Distruggi l'oggetto RNBO
        rnboObj = nullptr;
    }

    void prepareToPlay(double in_sampleRate, int in_samplesPerBlock)
    {
        //Prepara RNBO con il sampleRate e il samplePerBlock
        rnboObj->prepareToProcess(in_sampleRate, in_samplesPerBlock);
        //Recupera il numero dei canali
        numInputs = (int)rnboObj->getNumInputChannels();
        numOutputs = (int)rnboObj->getNumOutputChannels();
    }
    
    void process(juce::AudioBuffer<float>& in_buffer)
    {
        auto dataBuffer = in_buffer.getArrayOfWritePointers();
        rnboObj->process(dataBuffer, numInputs, dataBuffer, numOutputs, in_buffer.getNumSamples());
    }
    
    void setParameter(juce::String param, float in_paramValue)
    {
        //Recupera l'indice del parametro dalla stringa
        RNBO::ParameterIndex parameterIndex = rnboObj->getParameterIndexForID(param.toStdString().c_str());
        //Modifica il parametro
        rnboObj->setParameterValue(parameterIndex, in_paramValue);
    }

private:
    //Oggetto RNBO
    RNBO::CoreObject* rnboObj;
    //numero canali
    int numInputs;
    int numOutputs;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(RNBOcodeHandler)
};
