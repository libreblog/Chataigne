/*
  ==============================================================================

    CommandChooserUI.cpp
    Created: 4 Nov 2016 11:23:37am
    Author:  bkupe

  ==============================================================================
*/

#include "CommandChooserUI.h"
#include "AssetManager.h"
#include "Style.h"

CommandChooserUI::CommandChooserUI() :
	noTargetText("[Click to select a command]")
{
	setInterceptsMouseClicks(true, true);

	targetBT = AssetManager::getInstance()->getTargetBT();
	targetBT->setInterceptsMouseClicks(false, false);

	addAndMakeVisible(targetBT);

	targetBT->addListener(this);
	setRepaintsOnMouseActivity(true);

	label.setFont(label.getFont().withHeight(12));
	label.setInterceptsMouseClicks(false, false);
	label.setText(noTargetText, dontSendNotification);
	addAndMakeVisible(label);

	
}

CommandChooserUI::~CommandChooserUI()
{
}

void CommandChooserUI::paint(Graphics & g)
{

	Colour c = NORMAL_COLOR;
	if (isMouseOver()) c = c.brighter();

	g.setGradientFill(ColourGradient(c.brighter(), (float)getLocalBounds().getCentreX(), (float)getLocalBounds().getCentreY(), c.darker(), 2.f, 2.f, true));
	g.fillRoundedRectangle(targetBT->getBounds().expanded(2).toFloat(), 2);

}

void CommandChooserUI::resized()
{
	Rectangle<int> r = getLocalBounds();
	targetBT->setBounds(r.removeFromLeft(r.getHeight()).reduced(2));
	r.removeFromLeft(2);
	label.setBounds(r.reduced(0, 2));
}


void CommandChooserUI::setLabel(const String & text)
{
	label.setText(text.isNotEmpty()?text:noTargetText, dontSendNotification);
}

void CommandChooserUI::showPopupAndGetDefinition()
{
	CommandDefinition * d = CommandFactory::showMenuAndGetCommand();
	if (d != nullptr) chooserListeners.call(&Listener::definitionChosen, d);
}

void CommandChooserUI::mouseDown(const MouseEvent &)
{
	showPopupAndGetDefinition();
}

void CommandChooserUI::buttonClicked(Button * b)
{
	if (b == targetBT) {} // move code here ?
}