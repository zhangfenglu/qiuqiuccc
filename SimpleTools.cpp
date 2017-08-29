#include "SimpleTools.h"
//#include "DictionaryManager.h"
#include "cocos2d.h"
#include "ui/CocosGUI.h"
//#include "GlobalMacros.h"
USING_NS_CC;
using namespace ui;
Node * seekNodeByName(Node * root, const std::string & name)
{
	if (!root)
	{
		return nullptr;
	}
	if (root->getName() == name)
	{
		return root;
	}
	const auto& arrayRootChildren = root->getChildren();
	for (auto& subWidget : arrayRootChildren)
	{
		Node* child = dynamic_cast<Node*>(subWidget);
		if (child)
		{
			Node* res = seekNodeByName(child, name);
			if (res != nullptr)
			{
				return res;
			}
		}
	}
	return nullptr;
}

void requestFroGet(std::string url, std::function<void(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)> func, const char * tag)
{
	cocos2d::network::HttpRequest * request = new cocos2d::network::HttpRequest();
	request->setRequestType(cocos2d::network::HttpRequest::Type::GET);// set request type
	request->setResponseCallback(func);
	request->setTag(tag);
	request->setUrl(url.c_str());
	cocos2d::network::HttpClient::getInstance()->send(request);
	request->release();
}

void requestForPost(std::string url, const char* buffer, std::function<void(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)> func, const char * tag)
{
	cocos2d::network::HttpRequest * request = new cocos2d::network::HttpRequest();
	request->setRequestType(cocos2d::network::HttpRequest::Type::POST);// set request type
	request->setResponseCallback(func);
	request->setTag(tag);
	request->setUrl(url.c_str());
	request->setRequestData(buffer, strlen(buffer));
	cocos2d::network::HttpClient::getInstance()->send(request);
	request->release();
}

std::string getDataFromResponse(cocos2d::network::HttpResponse * response)
{
	std::vector<char> * v_data = response->getResponseData();
	std::string s_data;
	for (unsigned int i = 0; i < v_data->size(); i++)
	{
		s_data += (*v_data)[i];
	}

	auto index = s_data.find("{\"status\":");
	if (index != string::npos) s_data = &s_data[index];

	return s_data;
}

string & replace_all_distinct(string& str, const string& old_value, const string& new_value)
{
	for (string::size_type pos(0); pos != string::npos; pos += new_value.length())
	{
		if ((pos = str.find(old_value, pos)) != string::npos)
			str.replace(pos, old_value.length(), new_value);
		else break;
	}
	return   str;
}


void setCanTouchOtherLayer(Node* node, bool isTouch)
{
	auto callback = [](Touch *, Event *)
	{
		return true;
	};
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = callback;
	listener->setSwallowTouches(!isTouch);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, node);
}

void setCanTouchOtherLayer(Node* node, bool isTouch, std::function<bool(Touch * touch, Event * event)> func)
{
	auto listener = EventListenerTouchOneByOne::create();
	listener->onTouchBegan = func;
	listener->setSwallowTouches(!isTouch);
	Director::getInstance()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, node);
}

