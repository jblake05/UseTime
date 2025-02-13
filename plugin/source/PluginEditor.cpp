#include "../include/UseTime/PluginEditor.h"
#include "../include/UseTime/time.h"

const int WIDTH_PADDING = 10;
const int HEIGHT_PADDING = 10;
const int DIST = 15;
struct time totalTime;
int randSplash;

using namespace std;
using namespace juce;
//==============================================================================
AudioPluginAudioProcessorEditor::AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor& p)
    : AudioProcessorEditor (&p), processorRef (p)
{
    juce::ignoreUnused (processorRef);
    startTimerHz(2);

    addAndMakeVisible(hourLabel);
    addAndMakeVisible(minuteLabel);
    addAndMakeVisible(secondLabel);
    addAndMakeVisible(splashLabel);
    addAndMakeVisible(logoLabel);

    totalTime = secondToTime(processorRef.totalSeconds);

    hourString = to_string(totalTime.hour);
    minuteString = to_string(totalTime.minute);
    secondString = to_string(totalTime.second);

    hourLabel.setText(hourString + " hours", juce::dontSendNotification);
    minuteLabel.setText(minuteString + " minutes", juce::dontSendNotification);
    secondLabel.setText(secondString + " seconds", juce::dontSendNotification);

    randSplash = rand() % SPLASH_ARRAY_SIZE;
    splashLabel.setText(splashText[randSplash], juce::dontSendNotification);
    logoLabel.setText(":>", juce::dontSendNotification);

    Font font = juce::Font("Courier", 22.0f, juce::Font::bold);
    Font logoFont = juce::Font("Courier", 40.0f, juce::Font::bold);

    // label font setting
    hourLabel.setFont(font);
    minuteLabel.setFont(font);
    secondLabel.setFont(font);
    splashLabel.setFont(font);
    logoLabel.setFont(logoFont);

    // label color setsting
    hourLabel.setColour(juce::Label::textColourId, juce::Colour(216, 132, 132));
    minuteLabel.setColour(juce::Label::textColourId, juce::Colour(216, 132, 132));
    secondLabel.setColour(juce::Label::textColourId, juce::Colour(216, 132, 132));
    splashLabel.setColour(juce::Label::textColourId, juce::Colour(216, 132, 132));
    logoLabel.setColour(juce::Label::textColourId, juce::Colour(216, 132, 132));

    // justifications when necessary
    splashLabel.setJustificationType(Justification::bottomRight);
    logoLabel.setJustificationType(Justification::centred);

    // editability
    hourLabel.setEditable(false);
    minuteLabel.setEditable(false);
    secondLabel.setEditable(false);
    splashLabel.setEditable(false);
    logoLabel.setEditable(false);

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
    g.fillAll(juce::Colours::lightgreen);

    totalTime = secondToTime(processorRef.totalSeconds);
    
    string pHour = to_string(totalTime.hour);
    string pMinute = to_string(totalTime.minute);
    string pSecond = to_string(totalTime.second);

    if (hourString != pHour) {
        hourString = pHour;
        hourLabel.setText(hourString + " hours", juce::dontSendNotification);
    }
    if (minuteString != pMinute) {
        minuteString = pMinute;
        minuteLabel.setText(minuteString + " minutes", juce::dontSendNotification);
    }
    if (secondString != pSecond) {
        secondString = pSecond;
        secondLabel.setText(secondString + " seconds", juce::dontSendNotification);
    }
}

void AudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    hourLabel.setBounds(WIDTH_PADDING, HEIGHT_PADDING, getWidth() - 20, 30);
    minuteLabel.setBounds(WIDTH_PADDING, HEIGHT_PADDING + DIST, getWidth() - 20, 30);
    secondLabel.setBounds(WIDTH_PADDING, HEIGHT_PADDING + 2*DIST, getWidth() - 20, 30);

    Rectangle<int> bounds = getLocalBounds();
    logoLabel.setBounds(bounds);

    bounds.reduce(2*WIDTH_PADDING, 2*HEIGHT_PADDING);
    splashLabel.setBounds(bounds);
}
