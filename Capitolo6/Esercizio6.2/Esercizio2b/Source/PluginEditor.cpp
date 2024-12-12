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
    //Imposta la finestra principale a 450 px di larghezza e  250 px di altezza
    setSize (450, 250);
}

Esercizio2AudioProcessorEditor::~Esercizio2AudioProcessorEditor()
{
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
}

void Esercizio2AudioProcessorEditor::resized()
{
}
