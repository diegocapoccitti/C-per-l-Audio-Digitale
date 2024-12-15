/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Esempio7aAudioProcessorEditor::Esempio7aAudioProcessorEditor (Esempio7aAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    slider.setSliderStyle(juce::Slider::LinearHorizontal);
    slider.setRange(0.0, 1.0); // Range del valore da 0 a 1
    slider.setSkewFactor (0.5); //altera la distribuzione dei valori
    slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxLeft, true, 100, 50);
    addAndMakeVisible(slider);
    
    setSize (400, 300);
}

Esempio7aAudioProcessorEditor::~Esempio7aAudioProcessorEditor()
{
}

//==============================================================================
void Esempio7aAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void Esempio7aAudioProcessorEditor::resized()
{
    slider.setBounds(10, 10, 200, 100);
}
