/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Esempio7fAudioProcessorEditor::Esempio7fAudioProcessorEditor (Esempio7fAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    addAndMakeVisible(circle);
    setSize (400, 300);
}

Esempio7fAudioProcessorEditor::~Esempio7fAudioProcessorEditor()
{
}

//==============================================================================
void Esempio7fAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void Esempio7fAudioProcessorEditor::resized()
{
    circle.setBounds(0, 0, getWidth(), getHeight());
}
