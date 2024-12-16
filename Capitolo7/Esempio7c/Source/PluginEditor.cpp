/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
Esempio7cAudioProcessorEditor::Esempio7cAudioProcessorEditor (Esempio7cAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    //Slider
    slider.setSliderStyle(juce::Slider::LinearHorizontal);
    slider.setRange(0.0, 1.0); // Range del valore da 0 a 1
    slider.setSkewFactor (0.5); //altera la distribuzione dei valori
    slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxLeft, true, 100, 50);
    addAndMakeVisible(slider);
    
    //Toggle
    addAndMakeVisible(button);
    
    //Combobox
    // Aggiunta degli elementi alla ComboBox
    myComboBox.addItem("Preset 1", 1);
    myComboBox.addItem("Preset 2", 2);
    myComboBox.addItem("Preset 3", 3);

    // Configurazione della ComboBox
    myComboBox.setSelectedId(1); // Seleziona il primo elemento di default
    addAndMakeVisible(myComboBox); // Aggiunge la ComboBox alla finestra
    
    setSize (400, 300);
}

Esempio7cAudioProcessorEditor::~Esempio7cAudioProcessorEditor()
{
}

//==============================================================================
void Esempio7cAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
}

void Esempio7cAudioProcessorEditor::resized()
{
    slider.setBounds(10, 10, 200, 100);
    button.setBounds(250, 20, 100, 50);
    myComboBox.setBounds(20, 170, 150, 30); // Posizionamento della ComboBox
}
