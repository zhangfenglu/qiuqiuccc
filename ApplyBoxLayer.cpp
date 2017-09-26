#include "ApplyBoxLayer.h"
#include "HelpLayer.h"
#include "SunNetPublic.h"
#include "ApplyScene.h"
#include "GameVoice.h"
#include "ApplySaveGoldLayer.h"

bool ApplyBoxLayer::init()
{
	if (!Layer::init()) {
		return false;
	}


	_mainNode = CSLoader::createNode("apply/ApplayBoxLayer.csb");
	this->addChild(_mainNode);

	_initUI();
	return true;
}

void ApplyBoxLayer::initData(int grade, ValueMap &data, int week, int useGold, int groupId, string playerId)
{
	_groupId = groupId;
	_playerId = playerId;
	_week = week;

	int index = 0;
	int starNumber = 0;
	int starMax = 0;
	if (grade <= 3) {
		index = 0;
		starNumber = grade - 0;
		starMax = 3;
	}
	else if (grade <= 8) {
		index = 1;
		starNumber = grade - 3;
		starMax = 5;
	}
	else if (grade <= 13) {
		index = 2;
		starNumber = grade - 8;
		starMax = 5;
	}
	else if (grade <= 18) {
		index = 3;
		starNumber = grade - 13;
		starMax = 5;
	}
	else if (grade <= 23) {
		index = 4;
		starNumber = grade - 18;
		starMax = 5;
	}
	else if (grade <= 28) {
		index = 5;
		starNumber = grade - 23;
		starMax = 5;
	}
	else if (grade <= 33) {
		index = 6;
		starNumber = grade - 28;
		starMax = 5;
	}
	else if (grade <= 38) {
		index = 7;
		starNumber = grade - 33;
		starMax = 5;
	}
	else if (grade <= 45) {
		index = 8;
		starNumber = grade - 38;
		starMax = 7;
	}
	else if (grade <= 52) {
		index = 9;
		starNumber = grade - 45;
		starMax = 7;
	}
	else if (grade <= 59) {
		index = 10;
		starNumber = grade - 52;
		starMax = 7;
	}
	else if (grade <= 62) {
		index = 11;
		starNumber = grade - 59;
		starMax = 3;
	}
	else {
		starMax = 0;
		starNumber = grade - 59;
		index = 11;
	}		
	char url[100] = {};
	sprintf(url, "apply/dan/%02d.png", index);
	_dan->loadTexture(url);
	_danName->setString(data["dan"].asValueVector()[index].asString());

	for (int i = 0; i < starMax; i++)
	{
		_star[i]->setVisible(true);
		if (i < starNumber) {
			_star[i]->loadTexture("apply/dan/0001.png");
		}
		else {
			_star[i]->loadTexture("apply/dan/0002.png");
		}
	}

	if (index == 11 && starNumber > 3) {
		_star[0]->setVisible(true);
		_star[0]->loadTexture("apply/dan/0001.png");
		char cBuf[10] = {};
        sprintf(cBuf, "%d", starNumber);
		//itoa(starNumber, cBuf, 10);
		_starNumber->setString(cBuf);
		_starNumber->setVisible(true);
	}

	int saveNumber = grade * 100;
	int useNumber = ((useGold - saveNumber) > 1000) ? (useGold - saveNumber) : 1000;
	saveNumber = useGold - useNumber;
	
	char cbug[10] = {};
	sprintf(cbug, "%d", useNumber);
	_useText->setString(cbug);

	memset(cbug, 0, 10);
	sprintf(cbug, "%d", saveNumber);
	_saveText->setString(cbug);
	_duanwei = index;
}

void ApplyBoxLayer::_initUI()
{
	auto bg = static_cast<Sprite*>(_mainNode->getChildByName("bg"));
	auto cancel = static_cast<ui::Button*>(bg->getChildByName("cancel"));
	cancel->addClickEventListener([=](Ref* ref) {
		GameVoice::getInstance()->playClickBtnVoive();
		this->removeFromParent();
	});

	auto ok = static_cast<ui::Button*>(bg->getChildByName("ok"));
	ok->addClickEventListener([=](Ref* ref) {
		GameVoice::getInstance()->playClickBtnVoive();
		char url[100] = {};
		sprintf(url, applyMsg, ip);
		char data[100] = {};
		sprintf(data, applyInfoMsg, _playerId.c_str(), _groupId, applyTypeStr[0].c_str());
		SunNetPublic::getInstance()->sendUrlData(url, data, "applyInfoMsg", [=](bool isSucceed, std::vector<char>* buffer, string tag) {
			if (!isSucceed) {
				return;
			}

			std::string responseStr = std::string(buffer->begin(), buffer->end());
			((ApplyScene*)this->getParent())->applyReturn(responseStr);
		});
	});

	Button* rule = static_cast<ui::Button*>(bg->getChildByName("rule"));
	rule->addClickEventListener([=](Ref* ref) {
		GameVoice::getInstance()->playClickBtnVoive();
		auto* layer = ApplySaveGoldLayer::create();
		this->addChild(layer);
		layer->initData(_duanwei);
	});

	_dan = static_cast<ImageView*>(bg->getChildByName("dan"));
	_danName = static_cast<Text*>(bg->getChildByName("name"));
	for (auto i = 0; i < 7; i++) {
		char url[100] = {};
		sprintf(url, "star%d", i + 1);
		_star[i] = static_cast<ImageView*>(bg->getChildByName(url));
	}

	_starNumber = static_cast<Text*>(bg->getChildByName("starNumber"));

	_saveText = static_cast<Text*>(bg->getChildByName("saveText"));
	_useText = static_cast<Text*>(bg->getChildByName("useText"));
}
