/*
  ==============================================================================

    GenHandler.h
    Created: 6 Nov 2024 4:20:56pm
    Author:  Diego Capoccitti

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "gen_dsp/delay.h"

struct GenHandler
{
    GenHandler()
    {
        //Crea l'oggetto CommonState che si riferisce all'oggeto GEN chiamato m_cself, con parametri provvisori. Verranno poi sostituiti in prepareToPlay
        double sampleRate = 96000;
        int samplesPerBlock = 256;
        m_cself = (CommonState* )delay::create(sampleRate, samplesPerBlock);
        
        //recupera il numero dei canali dell'oggetto GEN
        numInputs = getNumInputs();
        numOutputs = getNumOutputs();
    }
    
    ~GenHandler()
    {
        //Distruggi l'oggetto GEN a chiusura
        if(m_cself) delay::destroy(m_cself);
        m_cself = nullptr;
    }
    
    int getNumInputs ()
    {
        return delay::num_inputs();
    }
    
    int getNumOutputs ()
    {
        return delay::num_outputs();
    }
    
    void reset()
    {
        //resetta l'oggetto GEN
        if(m_cself) delay::reset(m_cself);
    }
    
    void prepareGen(double sampleRate, int samplesPerBlock)
    {
        if(m_cself)
        {
            delay::destroy(m_cself);
            m_cself = (CommonState* )delay::create(sampleRate, samplesPerBlock);

            m_cself->sr = sampleRate;
            m_cself->vs = samplesPerBlock;
            
            delay::reset(m_cself);
            numInputs = delay::num_inputs();
            numOutputs = delay::num_outputs();
        }
        
        //PARAM ENUM
        for (int i = 0; i < getNumParameters(); ++i)
        {
            paramEnum[getParamName(i)] = i;
        }
    }

    
    void perform(juce::AudioBuffer<float>& in_buffer, juce::AudioBuffer<float>& dataOut_)
    {
        //converte AudioBuffer in puntatori multidimensionali da usare in delay::perform
        auto** buffData = (float**)in_buffer.getArrayOfWritePointers();
        auto** dataOutData = (float**)dataOut_.getArrayOfWritePointers();

        delay::perform(m_cself, buffData, numInputs, dataOutData, numOutputs, in_buffer.getNumSamples());
    }
    
    void setParameter(juce::String paramID, float in_paramValue)
    {
        delay::setparameter(m_cself, paramEnum[paramID], (t_sample)in_paramValue, NULL);
    }
    
    int getNumParameters ()
    {
        return delay::num_params();
    }
    
    juce::String getParamName(int i)
    {
        return delay::getparametername(m_cself, i);
    }
    
    CommonState* getGenState()
    {
        return m_cself;
    }
    
    
private:
    //STATE oggetto GEN
    CommonState *m_cself;
    //Numeri di input e output
    int numInputs;
    int numOutputs;
    //Param
    std::map<juce::String, int> paramEnum;
};
