#include "SunNetPublic.h"
#include "ApplyScene.h"
#include "ExchangeLayer.h"
#include "Global.h"

SunNetPublic::SunNetPublic()
{
	_labTips = nullptr;
	playerId = Global::getInstance()->GetAccountInfo().playerid;
}


SunNetPublic::~SunNetPublic()
{
}

static SunNetPublic* p = nullptr;
SunNetPublic* SunNetPublic::getInstance()
{
	if (p == nullptr) {
		p = new SunNetPublic();
	}
	return p;
}

void SunNetPublic::sendUrl(string url, string tag, sunHttpRequestCallback callback)
{
	cocos2d::log(url.c_str());
	HttpRequest* request = new  HttpRequest();
	request->setUrl(url.c_str());
	request->setRequestType(HttpRequest::Type::GET);
	request->setResponseCallback([=](cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response) {
		bool isSucceed = true;
		if (!response) { isSucceed = false; }

		if (0 == strlen(response->getHttpRequest()->getTag())) { isSucceed = false; }
		if (!response->isSucceed()) { isSucceed = false; }

		callback(isSucceed, response->getResponseData(), response->getHttpRequest()->getTag());
	});
	request->setTag(tag.c_str());
	HttpClient::getInstance()->send(request);
	request->release();
}

void SunNetPublic::sendUrlData(string url, string data, string tag, sunHttpRequestCallback callback)
{
	cocos2d::network::HttpRequest * request = new cocos2d::network::HttpRequest();
	request->setRequestType(cocos2d::network::HttpRequest::Type::POST);// set request type
	request->setResponseCallback([=](cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response) {
		bool isSucceed = true;
		if (!response) { isSucceed = false; }

		if (0 == strlen(response->getHttpRequest()->getTag())) { isSucceed = false; }
		if (!response->isSucceed()) { isSucceed = false; }

		callback(isSucceed, response->getResponseData(), response->getHttpRequest()->getTag());
	});
	request->setTag(tag.c_str());
	request->setUrl(url.c_str());
	request->setRequestData(data.c_str(), strlen(data.c_str()));
	cocos2d::network::HttpClient::getInstance()->send(request);
	request->release();
}

void SunNetPublic::addApplyLayer(cocos2d::Node* node) {
	auto layer = ApplyScene::create();
	node->addChild(layer, 3);
}

cocos2d::Node* SunNetPublic::showTips(std::string str)
{
	auto visibleSize = cocos2d::Director::getInstance()->getVisibleSize();
	cocos2d::Point orignPos = cocos2d::Point(visibleSize.width / 2, visibleSize.height / 3);
	int nSpace = 100;
	float time = 1;

	if (_labTips) {
		_labTips->removeFromParent();
	}

	_labTips = Text::create(str, "", 36);
	((Text*)_labTips)->setTextColor(Color4B(255, 0, 0, 255));
	_labTips->setPosition(orignPos);
	_labTips->runAction(cocos2d::Sequence::createWithTwoActions(cocos2d::MoveTo::create(time, cocos2d::Point(orignPos.x, orignPos.y + nSpace)), cocos2d::CallFunc::create([=]() {
		_labTips->removeFromParent();
		_labTips = nullptr;
	})));

	return _labTips;
}

void SunNetPublic::addExchangeLayer(cocos2d::Node* node)
{
	auto layer = ExchangeLayer::create();
	node->addChild(layer, 3);
}
