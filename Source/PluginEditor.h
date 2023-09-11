/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class LowFreqLookAndFeel : public juce::LookAndFeel_V4
{
public:
    LowFreqLookAndFeel()
    {
        setColour(Slider::rotarySliderOutlineColourId, Colours::tan);
        setColour(Slider::rotarySliderFillColourId, Colours::wheat);
        setColour(Slider::thumbColourId, Colours::beige);
    }
};

class MidFreqLookAndFeel : public juce::LookAndFeel_V4
{
public:
    MidFreqLookAndFeel()
    {
        setColour(Slider::rotarySliderOutlineColourId, Colours::tan);
        setColour(Slider::rotarySliderFillColourId, Colours::wheat);
        setColour(Slider::thumbColourId, Colours::beige);
    }
};

class HighFreqLookAndFeel : public juce::LookAndFeel_V4
{
public:
    HighFreqLookAndFeel()
    {
        setColour(Slider::rotarySliderOutlineColourId, Colours::tan);
        setColour(Slider::rotarySliderFillColourId, Colours::wheat);
        setColour(Slider::thumbColourId, Colours::beige);
    }
};


class GainLookAndFeel : public juce::LookAndFeel_V4
{
public:
    GainLookAndFeel()
    {
        setColour(Slider::thumbColourId, Colours::wheat);
        setColour(Slider::trackColourId, Colours::tan);
    }
};


class DroneboyAudioProcessorEditor  : public juce::AudioProcessorEditor,
                                                    public Slider::Listener
{
public:
    DroneboyAudioProcessorEditor (DroneboyAudioProcessor&);
    ~DroneboyAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;
    void sliderValueChanged(Slider* slider) override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DroneboyAudioProcessor& audioProcessor;
    Slider dial[9], gain[3];
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DroneboyAudioProcessorEditor)
};
