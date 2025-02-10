// #include "PluginProcessor.h"
#include "../include/UseTime/PluginEditor.h"

//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);
    startTimerHz(1);
    // hourLabel = Label("hourLabel", "0");
    // minuteLabel = Label("minuteLabel", "0");
    // secondLabel = Label("secondLabel", "0");

    addAndMakeVisible(hourLabel);
    addAndMakeVisible(minuteLabel);
    addAndMakeVisible(secondLabel);

    hourString = "0";
    minuteString = "0";
    secondString = "0";

    hourLabel.setText(hourString, juce::dontSendNotification);
    minuteLabel.setText(minuteString, juce::dontSendNotification);
    secondLabel.setText(secondString, juce::dontSendNotification);

    font = juce::Font("Courier", 20.0f, juce::Font::bold);

    // label font setting
    hourLabel.setFont(font);
    minuteLabel.setFont(font);
    secondLabel.setFont(font);

    // label color setsting
    hourLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    minuteLabel.setColour(juce::Label::textColourId, juce::Colours::black);
    secondLabel.setColour(juce::Label::textColourId, juce::Colours::black);

    hourLabel.setEditable(false);
    minuteLabel.setEditable(false);
    secondLabel.setEditable(false);

    // font.setTypefaceName("Courier");

    // font.setTypefaceName("Courier");
    // repaint();
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
}

AudioPluginAudioProcessorEditor::~AudioPluginAudioProcessorEditor()
{
    stopTimer();
}

//==============================================================================
void AudioPluginAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    // g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
    g.fillAll(juce::Colours::lightgreen);

    g.setColour (juce::Colours::black);
    

    // font.setBold(true);

    g.setFont(font);
    // g.setFont(20.0f);
    // g.setTypefaceName("Courier");
    // g.drawFittedText ("Hello World!", getLocalBounds(), juce::Justification::centred, 1);
    // g.drawFittedText(":", getWidth()/2 + 10, getHeight()/2 - 10, getWidth() - 20, 30, juce::Justification::centred, 1);
    // g.drawFittedText(":", getWidth()/2 + 10, getHeight()/2, getWidth() - 20, 30, juce::Justification::centred, 1);


// (const String &text, int x, int y, int width, int height, Justification justificationFlags, int maximumNumberOfLines, float minimumHorizontalScale=0.0f
    std::string pHour = std::to_string(*(processorRef.hour));
    std::string pMinute = std::to_string(*(processorRef.minute));
    std::string pSecond = std::to_string(*(processorRef.second));

    if (hourString != pHour) {
        hourString = pHour;
        hourLabel.setText(hourString, juce::sendNotification);
    }
    if (minuteString != pMinute) {
        minuteString = pMinute;
        minuteLabel.setText(minuteString, juce::sendNotification);
    }
    if (secondString != pSecond) {
        secondString = pSecond;
        secondLabel.setText(secondString, juce::sendNotification);
        // ideally only need to repaint here because a change in the second is guaranteed when a change in the hour/minute occurs
    }
    // repaint();
}

void AudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    hourLabel.setBounds(getWidth()/2, getHeight()/2 - 15, getWidth() - 20, 30);
    minuteLabel.setBounds(getWidth()/2, getHeight()/2, getWidth() - 20, 30);
    secondLabel.setBounds(getWidth()/2, getHeight()/2 + 15, getWidth() - 20, 30);
}
