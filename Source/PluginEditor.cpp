/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DroneboyAudioProcessorEditor::DroneboyAudioProcessorEditor (DroneboyAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    for (int i = 0; i < sizeof(dial)/sizeof(dial[0]); i++)
    {
        dial[i].setSliderStyle(Slider::SliderStyle::RotaryHorizontalVerticalDrag);
        // customizing our dials and gains within their respective arrays
        if (i < 3)
        {
            gain[i].setSliderStyle(Slider::SliderStyle::LinearHorizontal);
            gain[i].setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
            gain[i].setRange(-45.0, 0, 0.01);
            gain[i].setValue(-45.0);
            gain[i].setLookAndFeel(new GainLookAndFeel);
            gain[i].addListener(this);
            addAndMakeVisible(gain[i]);
            
            dial[i].setRange(20, 100, 1);
            dial[i].setValue(60);
            dial[i].setLookAndFeel(new LowFreqLookAndFeel);
        }
        else if ((3 <= i) && (i < 6))
        {
            dial[i].setRange(100, 200, 1);
            dial[i].setValue(150);
            dial[i].setLookAndFeel(new MidFreqLookAndFeel);
        }
        else if ((6 <= i) && (i < 9))
        {
            dial[i].setRange(200, 400, 1);
            dial[i].setValue(300);
            dial[i].setLookAndFeel(new HighFreqLookAndFeel);
        }
        dial[i].setTextBoxStyle(juce::Slider::NoTextBox, true, 0, 0);
        dial[i].addListener(this);
        addAndMakeVisible(dial[i]);
    }
    setSize (400, 600);
}

DroneboyAudioProcessorEditor::~DroneboyAudioProcessorEditor()
{
}

//==============================================================================
void DroneboyAudioProcessorEditor::paint (juce::Graphics& g)
{
    // drawing custom image to background
    Image background = ImageFileFormat::loadFrom(BinaryData::drone9_background_jpg, BinaryData::drone9_background_jpgSize);
    g.drawImageAt(background, 0, 0);
}

void DroneboyAudioProcessorEditor::sliderValueChanged(Slider *slider)
{
    for (int i = 0; i < 9; i++)
    {
        // array dial is where we're holding our frequency rotary objects
        if (slider == &dial[i])
        {
            audioProcessor.dialFreq[i] = dial[i].getValue();
            // use below for debug
            //std::cout << audioProcessor.dialFreq[i] << "\n";
        }
        // array gain is where we're holding our gain sliders
        else if (slider == &gain[i])
        {
            audioProcessor.sliderGain[i] = gain[i].getValue();
        }
    }
}



void DroneboyAudioProcessorEditor::resized()
{
    for (int i = 0; i < 3; ++i)
    {
        for(int j = 0; j < 3; ++j)
        {
            dial[i * 3 + j].setBounds(getWidth()*j/3, getHeight()*i/3, getWidth()*1/3, getHeight()*2/9);
        }
    }
    gain[0].setBounds(0, getHeight()*2/9, getWidth(), getHeight()*1/9);
    gain[1].setBounds(0, getHeight()*5/9, getWidth(), getHeight()*1/9);
    gain[2].setBounds(0, getHeight()*8/9, getWidth(), getHeight()*1/9);
}

