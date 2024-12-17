/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Esercizio3AudioProcessorEditor::Esercizio3AudioProcessorEditor (Esercizio3AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    //caratterizzazione knob Freq
     freqKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
     freqKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 100, 20);
     addAndMakeVisible(freqKnob);
     
     //Attachment Freq
     freqAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "cutoffF", freqKnob);
    
    //caratterizzazione pulsante Bypass
     addAndMakeVisible(bypassButton);
     
     //Attachment Volume
     bypassAttachment = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.parameters, "bypass", bypassButton);
    
    //Intervallo timer 30 ms
    startTimer(30);
    
    //Imposta la finestra principale a 450 px di larghezza e  250 px di altezza
    setSize (450, 250);
}

Esercizio3AudioProcessorEditor::~Esercizio3AudioProcessorEditor()
{
    //ferma il timer a chiusura del plugin
    stopTimer();
}

void Esercizio3AudioProcessorEditor::timerCallback()
{
    //Ridisegna la finestra con l'intervallo del timer
    repaint();
}

//==============================================================================
void Esercizio3AudioProcessorEditor::paint (juce::Graphics& g)
{
    //Colora la finestra di nero
    g.fillAll(juce::Colours::black);
    
    //Scrivi intestazione Plugin
    g.setColour(juce::Colours::white);
    g.setFont(20);
    g.drawText("Esercizio 3", 0, 10, getWidth(), 40, juce::Justification::centred);
    
    //Cambia la grandezza del font
    g.setFont(15);
    //testo pulsante bypass
    g.drawFittedText("Bypass", bypassButton.getX() -80, bypassButton.getY(), 100, 20, juce::Justification::centred, 1);
    //testo pulsante freq
    g.drawFittedText("Cutoff [hz]", freqKnob.getX(), freqKnob.getY()-20, freqKnob.getWidth(), 20, juce::Justification::centred, 1);
}

void Esercizio3AudioProcessorEditor::resized()
{
    freqKnob.setBounds(275, 100, 100, 100);
    bypassButton.setBounds(100, 100, 25, 20);
}
