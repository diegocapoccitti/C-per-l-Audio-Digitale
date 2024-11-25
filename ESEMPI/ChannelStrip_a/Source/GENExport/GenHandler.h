/*
  ==============================================================================

    GenHandler.h
    Created: 11 Nov 2024 9:57:05pm
    Author:  Diego Capoccitti

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "gen_dsp/biquadStereo.h"

struct GenHandler
{
    GenHandler()
    {
        //Crea l'oggetto CommonState che si riferisce all'oggeto GEN chiamato m_cself, con parametri provvisori. Verranno poi sostituiti in prepareToPlay
        double sampleRate = 96000;
        int samplesPerBlock = 256;
        m_cself = (CommonState* )biquadStereo::create(sampleRate, samplesPerBlock);
        
        //recupera il numero dei canali dell'oggetto GEN
        numInputs = getNumInputs();
        numOutputs = getNumOutputs();
    }
    
    ~GenHandler()
    {
        //Distruggi l'oggetto GEN a chiusura
        if(m_cself) biquadStereo::destroy(m_cself);
        m_cself = nullptr;
    }
    
    int getNumInputs ()
    {
        return biquadStereo::num_inputs();
    }
    
    int getNumOutputs ()
    {
        return biquadStereo::num_outputs();
    }
    
    void reset()
    {
        //resetta l'oggetto GEN
        if(m_cself) biquadStereo::reset(m_cself);
    }
    
    void prepareGen(double sampleRate, int samplesPerBlock)
    {
        if(m_cself)
        {
            biquadStereo::destroy(m_cself);
            m_cself = (CommonState* )biquadStereo::create(sampleRate, samplesPerBlock);

            m_cself->sr = sampleRate;
            m_cself->vs = samplesPerBlock;
            
            biquadStereo::reset(m_cself);
            numInputs = biquadStereo::num_inputs();
            numOutputs = biquadStereo::num_outputs();
        }
        
        //PARAM ENUM
        for (int i = 0; i < getNumParameters(); ++i)
        {
            ParamEnum[getParamName(i)] = i;
        }
    }

    
    void perform(juce::AudioBuffer<float>& in_buffer, juce::AudioBuffer<float>& dataOut_)
    {
        //converte AudioBuffer in puntatori multidimensionali da usare in biquadStereo::perform
        auto** buffData = (float**)in_buffer.getArrayOfWritePointers();
        auto** dataOutData = (float**)dataOut_.getArrayOfWritePointers();

        biquadStereo::perform(m_cself, buffData, numInputs, dataOutData, numOutputs, in_buffer.getNumSamples());
    }
    
    void setParameter(long in_paramIndex, float in_paramValue)
    {
        biquadStereo::setparameter(m_cself, in_paramIndex, (t_sample)in_paramValue, NULL);
    }
    
    void setParameter(juce::String paramID, float in_paramValue)
    {
        biquadStereo::setparameter(m_cself, ParamEnum[paramID], (t_sample)in_paramValue, NULL);
    }
    
    int getNumParameters ()
    {
        return biquadStereo::num_params();
    }
    
    juce::String getParamName(int i)
    {
        return biquadStereo::getparametername(m_cself, i);
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
    
    //Mappatura parametri
    std::map<juce::String, int> ParamEnum;
};
