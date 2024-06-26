/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

NewProjectAudioProcessorEditor::NewProjectAudioProcessorEditor (NewProjectAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    setSize (400, 300);

    addAndMakeVisible(gainSlider);
    gainSlider.setRange(0.0, 2.0);
    gainSlider.setValue(1.0);
    gainSlider.onValueChange = [this]
    {
        audioProcessor.gainParam->setValueNotifyingHost(gainSlider.getValue());
    };

    addAndMakeVisible(pitchSlider);
    pitchSlider.setRange(0.5, 2.0);
    pitchSlider.setValue(1.0);
    pitchSlider.onValueChange = [this]
    {
        audioProcessor.pitchParam->setValueNotifyingHost(pitchSlider.getValue());  
    };
    addAndMakeVisible(ksToggle);
    ksToggle.setButtonText("Karplus-Strong");
    ksToggle.onClick = [this]
    {
        audioProcessor.setKarplusStrongEnabled(ksToggle.getToggleState());
    };

    gainLabel.setText("Gain (0 - 2)", juce::dontSendNotification);
    gainLabel.attachToComponent(&gainSlider, false);
    gainLabel.setJustificationType(juce::Justification::centredTop);

    pitchLabel.setText("Pitch (0.5 - 2)", juce::dontSendNotification);
    pitchLabel.attachToComponent(&pitchSlider, false);
    pitchLabel.setJustificationType(juce::Justification::centredTop);

    setSize(400, 300);

}


NewProjectAudioProcessorEditor::~NewProjectAudioProcessorEditor()
{
}

void NewProjectAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));
}

void NewProjectAudioProcessorEditor::resized()
{
    gainSlider.setBounds(50, 50, 300, 50);
    pitchSlider.setBounds(50, 150, 300, 50);
    ksToggle.setBounds(50, 250, 150, 30);
}
