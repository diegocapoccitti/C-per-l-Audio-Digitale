/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Esempio76AudioProcessorEditor::Esempio76AudioProcessorEditor (Esempio76AudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    //caratterizzazione knob Gain
    gainKnob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    gainKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 100, 20);
    gainKnob.setRange(-60.f, 12.f, 0.f);
    addAndMakeVisible(gainKnob);
    
    //Attachment Gain
    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "gain", gainKnob);
    
    //caratterizzazione label Gain
    gainLabel.setText("Gain", juce::NotificationType::dontSendNotification);
    gainLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(gainLabel);
    
    //caratterizzazione label Meter
    meterLabel.setText("Meter", juce::NotificationType::dontSendNotification);
    meterLabel.setJustificationType(juce::Justification::centred);
    addAndMakeVisible(meterLabel);
    
    //esegure timerCallback ogni 30ms
    startTimer(30);
    
    //Imposta la finestra principale a 450 px di larghezza e  250 px di altezza
    setSize (450, 250);
}

void Esempio76AudioProcessorEditor::timerCallback()
{
    // Chiama repaint per aggiornare il disegno del meter in base al livello di uscita
    repaint();
}

Esempio76AudioProcessorEditor::~Esempio76AudioProcessorEditor()
{
    //Ferma il timer
    stopTimer();
}

//==============================================================================
void Esempio76AudioProcessorEditor::paint (juce::Graphics& g)
{
    //Colora la finestra di nero
    g.fillAll(juce::Colours::black);
    
    //altezza meter
    float hMeter = 100.f;
    
    // Disegna il background del meter
    g.setColour(juce::Colours::darkgrey);
    g.fillRect(300, 100, 50, (int)hMeter);
    
    // Calcola l'altezza del rettangolo verde
    float dB = audioProcessor.getOutputdB();
    if (dB < -60.f) dB = -60.f;
    float meterHeight = juce::jmap(dB, -60.0f, 12.0f, 0.0f, hMeter);
    
    // Disegna il rettangolo verde che riflette il livello di uscita
    g.setColour(juce::Colours::green);
    g.fillRect(300.f, (float)(100.f + hMeter - meterHeight), 50.f, meterHeight);
    
    //Scrivi intestazione Plugin
    g.setColour(juce::Colours::white);
    g.setFont(20);
    g.drawText("GAINMETER PLUGIN", 0, 10, getWidth(), 40, juce::Justification::centred);
}

void Esempio76AudioProcessorEditor::resized()
{
    //Posiziona gli oggetti
    gainKnob.setBounds(100, 100, 100, 100);
    gainLabel.setBounds(gainKnob.getX(), gainKnob.getY()-40, gainKnob.getWidth(), 20);
    meterLabel.setBounds(300, gainKnob.getY()-40, 50, 20);
}
