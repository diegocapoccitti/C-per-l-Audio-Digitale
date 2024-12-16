/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

class MovingCircle : public juce::Component, private juce::Timer
{
public:
    MovingCircle() : xPosition(0)  // Posizione iniziale
    {
        startTimer(30); // Intervallo di 30 ms
    }

    ~MovingCircle() override
    {
        stopTimer(); //Frema il timer all’uscita
    }

    void timerCallback() override
    {
        xPosition += 5; // Sposta il cerchio di 5 pixel verso destra
        if (xPosition > getWidth()) // Se esce dallo schermo, lo resetta
            xPosition = 0;

        repaint(); // Aggiorna il disegno per mostrare la nuova posizione
    }

    void paint(juce::Graphics& g) override
    {
        g.fillAll(juce::Colours::black);
        g.setColour(juce::Colours::red);
        g.fillEllipse(xPosition, getHeight() / 2 - 25, 50, 50); // Disegna il cerchio
    }

private:
    int xPosition; // Coordinata x del cerchio
};

//==============================================================================
/**
*/
class Esempio7fAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    Esempio7fAudioProcessorEditor (Esempio7fAudioProcessor&);
    ~Esempio7fAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    MovingCircle circle;
    
    Esempio7fAudioProcessor& audioProcessor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Esempio7fAudioProcessorEditor)
};
