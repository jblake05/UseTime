#pragma once

#include "PluginProcessor.h"

using namespace juce;
using namespace std;
//==============================================================================
class AudioPluginAudioProcessorEditor final : public juce::AudioProcessorEditor, private juce::Timer
{
public:
    explicit AudioPluginAudioProcessorEditor (AudioPluginAudioProcessor&);
    ~AudioPluginAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AudioPluginAudioProcessor& processorRef;

    // Labels for timer
    Label hourLabel;
    Label minuteLabel;
    Label secondLabel;
    Label splashLabel;
    Label logoLabel;

    // Strings for labels, used for comparison => efficient repainting
    string hourString;
    string minuteString;
    string secondString;

    // Font font;

    void timerCallback() final {
        repaint();
    }

    static const int SPLASH_ARRAY_SIZE = 5;
    std::string splashText[SPLASH_ARRAY_SIZE] = {"Good luck!", "Make things :)", "Have fun!", "Keep going!", "You can do it!"};

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessorEditor)
};
