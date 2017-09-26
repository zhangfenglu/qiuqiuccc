#include "ExchangeAwardLayer.h"

#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "GameVoice.h"

USING_NS_CC;

bool ExchangeAwardLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	_mainNode = CSLoader::createNode("exchange/ExchangeAwardLayer.csb");
	this->addChild(_mainNode);

	_initUI();

	return true;
}

void ExchangeAwardLayer::initData(std::vector<Prop> data)
{
	auto listView = ui::ListView::create();
	auto size = data.size();
	_mainNode->addChild(listView);
	listView->setItemsMargin(10);
	listView->setContentSize(Size(148 * size + listView->getItemsMargin() * (size - 1), 188));
	listView->setAnchorPoint(Vec2(0.5, 0.5));
	listView->setNormalizedPosition(Vec2(0.5, 0.45));
	listView->setDirection(cocos2d::ui::ScrollView::Direction::HORIZONTAL);
	listView->setTouchEnabled(false);
	listView->setClippingEnabled(false);
	for (auto i = 0; i < size; i++) {
		auto node = _pushListViewItem(data[i]);
		listView->pushBackCustomItem(node);
	}
}

void ExchangeAwardLayer::_initUI()
{
	ui::Button* ok = static_cast<ui::Button*>(_mainNode->getChildByName("ok"));
	ok->addClickEventListener([=](Ref* ref) {
		GameVoice::getInstance()->playClickBtnVoive();
		this->removeFromParent();
	});
}

ui::Layout* ExchangeAwardLayer::_pushListViewItem(Prop &prop)
{
	auto node = CSLoader::createNode("exchange/ExchangeAwardNode.csb");
	auto layout = ui::Layout::create();
	layout->setContentSize(Size(148, 188));
	layout->addChild(node);

	auto name = static_cast<ui::Text*>(node->getChildByName("name"));
	name->setString(prop.propName);;

	char data[10] = {};
	sprintf(data, "%d", prop.number);
	auto number = static_cast<ui::Text*>(node->getChildByName("number"));
	number->setString(data);
	return layout;
}
