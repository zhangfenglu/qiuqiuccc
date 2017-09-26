#include "ApplySaveGoldLayer.h"
#include "GameVoice.h"
#include "Resources.h"

bool ApplySaveGoldLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	_mainNode = CSLoader::createNode("apply/ApplyIconLayer.csb");
	addChild(_mainNode);

	_initUI();

	return true;
}

void ApplySaveGoldLayer::initData(int danwei)
{
	_duanwei = danwei;
	_duanWeiTableView->reloadData();
}

void ApplySaveGoldLayer::_initUI()
{
	auto bg = static_cast<Node*>(_mainNode->getChildByName("bg_1"));

	auto closeBtn = static_cast<ui::Button*>(_mainNode->getChildByName("close"));
	closeBtn->addClickEventListener([=](Ref* ref) {
		GameVoice::getInstance()->playClickBtnVoive();
		this->removeFromParent();
	});

	_duanWeiTableView = TableView::create(this, Size(1010.f, 523.f));
	_duanWeiTableView->setPosition(Vec2(135, 56));
	_mainNode->addChild(_duanWeiTableView);
	_duanWeiTableView->setDirection(cocos2d::extension::ScrollView::Direction::VERTICAL);
	_duanWeiTableView->setVerticalFillOrder(TableView::VerticalFillOrder::TOP_DOWN);
	_duanWeiTableView->setDelegate(this);
}



TableViewCell* ApplySaveGoldLayer::tableCellAtIndex(TableView* table, ssize_t idex)
{
	TableViewCell* cell = table->dequeueCell();
	if (!cell) {
		cell = new TableViewCell();
		cell->autorelease();
		auto node = CSLoader::createNode("apply/ApplyIconNode.csb");
		node->setTag(100);
		cell->addChild(node);
	}

	auto node = cell->getChildByTag(100);
	if (node) {
		auto bg = static_cast<ui::ImageView*>(node->getChildByName("bg"));
		auto danWei = static_cast<ui::ImageView*>(node->getChildByName("danWei"));
		auto duanWeiText = static_cast<ui::Text*>(node->getChildByName("duanWeiText"));
		auto gold = static_cast<ui::Text*>(node->getChildByName("gold"));

		char buf[128] = {0};
		sprintf(buf, "danWei/%02d.png", idex + 1);
		danWei->loadTexture(buf);

		std::string name = Resource::sharedResource()->stringData["dan"].asValueVector().at(idex).asString();
		duanWeiText->setString(name);
		memset(buf, 0, 128);
		sprintf(buf, "%d", Resource::sharedResource()->stringData["danSaveGold"].asValueVector().at(idex).asInt());
		gold->setString(buf);
		if (_duanwei == idex) {
			duanWeiText->setString(name + "(当前段位)");
			bg->loadTexture("apply/iconHelp/selfBg.png");
		}
		else {
			bg->loadTexture("apply/iconHelp/bgLan.png");
		}
	}

	return cell;
}

cocos2d::Size ApplySaveGoldLayer::cellSizeForTable(TableView* table)
{
	return Size(1006.f, 122.f);
}

ssize_t ApplySaveGoldLayer::numberOfCellsInTableView(TableView* table)
{
	return 12;
}
