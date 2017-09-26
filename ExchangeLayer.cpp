#include "ExchangeLayer.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
#include "SunNetPublic.h"
#include "ExchangeAwardLayer.h"
#include "GameVoice.h"

using namespace cocos2d::ui;

bool ExchangeLayer::init()
{
	if (!Layer::init()) {
		return false;
	}

	_mainNode = CSLoader::createNode("exchange/ExchangeLayer.csb");
	this->addChild(_mainNode);

	_initUI();
	return true;
}

void ExchangeLayer::_initUI()
{
	ui::Button* close = static_cast<ui::Button*>(_mainNode->getChildByName("close"));
	close->addClickEventListener([=](Ref* ref) {
		GameVoice::getInstance()->playClickBtnVoive();
		this->removeFromParent();
	});

	auto editBox = EditBox::create(Size(508, 71), "exchange/editbox.png");
	_mainNode->addChild(editBox);
	editBox->setPosition(_mainNode->getChildByName("editboxBg")->getPosition());
	editBox->setInputFlag(EditBox::InputFlag::LOWERCASE_ALL_CHARACTERS);
	editBox->setMaxLength(18);

	ui::Button* get = static_cast<ui::Button*>(_mainNode->getChildByName("get"));
	get->addClickEventListener([=](Ref* ref) {
		GameVoice::getInstance()->playClickBtnVoive();
		char url[100] = {};
		std::string str = editBox->getText();
		sprintf(url, exchangeMsg, ip, SunNetPublic::getInstance()->playerId.c_str(), str.c_str());
		SunNetPublic::getInstance()->sendUrl(url, "exchangeMsg", [=](bool isSucceed, std::vector<char>* buffer, string tag) {
			if (!isSucceed) {
				return;
			}

			auto plistData  = FileUtils::getInstance()->getValueMapFromFile("apply/string.plist");

			std::string responseStr = std::string(buffer->begin(), buffer->end());
			rapidjson::Document jsonData;
			jsonData.Parse<rapidjson::kParseDefaultFlags>(responseStr.c_str());
			if (jsonData.HasParseError()) {
				CCLOG("GetParseError %s\n", jsonData.GetParseError());
				return;
			}

			if (jsonData.HasMember("ok")) {
				bool isOk = jsonData["ok"].GetBool();
				if (isOk) {
					auto layer = ExchangeAwardLayer::create();
					this->getParent()->addChild(layer, 4);
					
					std::vector<Prop> data;
					Prop prop;
					prop.number = jsonData["resultObj"]["goldcoins"].GetInt();
					prop.propName = plistData["prop"].asValueMap()["icon"].asValueMap()["name"].asString();
					data.push_back(prop);
					layer->initData(data);
				}
				else {
					string str = jsonData["message"].GetString();
					auto node = SunNetPublic::getInstance()->showTips(str);
					this->addChild(node);
				}
			}
		});

	});
}
