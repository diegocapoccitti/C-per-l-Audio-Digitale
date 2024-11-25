/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Esercizio1AudioProcessorEditor::Esercizio1AudioProcessorEditor (Esercizio1AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    //caratterizzazione knob Volume
    volKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    volKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 100, 20);
    addAndMakeVisible(volKnob);
    
    //Attachment Volume
    volAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "vol", volKnob);
    
    //Intervallo timer 30 ms
    startTimer(30);
    
    //Imposta la finestra principale a 450 px di larghezza e  250 px di altezza
    setSize (450, 250);
}

Esercizio1AudioProcessorEditor::~Esercizio1AudioProcessorEditor()
{
    //ferma il timer a chiusura del plugin
    stopTimer();
}

void Esercizio1AudioProcessorEditor::timerCallback()
{
    //Ridisegna la finestra con l'intervallo del timer
    repaint();
}

//==============================================================================
void Esercizio1AudioProcessorEditor::paint (juce::Graphics& g)
{
    //Colora la finestra di nero
    g.fillAll(juce::Colours::black);
    
    //Scrivi intestazione Plugin
    g.setColour(juce::Colours::white);
    g.setFont(20);
    g.drawText("Esercizio 1", 0, 10, getWidth(), 40, juce::Justification::centred);
    
    g.setFont(15);
    g.drawFittedText("dB Noise", volKnob.getX(), volKnob.getY()-20, volKnob.getWidth(), 20, juce::Justification::centred, 1);
}

void Esercizio1AudioProcessorEditor::resized()
{
    volKnob.setBounds(175, 100, 100, 100);
}
