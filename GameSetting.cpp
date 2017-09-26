#include "GameSetting.h"
#include "SimpleTools.h"
#include "GameVoice.h"

using namespace cocos2d::network;

bool GameSetting::init()
{
	if (!Layer::init())
	{
		return false;
	}
	auto rootNode = CSLoader::createNode("GameSetting.csb");

	addChild(rootNode);

	


    auto loginBg = seekNodeByName(rootNode, "loginBg");

	btnLogin = (cocos2d::ui::Button*)seekNodeByName(rootNode,"btnLogin");

	btnLogin->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			GameVoice::getInstance()->playClickBtnVoive();
			clickBtnToLogin();
		}
	});

	//zhangHao = (cocos2d::ui::TextField*)seekNodeByName(rootNode, "zhangHao");
	//miMa = (cocos2d::ui::TextField*)seekNodeByName(rootNode, "miMa");



	//ÕËºÅÉèÖÃºÐ×Ó
	cocos2d::ui::ImageView* setBox = (cocos2d::ui::ImageView*)seekNodeByName(rootNode, "setBox");
	btnChange = (cocos2d::ui::Button*)seekNodeByName(rootNode,"btnChange");
	btnChange->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType type)
	{
		if (type == cocos2d::ui::Widget::TouchEventType::ENDED)
		{
			GameVoice::getInstance()->playClickBtnVoive();
			loginBg->setVisible(true);
		}
	});
    //setCanTouchOtherLayer(this,false);

	return true;
}

void GameSetting::onHttpRequestCompleted(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)
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
	/*log("Http Test, dump data: ");
	for (unsigned int i = 0; i < buffer->size(); i++)
	{
	log("%c", (*buffer)[i]);
	}
	log("\n");
	if (response->getHttpRequest()->getReferenceCount() != 2)
	{
	log("request ref count not 2, is %d", response->getHttpRequest()->getReferenceCount());
	}*/

	std::string responseStr = std::string(buffer->begin(), buffer->end());
	CCLOG("%s", responseStr.c_str());
}

void GameSetting::clickBtnToLogin()
{
    
    
    
	// test 2: set Content-Type
	{
		HttpRequest* request = new (std::nothrow) HttpRequest();
		request->setUrl("47.93.50.101:8080/QQWar/Qqwar/validateUserLogin");
		request->setRequestType(HttpRequest::Type::POST);
		std::vector<std::string> headers;
		headers.push_back("Content-Type: application/json; charset=utf-8");
		request->setHeaders(headers);
		request->setResponseCallback(CC_CALLBACK_2(GameSetting::onHttpRequestCompleted, this));

		std::string zhanghaoStr = zhangHao->getString();
		std::string mimaStr = miMa->getString();
		//log("%s,====%s", zhanghaoStr.c_str(), mimaStr.c_str());
		// write the post data
		std::string shuju = "account=" + zhanghaoStr + "z&password=" + mimaStr;
		const char* postData = shuju.c_str();
		log("%s", postData);
		request->setRequestData(postData, strlen(postData));
		/*if (isImmediate)
		{
			request->setTag("POST immediate test2");
			HttpClient::getInstance()->sendImmediate(request);
		}
		else*/
		{
			request->setTag("POST test2");
			HttpClient::getInstance()->send(request);
		}
		request->release();
	}
}
