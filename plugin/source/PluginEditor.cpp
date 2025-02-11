// #include "PluginProcessor.h"
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
    // hourLabel = Label("hourLabel", "0");
    // minuteLabel = Label("minuteLabel", "0");
    // secondLabel = Label("secondLabel", "0");

    addAndMakeVisible(hourLabel);
    addAndMakeVisible(minuteLabel);
    addAndMakeVisible(secondLabel);
    addAndMakeVisible(splashLabel);

    totalTime = secondToTime(processorRef.totalSeconds);

    hourString = to_string(totalTime.hour);
    minuteString = to_string(totalTime.minute);
    secondString = to_string(totalTime.second);

    hourLabel.setText(hourString + " hours", juce::dontSendNotification);
    minuteLabel.setText(minuteString + " minutes", juce::dontSendNotification);
    secondLabel.setText(secondString + " seconds", juce::dontSendNotification);

    randSplash = rand() % SPLASH_ARRAY_SIZE;
    splashLabel.setText(splashText[randSplash], juce::dontSendNotification);

    font = juce::Font("Courier", 20.0f, juce::Font::bold);

    // label font setting
    hourLabel.setFont(font);
    minuteLabel.setFont(font);
    secondLabel.setFont(font);
    splashLabel.setFont(font);

    // label color setsting
    hourLabel.setColour(juce::Label::textColourId, juce::Colour(216, 132, 132));
    minuteLabel.setColour(juce::Label::textColourId, juce::Colour(216, 132, 132));
    secondLabel.setColour(juce::Label::textColourId, juce::Colour(216, 132, 132));
    splashLabel.setColour(juce::Label::textColourId, juce::Colour(216, 132, 132));

    splashLabel.setJustificationType(Justification::bottomRight);

    hourLabel.setEditable(false);
    minuteLabel.setEditable(false);
    secondLabel.setEditable(false);
    splashLabel.setEditable(false);

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

    // g.setColour (juce::Colour(216, 132, 132));
    

    // font.setBold(true);

    // g.setFont(font);
    // g.setFont(20.0f);
    // g.setTypefaceName("Courier");

    // apply width and height padding to this bounding box
    // juce::Rectangle<int> splashBounds = juce::Rectangle<int>(0, 0, getWidth() - WIDTH_PADDING, getHeight() - HEIGHT_PADDING);
    // g.drawFittedText (splashText[randSplash], splashBounds, juce::Justification::bottomRight, 1);
    // g.drawFittedText(splashText[randSplash], getWidth() - WIDTH_PADDING, getHeight() - HEIGHT_PADDING, getWidth()/2, getHeight()/2, juce::Justification::left, 2);
    // g.drawFittedText(":", getWidth()/2 + 10, getHeight()/2 - 10, getWidth() - 20, 30, juce::Justification::centred, 1);
    // g.drawFittedText(":", getWidth()/2 + 10, getHeight()/2, getWidth() - 20, 30, juce::Justification::centred, 1);


// (const String &text, int x, int y, int width, int height, Justification justificationFlags, int maximumNumberOfLines, float minimumHorizontalScale=0.0f

    totalTime = secondToTime(processorRef.totalSeconds);
    
    string pHour = to_string(totalTime.hour);
    string pMinute = to_string(totalTime.minute);
    string pSecond = to_string(totalTime.second);

    // std::string pHour = std::to_string(*(processorRef.hour));
    // std::string pMinute = std::to_string(*(processorRef.minute));
    // std::string pSecond = std::to_string(*(processorRef.second));

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
        // ideally only need to repaint here because a change in the second is guaranteed when a change in the hour/minute occurs
    }
    // repaint();
}

void AudioPluginAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    // ig keep the units one for each line to avoid overlap when the vals increase?
    // maybe add labels (e.g. Hours: x \n Minutes: y \n Seconds: z \n)
    // hourLabel.setBounds(getWidth()/2, getHeight()/2 - 15, getWidth() - 20, 30);
    // minuteLabel.setBounds(getWidth()/2, getHeight()/2, getWidth() - 20, 30);
    // secondLabel.setBounds(getWidth()/2, getHeight()/2 + 15, getWidth() - 20, 30);
    hourLabel.setBounds(WIDTH_PADDING, HEIGHT_PADDING, getWidth() - 20, 30);
    minuteLabel.setBounds(WIDTH_PADDING, HEIGHT_PADDING + DIST, getWidth() - 20, 30);
    secondLabel.setBounds(WIDTH_PADDING, HEIGHT_PADDING + 2*DIST, getWidth() - 20, 30);

    Rectangle<int> bounds = getLocalBounds();
    // bounds.width -= WIDTH_PADDING;
    // bounds.height -= HEIGHT_PADDING;
    bounds.reduce(2*WIDTH_PADDING, 2*HEIGHT_PADDING);
    splashLabel.setBounds(bounds);
}
