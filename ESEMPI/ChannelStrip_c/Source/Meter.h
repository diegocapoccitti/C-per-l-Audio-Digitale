/*
  ==============================================================================

    Meter.h
    Created: 18 Nov 2024 9:32:15pm
    Author:  Diego Capoccitti

  ==============================================================================
*/

#pragma once

class Meter : public juce::Component
{
    public:
    Meter () {}
    ~Meter() override {}

    //==============================================================================
    void paint (juce::Graphics& g) override
    {
        //Sfondo grigio
        g.fillAll (juce::Colours::grey.withLightness(0.1));

        int hTot = (int)((float)getHeight() * (1.f - hLevel));
        
        //Livello verde
        if (hLevel > 0.f && hLevel < 30.f/42.f)
        {
            g.setColour(juce::Colours::green.withAlpha(0.5f));
            g.fillRect(0, hTot, getWidth(), (int)(hLevel * getHeight()));
        }
        //Livello Giallo
        else if (hLevel >= 30.f/42.f && hLevel < 36.f/42.f)
        {
            g.setColour(juce::Colours::green.withAlpha(0.5f));
            g.fillRect(0, (int)(getHeight() * (1.f - 30.f/42.f)), getWidth(), (int)(30.f/42.f * getHeight()));
            g.setColour(juce::Colours::yellow.withAlpha(0.5f));
            g.fillRect(0, hTot, getWidth(), (int)(hLevel * getHeight()) - (int)(30.f/42.f * getHeight()));
        }
        //Livello Rosso
        else if (hLevel >= 36.f/42.f)
        {
            g.setColour(juce::Colours::green.withAlpha(0.5f));
            g.fillRect(0, (int)(getHeight() * (1.f - 30.f/42.f)), getWidth(), (int)(30.f/42.f * getHeight()));
            g.setColour(juce::Colours::yellow.withAlpha(0.5f));
            g.fillRect(0, (int)(getHeight() * (1.f - 36.f/42.f)), getWidth(), (int)(6.f/42.f * getHeight()));
            g.setColour(juce::Colours::red.withAlpha(0.5f));
            g.fillRect(0, hTot, getWidth(), (int)(hLevel * getHeight()) - (int)(36.f/42.f * getHeight()));
        }
        
        //Clip
        if (clip)
        {
            g.setColour(juce::Colours::red);
            g.fillRect(0, 0, getWidth(), (int)(1.f/42.f * getHeight()));
        }
            
        //Tacche
        g.setFont(10);
        
        for (int i = 0; i < 43; ++i)
        {
            int h = getHeight() * (1.f - i  / 42.f);
            
            if (i % 3 == 0)
            {
                g.setColour(juce::Colours::grey);
                juce::String text = i == 42 ? "0 dB" : "-" + juce::String(42-i) + " dB";
                g.drawFittedText(text, 0, h - 2, getWidth(), 15, juce::Justification::centred, 1);
                g.drawLine(0, h, getWidth(), h);
            }
            else
            {
                g.setColour(juce::Colours::grey.withAlpha(0.6f));
                g.drawLine(0, h, getWidth(), h);
            }
        }
        
        //Bordo
        g.drawRect(getLocalBounds());
    }
    void resized() override {}
    
    void mouseDown(const juce::MouseEvent& event) override
    {
        clip = false;
    }
    
    void setLevel (float level)
    {
        //Ricava i decibel dalla magnitudo
        float levelDB = juce::Decibels::gainToDecibels(level);
        //Rimappa i decibel tra 0 e 1
        hLevel = juce::jmap(levelDB, -42.f, 0.f, 0.f, 1.f);
        //Rileva Clip
        if (hLevel >= 1.f) clip = true;
    }
    
    private:
    
    float hLevel = 0.f;
    bool clip = false;
};
