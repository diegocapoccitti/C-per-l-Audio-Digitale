/*
  ==============================================================================

    Look.h
    Created: 19 Nov 2024 1:36:50am
    Author:  Diego Capoccitti

  ==============================================================================
*/

#pragma once

struct Look : juce::LookAndFeel_V4
{
    Look(){}

    void drawRotarySlider (juce::Graphics& g, int x, int y, int width, int height,
                           float sliderPosProportional, float rotaryStartAngle,
                           float rotaryEndAngle, juce::Slider& slider) override
    {
        {
            //MISURE
            //Calcola la dimensione da utilizzare per l'area del knob
            auto size = juce::jmin(width * 0.6, height * 0.6);
            //Calcola il rettangolo dell'area del knob
            auto r = slider.getLocalBounds().withSizeKeepingCentre(size, size).reduced(2).toFloat();
            
            //DISEGNA IL FONDO
            //Imposta il colore grigio
            g.setColour(juce::Colours::grey.withAlpha(0.5f));
            //Disegna il cerchio grigio
            g.fillEllipse(r);
            //Imposta il colore giallo
            g.setColour(juce::Colours::yellow);
            
            //DISEGNA LA TACCA
            //Calcola il rettangolo della tacca di larghezza 2 (posizionato a ore 12)
            auto tickMarkBounds = r.withSizeKeepingCentre(2, size/2).withY(r.getY());
            //Calcola l'angolo di rotazione
            auto sliderAng = juce::jmap(sliderPosProportional, 0.f, 1.f, rotaryStartAngle, rotaryEndAngle);
            //Calcola il centro dell'area
            juce::Point<float> center = r.getCentre();
            //Calcola la rotazione
            auto rot = juce::AffineTransform().rotation(sliderAng, center.getX(), center.getY());
            //Applica la rotazione
            g.addTransform(rot);
            //Disegna la tacca
            g.fillRect(tickMarkBounds);

            //BORDO ESTERNO
            //Imposta il colore giallo piu scuro
            g.setColour(juce::Colours::yellow.withLightness(0.2f));
            //Disegna il cerchio esterno
            g.drawEllipse(r, 2);
        }
    }
    

    void drawToggleButton (juce::Graphics& g, juce::ToggleButton& button, bool shouldDrawButtonAsHighlighted, bool shouldDrawButtonAsDown) override
    {
        //MISURE
        auto size = juce::jmin(button.getWidth() * 0.6, button.getHeight() * 0.6);
        auto r = button.getLocalBounds().withSizeKeepingCentre(size, size).reduced(2).toFloat();

        //Sceglie colore in base alla condizione del pulsante
        if (button.getToggleState())
        {
            g.setColour(juce::Colours::yellow); //Colore giallo: acceso
        }
        else
        {
            g.setColour(juce::Colours::grey.withAlpha(0.5f)); //Colore grigio: spento
        }
        
        //Disegna il cerchio colorato
        g.fillEllipse(r);
        
        //BORDO ESTERNO
        g.setColour(juce::Colours::yellow.withLightness(0.2f));
        g.drawEllipse(r, 2);
    }
};
    
