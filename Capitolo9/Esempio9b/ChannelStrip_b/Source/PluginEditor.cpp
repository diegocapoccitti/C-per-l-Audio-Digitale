/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
ChannelStripAudioProcessorEditor::ChannelStripAudioProcessorEditor (ChannelStripAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    //Equalizzatore
    createSlider(freqHpKnob, freqHpAtt, "freq_hp", " Hz");
    createSlider(freqBellKnob, freqBellAtt, "freq_bell", " Hz");
    createSlider(qBellKnob, qBellAtt, "q_bell", "");
    createSlider(gainBellKnob, gainBellAtt, "gain_bell", " Linear");
    createSlider(freqLpKnob, freqLpAtt, "freq_lp", " Hz");
    
    //Compressore
    createSlider(paralMixKnob, paralMixAtt, "parallel_mix", "");
    createSlider(inputGainKnob, inputGainAtt, "input_gain", " Linear");
    createSlider(threshKnob, threshAtt, "threshold", " dB");
    createSlider(ratioKnob, ratioAtt, "ratio", ":1");
    createSlider(attackKnob, attackAtt, "attack", " ms");
    createSlider(releaseKnob, releaseAtt, "release", " ms");
    
    //Output Gain
    outputGainKnob.setSliderStyle(juce::Slider::SliderStyle::LinearHorizontal);
    outputGainKnob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 100, 20);
    outputGainKnob.setTextBoxIsEditable(true);
    outputGainKnob.setTextValueSuffix (" dB");
    addAndMakeVisible(outputGainKnob);
    outputGainAtt = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, "output_gain", outputGainKnob);
    
    //Bypass
     addAndMakeVisible(bypassButton);
     bypassAtt = std::make_unique<juce::AudioProcessorValueTreeState::ButtonAttachment>(audioProcessor.parameters, "bypass", bypassButton);
    
    //Meters
    addAndMakeVisible(meterIn);
    addAndMakeVisible(meterOut);
    
    //Intervallo timer 30 ms
    startTimer(30);
    
    //Imposta la finestra principale a 600 px di larghezza e  650 px di altezza
    setSize (600, 650);
}

ChannelStripAudioProcessorEditor::~ChannelStripAudioProcessorEditor()
{
    stopTimer();
}

void ChannelStripAudioProcessorEditor::createSlider(juce::Slider& knob, std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment>& att, juce::String id, juce::String unit)
{
    //caratterizzazione
    knob.setSliderStyle(juce::Slider::SliderStyle::RotaryVerticalDrag);
    knob.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::TextBoxBelow, true, 100, 20);
    knob.setTextBoxIsEditable(true);
    knob.setTextValueSuffix (unit);
    //Aggiungi alla finestra principale
    addAndMakeVisible(knob);
     //Collega l'Attachment
    att = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.parameters, id, knob);
}

void ChannelStripAudioProcessorEditor::timerCallback()
{
    // Ottieni e resetta il valore del picco in e aggiorna meter In
    float currentPeakIn = audioProcessor.getAndResetPeakLevelIn();
    meterIn.setLevel(currentPeakIn);
    
    // Ottieni e resetta il valore del picco out e aggiorna meter Out
    float currentPeakOut = audioProcessor.getAndResetPeakLevelOut();
    meterOut.setLevel(currentPeakOut);
    
    //Ridisegna la finestra con l'intervallo del timer
    repaint();
}

//==============================================================================
void ChannelStripAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

     
    //Linee separatrici
    g.setColour (juce::Colours::yellow);
    g.drawLine(freqHpKnob.getX(), 40, freqLpKnob.getRight(), 40);
    g.drawLine(freqHpKnob.getX(), gainBellKnob.getBottom() + 20, freqLpKnob.getRight(), gainBellKnob.getBottom() + 20);
    g.drawLine(freqHpKnob.getX(), paralMixKnob.getBottom() + 20, freqLpKnob.getRight(), paralMixKnob.getBottom() + 20);
    
    //Titolo EQ
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("EQUALIZZATORE", 0, 50, getWidth(), 15, juce::Justification::centred, 1);
    //Titolo Comp
    g.drawFittedText ("COMPRESSORE", 0, gainBellKnob.getBottom() + 35, getWidth(), 15, juce::Justification::centred, 1);
    //Titolo Output Gain
    g.drawFittedText ("OUTPUT GAIN", outputGainKnob.getX(), paralMixKnob.getBottom() + 40, outputGainKnob.getWidth(), 15, juce::Justification::centred, 1);
    //Titolo bypass
    g.drawFittedText ("BYPASS", bypassButton.getX()- 30, paralMixKnob.getBottom() + 40, bypassButton.getWidth(), 15, juce::Justification::centred, 1);
  
    //Titolo meters
    g.drawFittedText ("IN", meterIn.getX(), meterIn.getBottom() + 10, meterIn.getWidth(), 15, juce::Justification::centred, 1);
    g.drawFittedText ("OUT", meterOut.getX(), meterOut.getBottom() + 10, meterOut.getWidth(), 15, juce::Justification::centred, 1);
    
    g.setColour (juce::Colours::white);
    
    //TITOLO
    g.setFont (juce::FontOptions (25.0f));
    g.drawFittedText ("CHANNEL STRIP", 0, 5, getWidth(), 30, juce::Justification::centred, 1);
    
    //Equalizzatore
    g.setFont (juce::FontOptions (12.0f));
    g.drawFittedText ("HP freq", freqHpKnob.getX(), freqHpKnob.getY() - 10, freqHpKnob.getWidth(), 10, juce::Justification::centred, 1);
    g.drawFittedText ("LP freq", freqLpKnob.getX(), freqLpKnob.getY() - 10, freqLpKnob.getWidth(), 10, juce::Justification::centred, 1);
    g.drawFittedText ("freq", freqBellKnob.getX(), freqBellKnob.getY() - 10, freqBellKnob.getWidth(), 10, juce::Justification::centred, 1);
    g.drawFittedText ("gain", gainBellKnob.getX(), gainBellKnob.getY() - 10, gainBellKnob.getWidth(), 10, juce::Justification::centred, 1);
    g.drawFittedText ("Q", qBellKnob.getX() + 30, qBellKnob.getY() + 20, qBellKnob.getWidth(), 10, juce::Justification::centred, 1);
    g.drawFittedText ("BELL", 0, gainBellKnob.getY() + 20, getWidth(), 15, juce::Justification::centred, 1);
    
    //Compressore
    g.drawFittedText ("input gain", inputGainKnob.getX(), inputGainKnob.getY() - 10, inputGainKnob.getWidth(), 10, juce::Justification::centred, 1);
    g.drawFittedText ("threshold", threshKnob.getX(), threshKnob.getY() - 10, threshKnob.getWidth(), 10, juce::Justification::centred, 1);
    g.drawFittedText ("ratio", ratioKnob.getX(), ratioKnob.getY() - 10, ratioKnob.getWidth(), 10, juce::Justification::centred, 1);
    g.drawFittedText ("attack", attackKnob.getX(), attackKnob.getY() - 10, attackKnob.getWidth(), 10, juce::Justification::centred, 1);
    g.drawFittedText ("release", releaseKnob.getX(), releaseKnob.getY() - 10, releaseKnob.getWidth(), 10, juce::Justification::centred, 1);
    g.drawFittedText ("parallel mix", paralMixKnob.getX(), paralMixKnob.getY() - 10, paralMixKnob.getWidth(), 10, juce::Justification::centred, 1);
    
    //Copyright
    g.drawFittedText ("2024 Diego Capoccitti. Tutti i diritti riservati.", 0, getHeight() - 25, getWidth(), 10, juce::Justification::centred, 1);
}

void ChannelStripAudioProcessorEditor::resized()
{
    int dimKnobBig = 100;
    int dimKnobSmall = 80;
    int hEq = 100;
    
    //Equalizzatore
    freqHpKnob.setBounds(dimKnobBig, hEq, dimKnobBig, dimKnobBig);
    freqLpKnob.setBounds(getRight() - 2*dimKnobBig, hEq, dimKnobBig, dimKnobBig);
    freqBellKnob.setBounds(freqHpKnob.getRight(), 1.5*hEq, dimKnobSmall, dimKnobSmall);
    gainBellKnob.setBounds(freqLpKnob.getX() - dimKnobSmall, 1.5*hEq, dimKnobSmall, dimKnobSmall);
    qBellKnob.setBounds(getWidth()/2 - dimKnobSmall/2, gainBellKnob.getY() - dimKnobSmall, dimKnobSmall, dimKnobSmall);

    //Compressore
    inputGainKnob.setBounds(freqHpKnob.getX() + dimKnobBig/2, gainBellKnob.getBottom() + 70, dimKnobSmall, dimKnobSmall);
    threshKnob.setBounds(inputGainKnob.getX() + 110, inputGainKnob.getY(), dimKnobSmall, dimKnobSmall);
    ratioKnob.setBounds(threshKnob.getX() + 110, inputGainKnob.getY(), dimKnobSmall, dimKnobSmall);
    attackKnob.setBounds(inputGainKnob.getX(), inputGainKnob.getBottom() + 20, dimKnobSmall, dimKnobSmall);
    releaseKnob.setBounds(threshKnob.getX(), inputGainKnob.getBottom() + 20, dimKnobSmall, dimKnobSmall);
    paralMixKnob.setBounds(ratioKnob.getX(), inputGainKnob.getBottom() + 20, dimKnobSmall, dimKnobSmall);

    //Output Gain
    outputGainKnob.setBounds(freqHpKnob.getX(), paralMixKnob.getBottom() + 70, paralMixKnob.getX() - freqHpKnob.getX(), dimKnobSmall/2);
    
    //Bypass
    bypassButton.setBounds(paralMixKnob.getX() + 50, outputGainKnob.getY() - 10, dimKnobSmall, dimKnobSmall/2);
    
    //Meters
    meterIn.setBounds(20, 40, 50, getHeight() - 90);
    meterOut.setBounds(getWidth() - 70, 40, 50, getHeight() - 90);
     
}
