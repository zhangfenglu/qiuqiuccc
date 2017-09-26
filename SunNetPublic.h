#pragma once
#include <iostream>
#include "network/HttpClient.h"
#include "cocos2d.h"
using namespace std;
using namespace cocos2d::network;

// Parameter: bool isSucceed			是否成功
// Parameter: std::vector<char>* buffer	数据流
// Parameter: string tag				别名
typedef std::function<void(bool isSucceed, std::vector<char>* buffer, string tag) > sunHttpRequestCallback;

// ip
const char ip[] = "http://47.93.50.101:8080";
// 玩家信息
const char playerInfoMsg[] = "%s/QQWar/melee/info?id=%s";
// 圣杯信息
const char groupMsg[] = "%s/QQWar/melee/gomelee?playerId=%s&type=%d";
// 报名信息
const char applyMsg[] = "%s/QQWar/melee/enroll";
const char applyInfoMsg[] = "id=%s&aid=%d&type=%s";
// 报名类型
const string applyTypeStr[] = { "goldcoins", "diamonds", "likenumber" };

// 兑换码
const char exchangeMsg[] = "%s/QQWar/cdkey/convert?id=%s&keynum=%s";

class SunNetPublic
{
public:
	virtual ~SunNetPublic();

	//************************************
	// Method:    getInstance			单例
	// FullName:  SunNetPublic::getInstance
	// Access:    public static 
	// Returns:   SunNetPublic*
	// Qualifier:
	//************************************
	static SunNetPublic* getInstance();

	//************************************
	// Method:    sendUrl				发送http协议
	// FullName:  SunNetPublic::sendUrl
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: string url			地址
	// Parameter: string tag			别名
	// Parameter: sunHttpRequestCallback callback	回调事件
	//************************************
	void sendUrl(string url, string tag, sunHttpRequestCallback callback);

	//************************************
	// Method:    sendUrlData			发送http协议 加参数
	// FullName:  SunNetPublic::sendUrlData
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: string url			地址
	// Parameter: string data			参数
	// Parameter: string tag			tag
	// Parameter: sunHttpRequestCallback callback	回调事件
	//************************************
	void sendUrlData(string url, string data, string tag, sunHttpRequestCallback callback);

	//************************************
	// Method:    addApplyLayer			添加报名界面
	// FullName:  SunNetPublic::addApplyLayer
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: cocos2d::Node * node	父节点
	//************************************
	void addApplyLayer(cocos2d::Node* node);

	//************************************
	// Method:    showTips				显示提示文字
	// FullName:  SunNetPublic::showTips
	// Access:    public 
	// Returns:   cocos2d::Node*
	// Qualifier:
	// Parameter: std::string str
	//************************************
	cocos2d::Node* showTips(std::string str);

	//************************************
	// Method:    addExchangeLayer		添加兑换界面
	// FullName:  SunNetPublic::addExchangeLayer
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: cocos2d::Node * node	主节点
	//************************************
	void addExchangeLayer(cocos2d::Node* node);

	cocos2d::Node* _labTips;			// 提示框
	string playerId;					// 玩家id
private:
	SunNetPublic();
};

