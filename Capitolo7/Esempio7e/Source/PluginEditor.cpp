/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Esempio7eAudioProcessorEditor::Esempio7eAudioProcessorEditor (Esempio7eAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    gainSlider.setRange(-60.0, 12.0);
    gainSlider.setValue(0.0);
    gainSlider.setSliderStyle(juce::Slider::LinearHorizontal);
    gainSlider.setTextBoxStyle(juce::Slider::TextBoxRight, false, 50, 20);
    addAndMakeVisible(&gainSlider);

    bypassButton.setButtonText("Bypass");
    addAndMakeVisible(&bypassButton);

    setSize (400, 300);
}

Esempio7eAudioProcessorEditor::~Esempio7eAudioProcessorEditor()
{
}

//==============================================================================
void Esempio7eAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void Esempio7eAudioProcessorEditor::resized()
{
    gainSlider.setBounds (20, 20, 300, 40);
    bypassButton.setBounds (20, 80, 100, 30);
}
