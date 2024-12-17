/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Esercizio2AudioProcessorEditor::Esercizio2AudioProcessorEditor (Esercizio2AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    //caratterizzazione pulsante Bypass
    addAndMakeVisible(bypassButton);
    
    //Attachment Volume
    bypassAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.parameters, "bypass", bypassButton);
    
    //Intervallo timer 30 ms
    startTimer(30);
    
    //Imposta la finestra principale a 450 px di larghezza e  250 px di altezza
    setSize (450, 250);
}

Esercizio2AudioProcessorEditor::~Esercizio2AudioProcessorEditor()
{
    //ferma il timer a chiusura del plugin
    stopTimer();
}

void Esercizio2AudioProcessorEditor::timerCallback()
{
    //Ridisegna la finestra con l'intervallo del timer
    repaint();
}

//==============================================================================
void Esercizio2AudioProcessorEditor::paint (juce::Graphics& g)
{
    //Colora la finestra di nero
    g.fillAll(juce::Colours::black);
    
    //Scrivi intestazione Plugin
    g.setColour(juce::Colours::white);
    g.setFont(20);
    g.drawText("Esercizio 2", 0, 10, getWidth(), 40, juce::Justification::centred);
    
    g.setFont(15);
    g.drawFittedText("Bypass Inv Fase", bypassButton.getX() -100, bypassButton.getY(), 100, 20, juce::Justification::centred, 1);
}

void Esercizio2AudioProcessorEditor::resized()
{
    bypassButton.setBounds(225, 100, 25, 20);
}
