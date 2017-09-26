#include "HelpLayer.h"
#include "GameVoice.h"

bool HelpLayer::init()
{
	if (!Layer::init()) {
		return false;
	}


	_mainNode = CSLoader::createNode("apply/ApplyHelpLayer.csb");
	this->addChild(_mainNode);

	Button* close = static_cast<ui::Button*>(_mainNode->getChildByName("close"));
	close->addClickEventListener([=](Ref* ref) {
		GameVoice::getInstance()->playClickBtnVoive();
		this->removeFromParent();
	});

	return true;
}
