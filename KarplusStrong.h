#pragma once

#include <JuceHeader.h>

class KarplusStrong
{
public:
    KarplusStrong();
    void prepare(double sampleRate, int samplesPerBlock);
    void process(juce::AudioBuffer<float>& buffer);
    void setFrequency(float freq);
    void pluck();

private:
    float frequency;
    int sampleRate;
    juce::AudioBuffer<float> delayBuffer;
    int writePosition;
    float smoothing;
    float decay;
};
