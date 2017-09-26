#include "ApplyScene.h"
#include "SimpleAudioEngine.h"
#include "ApplyBoxLayer.h"
#include "HelpLayer.h"
#include "editor-support/spine/Json.h"
#include <math.h>
#include "SunNetPublic.h"
#include "SunPublic.h"
#include "GameVoice.h"

USING_NS_CC;
using namespace network;
using namespace cocos2d::ui;

// on "init" you need to initialize your instance
bool ApplyScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	_useGold = 8000;
	_useDiamond = 1;
	_nodeAction = nullptr;
	_stringData = FileUtils::getInstance()->getValueMapFromFile("apply/string.plist");
	_useType = true;

	_mainNode = CSLoader::createNode("apply/ApplyScene.csb");
	this->addChild(_mainNode);

	_rightMoveAction = CSLoader::createTimeline("apply/ApplyScene.csb");
	_mainNode->runAction(_rightMoveAction);
	
	ui::Button* close = static_cast<ui::Button*>(_mainNode->getChildByName("close"));
	close->addClickEventListener([=](Ref* ref) {
		GameVoice::getInstance()->playClickBtnVoive();
		this->removeFromParent();
	});

	_initLeftUI();
	_initRightUI();

	char url[100] = {};
	sprintf(url, playerInfoMsg, ip, SunNetPublic::getInstance()->playerId.c_str());
	SunNetPublic::getInstance()->sendUrl(url, "playerInfo", [=](bool isSucceed, std::vector<char>* buffer, string tag) {
		if (!isSucceed) {
			return;
		}

		std::string responseStr = std::string(buffer->begin(), buffer->end());
		_initPlayerInfoMsg(responseStr);
	});

	//_initLeftData();
    return true;
}

void ApplyScene::_initLeftUI()
{
	auto leftNode = _mainNode->getChildByName("left");

	///
	ui::Button* record = static_cast<ui::Button*>(leftNode->getChildByName("record"));
	record->addClickEventListener([=](Ref* ref) {
		GameVoice::getInstance()->playClickBtnVoive();
	});

	for (auto i = 0; i < 5; i++)
	{
		char name[10] = {};
		sprintf(name, "small_%d", i + 1);
		auto btn = static_cast<ui::Button*>(leftNode->getChildByName(name));
		btn->setTag(201 + i);
		btn->addClickEventListener([=](Ref* ref) {
			GameVoice::getInstance()->playClickBtnVoive();
			_checkLeftButton(((Node*)ref)->getTag());
			auto node = _openBtnAction(false);
			((Node*)ref)->addChild(node);
			node->setNormalizedPosition(Vec2(0.5, 0.5));
		});
		_smallGrail[i] = btn;
	}

	_bigGrail = static_cast<ui::Button*>(leftNode->getChildByName("big"));
	_bigGrail->addClickEventListener([=](Ref* ref) {
		GameVoice::getInstance()->playClickBtnVoive();
		_checkLeftButton(206);
		auto node = _openBtnAction(true);
		((Node*)ref)->addChild(node);
		node->setNormalizedPosition(Vec2(0.5, 0.5));
	});
}

void ApplyScene::_checkLeftButton(int tag)
{
	char url[100] = {};
	_checkIndex = tag;
	sprintf(url, groupMsg, ip, _playerData.playerId.c_str(), _checkIndex);
	SunNetPublic::getInstance()->sendUrl(url, "groupMsg", [=](bool isSucceed, std::vector<char>* buffer, string tag) {
		if (!isSucceed) { return;}

		std::string responseStr = std::string(buffer->begin(), buffer->end());
		_initGroupMsg(responseStr);
	});
}

void ApplyScene::_initRightUI()
{
	_rightNode = _mainNode->getChildByName("right");

	_applyBtn = static_cast<ui::Button*>(_rightNode->getChildByName("apply"));
	_applyBtn->addClickEventListener([=](Ref* ref) {
		GameVoice::getInstance()->playClickBtnVoive();
		if (_useType == true && _useConsumeType == 2) {
			ApplyBoxLayer* layer = ApplyBoxLayer::create();
			this->addChild(layer);
			layer->initData(_playerData.grade, _stringData, _week, _useGold, _gouldId, _playerData.playerId);
		}
		else {
			char url[100] = {};
			sprintf(url, applyMsg, ip);
			char data[100] = {};
			if (_useType == false)
				sprintf(data, applyInfoMsg, _playerData.playerId.c_str(), _gouldId, applyTypeStr[1].c_str());
			else
				sprintf(data, applyInfoMsg, _playerData.playerId.c_str(), _gouldId, applyTypeStr[2].c_str());
			SunNetPublic::getInstance()->sendUrlData(url, data, "applyInfoMsg", [=](bool isSucceed, std::vector<char>* buffer, string tag) {
				if (!isSucceed) {
					return;
				}

				std::string responseStr = std::string(buffer->begin(), buffer->end());
				applyReturn(responseStr);
			});
		}
	});

	_applyText = static_cast<ui::Text*>(_rightNode->getChildByName("noApply"));

	_leftImage = static_cast<ui::ImageView*>(_rightNode->getChildByName("left_image"));
	_RightImage = static_cast<ui::ImageView*>(_rightNode->getChildByName("right_image"));

	_leftCheckBox = static_cast<ui::Button*>(_rightNode->getChildByName("checkBox_left"));
	_leftCheckBox->addClickEventListener([=](Ref* ref) {
		GameVoice::getInstance()->playClickBtnVoive();
		_leftImage->setVisible(!_leftImage->isVisible());
		_RightImage->setVisible(!_RightImage->isVisible());
		_useType = _leftImage->isVisible();
	});

	_rightCheckBox = static_cast<ui::Button*>(_rightNode->getChildByName("checkBox_right"));
	_rightCheckBox->addClickEventListener([=](Ref* ref) {
		GameVoice::getInstance()->playClickBtnVoive();
		_leftImage->setVisible(!_leftImage->isVisible());
		_RightImage->setVisible(!_RightImage->isVisible());
		_useType = _leftImage->isVisible();
	});

	_textTime = static_cast<ui::Text*>(_rightNode->getChildByName("textTime"));
	_ruleText = static_cast<ui::Text*>(_rightNode->getChildByName("ruleText"));
	_title = static_cast<ui::Text*>(_rightNode->getChildByName("title"));

	for (auto i = 0; i < 3; i++)
	{
		char name[10] = {};
		sprintf(name, "%d", i + 1);
		_prograssBg[i] = static_cast<ui::ImageView*>(_rightNode->getChildByName(name));
		_bar[i] = static_cast<ui::LoadingBar*>(_prograssBg[i]->getChildByName("LoadingBar"));
		_bar[i]->setPercent(0);
	}

	_titleImage = static_cast<ui::ImageView*>(_rightNode->getChildByName("title_image"));
	_diamondText = static_cast<ui::Text*>(_rightNode->getChildByName("diamond_text"));
	_numberText = static_cast<ui::Text*>(_rightNode->getChildByName("number_text"));
	_icon = static_cast<ui::ImageView*>(_rightNode->getChildByName("icon"));

	Button* help = static_cast<ui::Button*>(_rightNode->getChildByName("help"));
	help->addClickEventListener([=](Ref* ref) {
		GameVoice::getInstance()->playClickBtnVoive();
		Node* layer = HelpLayer::create();
		this->addChild(layer);
	});
}

void ApplyScene::_initPlayerInfoMsg(std::string data)
{
	rapidjson::Document jsonData;
	jsonData.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
	if (jsonData.HasParseError()) {
		CCLOG("GetParseError %s\n", jsonData.GetParseError());
		return;
	}

	if (jsonData.HasMember("resultObj")) {
		if (jsonData["resultObj"].IsObject()) {
			_playerData.playerId = jsonData["resultObj"]["id"].IsNull() ? "0" : jsonData["resultObj"]["id"].GetString();
			_playerData.timeStr = jsonData["resultObj"]["time"].IsNull() ? "0" : jsonData["resultObj"]["time"].GetString();
			_playerData.monthcard = jsonData["resultObj"]["monthcard"].IsNull() ? 0 : jsonData["resultObj"]["monthcard"].GetInt();
			_playerData.yearcard = jsonData["resultObj"]["yearcard"].IsNull() ? 0 : jsonData["resultObj"]["yearcard"].GetInt();
			_playerData.diamonds = jsonData["resultObj"]["diamonds"].IsNull() ? 0 : jsonData["resultObj"]["diamonds"].GetInt();
			_playerData.goldcoins = jsonData["resultObj"]["goldcoins"].IsNull() ? 0 : jsonData["resultObj"]["goldcoins"].GetInt();
			_playerData.likenumber = jsonData["resultObj"]["likenumber"].IsNull() ? 0 : jsonData["resultObj"]["likenumber"].GetInt();
			_playerData.grade = jsonData["resultObj"]["grade"].IsNull() ? 1 : jsonData["resultObj"]["grade"].GetInt();

			_playerData.time = _changeStrTimeToNumber(_playerData.timeStr);

			if (_playerData.time.week == 1 || _playerData.time.week == 3 || _playerData.time.week == 5) {
				_openGrailByState(false);
				//_openAllGrail();
			}
			else if (_playerData.time.week == 2 || _playerData.time.week == 4 || _playerData.time.week == 6) {
				_openGrailByState(true);
				//_openAllGrail();
			}
			else {
				_openAllGrail();
			}
		}
	}
}

void ApplyScene::_initGroupMsg(std::string data)
{
	rapidjson::Document jsonData;
	jsonData.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
	if (jsonData.HasParseError()) {
		CCLOG("GetParseError %s\n", jsonData.GetParseError());
		return;
	}

	bool enroll = false;
	if (jsonData.HasMember("enroll")) { enroll = jsonData["enroll"].GetBool(); }
	int week = 0;
	if (jsonData.HasMember("week")) { week = jsonData["week"].GetInt(); }
	if (jsonData.HasMember("meleeRank") && jsonData["meleeRank"].HasMember("id")) { _gouldId = jsonData["meleeRank"]["id"].GetInt(); };
	int playerNumber = 0;
	if (jsonData.HasMember("meleeRank") && jsonData["meleeRank"].HasMember("ranks")) { playerNumber = jsonData["meleeRank"]["ranks"].GetInt(); };

	std::string time;
	if (jsonData.HasMember("time")) { time = jsonData["time"].GetString(); }
	std::string openTime;
	if (jsonData.HasMember("opentime")) { openTime = jsonData["opentime"].GetString(); }
	week--;

	_initRightData(enroll, playerNumber, openTime, week, _changeStrTimeToNumber(time));
}

void ApplyScene::_initRightData(bool enroll, int playerNumber, std::string openTime, int week, SunTime time)
{

	for (int i = 0; i < 3; i++)
	{
		_bar[i]->setPercent(0);
		_prograssBg[i]->loadTexture("apply/right/progress_gray.png");
	}

	_week = week;
	if (_checkIndex == 206) {
		_titleImage->loadTexture("apply/right/grail_100.png");
		_icon->loadTexture("apply/right/flower.png");
		_useConsumeType = 1;
	}
	else{
		_titleImage->loadTexture("apply/right/grail_20.png");
		_icon->loadTexture("apply/right/icon.png");
		_useConsumeType = 2;
	}
	
	_rightMoveAction->play("action", false);
	_rightNode->setVisible(true);
	if (playerNumber <= 30) {
		_bar[0]->setPercent(playerNumber / 30.f * 100);
		_ruleText->setString(_stringData["number30"].asString());
		_prograssBg[0]->loadTexture("apply/right/progress_light.png");
	}
	else if (playerNumber <= 900) {
		_bar[0]->setPercent(100);
		_prograssBg[0]->loadTexture("apply/right/progress_light.png");
		_bar[1]->setPercent(playerNumber / 900.f * 100);
		_ruleText->setString(_stringData["number900"].asString());
		_prograssBg[1]->loadTexture("apply/right/progress_light.png");
	}
	else if (playerNumber <= 2700) {
		_bar[0]->setPercent(100);
		_prograssBg[0]->loadTexture("apply/right/progress_light.png");
		_bar[1]->setPercent(100);
		_prograssBg[1]->loadTexture("apply/right/progress_light.png");
		_bar[2]->setPercent(playerNumber / 2700.f * 100);
		_ruleText->setString(_stringData["number2700"].asString());
		_prograssBg[2]->loadTexture("apply/right/progress_light.png");
	}
	else {
		_bar[0]->setPercent(100);
		_prograssBg[0]->loadTexture("right/progress_light.png");
		_bar[1]->setPercent(100);
		_prograssBg[1]->loadTexture("right/progress_light.png");
		_bar[2]->setPercent(100);
		_prograssBg[2]->loadTexture("right/progress_light.png");
		_ruleText->setString(_stringData["number2700"].asString());
	}

	char name[100] = {};
	sprintf(name, _stringData["openStr"].asString().c_str(), openTime.c_str());
	_textTime->setString(name);
	memset(name, 0, 100);
	sprintf(name, _stringData["titleStr"].asString().c_str(), _stringData["titleStrArray"].asValueVector()[week].asString().c_str(), openTime.c_str());
	_title->setString(name);

	int pot = openTime.find(":");
	auto hour = atoi(openTime.substr(pot - 2, 2).c_str());
	auto minute = atoi(openTime.substr(pot + 1, 2).c_str());

	// 提前5分钟
	int aheadTimeMinute = minute - 5;
	int aheadTimeHour = hour;
	if (aheadTimeMinute < 0) {
		aheadTimeMinute += 60;
		aheadTimeHour--;
	}
	int aheadTime = aheadTimeHour * 60 + aheadTimeMinute;

	// 延后40分钟
	int delayTimeMinute = minute + 40;
	int delayTimeHour = hour;
	if (delayTimeMinute >= 60) {
		delayTimeMinute -= 60;
		delayTimeHour++;
	}
	int delayTime = delayTimeHour * 60 + delayTimeMinute;
	int nowTime = time.hour * 60 + time.minute;

	if (nowTime > aheadTime && nowTime < delayTime && week == _playerData.time.week) {
		_applyBtn->setVisible(false);
		_applyText->setVisible(true);
	}
	else {
		if (enroll) {
			_applyBtn->setTouchEnabled(false); 
			_applyBtn->loadTextures("apply/right/applyOk.png", "", "");
		}
		else {
			_applyBtn->setTouchEnabled(true);
			_applyBtn->loadTextures("apply/right/apply_btn.png", "", "");
		}
	}
}


void ApplyScene::_openAllGrail()
{
	for (auto i = 0; i < 5; i++)
	{
		_smallGrail[i]->setBright(true);
	}
	_bigGrail->setBright(true);
}

void ApplyScene::_openGrailByState(bool state)
{
	for (auto i = 0; i < 5; i++)
	{
		_smallGrail[i]->setBright(state);
	}
	_bigGrail->setBright(!state);
}

SunTime ApplyScene::_changeStrTimeToNumber(string timeStr)
{
	SunTime time;
	int startPot = 0;
	int y, m, d;
	string hourStr, minuteStr;
	string year, month, day;

	auto pot =timeStr.find(_stringData["year"].asString());
	if (pot == string::npos) {
		pot = timeStr.find("-");
		if (pot == string::npos) {
			time.year = 2017;
			time.month = 9;
			time.day = 9;
			time.week = 6;
			time.hour = 9;
			time.minute = 9;
			time.second = 9;
			return time;
		}
		year = "-";
		month = "-";
		day = "-";
	}
	else {
		year = _stringData["year"].asString();
		month = _stringData["month"].asString();
		day = _stringData["day"].asString();
	}
	auto yearStr = timeStr.substr(startPot, pot);
	y = atoi(yearStr.c_str());

	startPot = pot + year.size();
	auto monthStr = timeStr.substr(startPot, 2);
	m = atoi(monthStr.c_str());

	startPot = startPot + month.size() + monthStr.size();
	auto dayStr = timeStr.substr(startPot, 2);
	d = atoi(dayStr.c_str());

	pot = timeStr.find(":");

	hourStr = timeStr.substr(pot - 2, 2);
	minuteStr = timeStr.substr(pot + 1, 2);

	int week = (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7 + 1;

	time.year = y;
	time.month = m;
	time.day = d;
	time.week = week;
	time.hour = atoi(hourStr.c_str());
	time.minute = atoi(minuteStr.c_str());
	return time;
}

Node* ApplyScene::_openBtnAction(bool state)
{
	if (_nodeAction) {
		_nodeAction->removeFromParent();
	}

	string actionCsb;
	if (state) {
		actionCsb = "apply/Big.csb";
	}
	else {
		actionCsb = "apply/Small.csb";
	}
	_nodeAction = CSLoader::createNode(actionCsb);
	auto action = CSLoader::createTimeline(actionCsb);
	_nodeAction->runAction(action);
	action->play("action", true);
	return _nodeAction;
}

void ApplyScene::applyReturn(std::string data)
{
	rapidjson::Document jsonData;
	jsonData.Parse<rapidjson::kParseDefaultFlags>(data.c_str());
	if (jsonData.HasParseError()) {
		CCLOG("GetParseError %s\n", jsonData.GetParseError());
		return;
	}

	bool ok = jsonData["ok"].GetBool();
	string msg = jsonData["message"].GetString();

	auto node = SunNetPublic::getInstance()->showTips(msg);
	this->addChild(node);
}


