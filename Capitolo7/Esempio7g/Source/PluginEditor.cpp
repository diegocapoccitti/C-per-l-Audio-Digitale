/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
TESTAudioProcessorEditor::TESTAudioProcessorEditor (TESTAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (400, 300);

    // --- Configurazione del Knob ---
    // Stile rotary con trascinamento verticale e casella di testo sotto
    gainKnob.setSliderStyle (juce::Slider::SliderStyle::RotaryVerticalDrag);
    gainKnob.setTextBoxStyle (juce::Slider::TextEntryBoxPosition::TextBoxBelow,
                              true, 100, 20);
    addAndMakeVisible (gainKnob);

    // L'attachment collega il knob al parametro "gain" dell'APVTS:
    // ogni volta che l'utente muove il knob, il valore del parametro viene aggiornato
    // automaticamente senza dover scrivere nessun listener nell'editor.
    gainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(
        audioProcessor.parameters, "gain", gainKnob);

    gainLabel.setText ("Gain", juce::NotificationType::dontSendNotification);
    gainLabel.setJustificationType (juce::Justification::centred);
    gainLabel.setColour (juce::Label::textColourId, juce::Colours::white);
    addAndMakeVisible (gainLabel);

    // Avvia il timer a 30 ms (~30 fps): verrà chiamato timerCallback() a ogni tick
    startTimer (30);
}

TESTAudioProcessorEditor::~TESTAudioProcessorEditor()
{
    stopTimer();
}

//==============================================================================
void TESTAudioProcessorEditor::timerCallback()
{
    // Forza il ridisegno dell'editor: così il meter viene aggiornato ~30 volte al secondo
    repaint();
}

//==============================================================================
void TESTAudioProcessorEditor::paint (juce::Graphics& g)
{
    // Sfondo nero
    g.fillAll (juce::Colours::black);

    // --- Titolo ---
    g.setColour (juce::Colours::white);
    g.setFont (juce::FontOptions (20.0f).withStyle ("Bold"));
    g.drawFittedText ("GAINMETER PLUGIN", 0, 0, getWidth(), 40,
                      juce::Justification::centred, 1);

    // --- Label "Meter" ---
    g.setFont (juce::FontOptions (15.0f));
    g.drawFittedText ("Meter",
                      getWidth() / 2, 80, getWidth() / 2, 20,
                      juce::Justification::centred, 1);

    // --- Disegno del Meter ---
    // Posizione e dimensioni del rettangolo del meter
    const int meterX = 3 * getWidth() / 4 - 40;
    const int meterY = 100;
    const int meterW = 80;
    const int hmeter = getHeight() - 120;   // altezza totale disponibile

    // 1) Sfondo grigio scuro (livello "vuoto")
    g.setColour (juce::Colours::darkgrey);
    g.fillRect (meterX, meterY, meterW, hmeter);

    // 2) Parte verde che sale dal basso in proporzione al livello in dB
    //    getOutputdB() restituisce il picco calcolato nel processBlock
    const float dB = audioProcessor.getOutputdB();

    //    jmap mappa il range dB [-60, +12] nell'intervallo di pixel [0, hmeter]
    float meterHeight = juce::jmap (dB, -60.0f, 12.0f, 0.0f, (float) hmeter);
    meterHeight = juce::jlimit (0.0f, (float) hmeter, meterHeight);

    //    Il rettangolo verde parte dal basso: la sua y di partenza è
    //    meterY + hmeter - meterHeight  (coordinate Y scendono verso il basso)
    g.setColour (juce::Colours::green);
    g.fillRect (meterX,
                meterY + hmeter - (int) meterHeight,
                meterW,
                (int) meterHeight);
}

//==============================================================================
void TESTAudioProcessorEditor::resized()
{
    // Label "Gain" sopra il knob
    gainLabel.setBounds (30, 80, 160, 20);

    // Knob centrato nella metà sinistra della finestra
    gainKnob.setBounds (30, 100, 160, 160);
}
