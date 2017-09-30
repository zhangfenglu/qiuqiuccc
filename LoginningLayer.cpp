#include "LoginningLayer.h"
#include "MainScene.h"
#include "SimpleTools.h"
#include "GameVoice.h"
using namespace cocos2d::network;

#include "spine/Json.h"
#include "spine/extension.h"


bool LoginingLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto rootNode = CSLoader::createNode("LoginningLayer.csb");

	addChild(rootNode);
	
	loadingBar = (cocos2d::ui::LoadingBar*)seekNodeByName(rootNode, "ProgressBar");
	tishi = (cocos2d::ui::Text*)seekNodeByName(rootNode, "tishi");
	str = tishi->getString();
    


	box = (cocos2d::ui::ImageView*)seekNodeByName(rootNode,"box");
	btnGenXin = (cocos2d::ui::Button*)seekNodeByName(rootNode, "btnGenXin");
	
	scheduleUpdate();
	return true;
}

void LoginingLayer::update(float delta)
{
	if (m_nCount <= 98)
	{
		if ((int)(delta * 1000000) % 2 == 0)
			m_nCount++;
	}
	else
	{
		if ((int)(delta * 1000000) % 20 == 0)
			m_nCount++;
	}
	m_nCount++;

	if (m_nCount >= 100)
	{
		unscheduleUpdate();
        string url = "http://47.93.50.101:8080/QQWar/Qqwar/updateVersion?type=ios";
        requestFroGet(url, [=](HttpClient *sender, HttpResponse *response)
                      {
                          if (response == nullptr || !response->isSucceed())
                          {
                              CCLOG("responese is null");
                              CCLOG("responese not succeed");
                              
                              return;
                          }
                          
                          vector<char> *buffer = response->getResponseData();
                          
                          std::string responseStr = std::string(buffer->begin(), buffer->end());
                          CCLOG("%s", responseStr.c_str());
                          
                          
                          
                          auto pScene = Scene::create();
                          WebSocketLayer* socket = WebSocketLayer::create();
                          pScene->addChild(socket, 0, 1);
                          
                          MainScene* layer = MainScene::create();
                          pScene->addChild(layer, 2 , 0);
                          Director::getInstance()->replaceScene(pScene);                          
                          
                      }, "GetVersion");

	}
	else
	{
		loadingBar->setOpacity(255);
		loadingBar->setPercent(m_nCount);
		std::ostringstream ss("");
		ss << str << m_nCount << "%";
		tishi->setString(ss.str().c_str());
	}

}

LoginingLayer::LoginingLayer()
: m_nCount(0)
{

}

LoginingLayer::~LoginingLayer()
{
	unscheduleUpdate();
}

/*
void LoginingLayer::onHttpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
{
	if (!response)
	{
		return;
	}

	// You can get original request type from: response->request->reqType
	if (0 != strlen(response->getHttpRequest()->getTag()))
	{
		log("%s completed", response->getHttpRequest()->getTag());
	}

	long statusCode = response->getResponseCode();
	char statusString[64] = {};
	sprintf(statusString, "HTTP Status Code: %ld, tag = %s", statusCode, response->getHttpRequest()->getTag());
	//_labelStatusCode->setString(statusString);
	log("response code: %ld", statusCode);

	if (!response->isSucceed())
	{
		log("response failed");
		log("error buffer: %s", response->getErrorBuffer());
		return;
	}

	// dump data
	std::vector<char> *buffer = response->getResponseData();
	log("Http Test, dump data: ");
	for (unsigned int i = 0; i < buffer->size(); i++)
	{
		log("%c", (*buffer)[i]);
	}
	log("\n");
	if (response->getHttpRequest()->getReferenceCount() != 2)
	{
		log("request ref count not 2, is %d", response->getHttpRequest()->getReferenceCount());
	}

	std::string responseStr = std::string(buffer->begin(), buffer->end());
	CCLOG("%s", responseStr.c_str());

	//Json* root = Json_create(responseStr.c_str());
	//Json* version = Json_getItem(root, "version");
	//
	////if (version->type == Json_String)
	//{

	//	CCLOG(version->valueString);
	//}

}
*/
