#pragma once

#include <juce_audio_processors/juce_audio_processors.h>
#include <filesystem>

//==============================================================================
class AudioPluginAudioProcessor final : public juce::AudioProcessor, private juce::Timer
{
public:
    //==============================================================================
    AudioPluginAudioProcessor();
    ~AudioPluginAudioProcessor() override;

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;

    void processBlock (juce::AudioBuffer<float>&, juce::MidiBuffer&) override;
    using AudioProcessor::processBlock;

    //==============================================================================
    juce::AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const juce::String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const juce::String getProgramName (int index) override;
    void changeProgramName (int index, const juce::String& newName) override;

    //==============================================================================
    void getStateInformation (juce::MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    int writeFile();

    double totalSeconds;

    void timerCallback() override;

private:
    //==============================================================================
    // juce::AudioProcessorValueTreeState apvts;
    // std::atomic<int>* hourParameter = nullptr;
    // std::atomic<int>* hourParameter = nullptr;
    // std::atomic<int>* hourParameter = nullptr;
    // std::string path;
    // std::filesystem::path cwd;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AudioPluginAudioProcessor)
};
