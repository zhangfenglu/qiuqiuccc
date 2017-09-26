#pragma once
#include <iostream>
#include "network/HttpClient.h"
#include "cocos2d.h"
using namespace std;
using namespace cocos2d::network;

// Parameter: bool isSucceed			�Ƿ�ɹ�
// Parameter: std::vector<char>* buffer	������
// Parameter: string tag				����
typedef std::function<void(bool isSucceed, std::vector<char>* buffer, string tag) > sunHttpRequestCallback;

// ip
const char ip[] = "http://47.93.50.101:8080";
// �����Ϣ
const char playerInfoMsg[] = "%s/QQWar/melee/info?id=%s";
// ʥ����Ϣ
const char groupMsg[] = "%s/QQWar/melee/gomelee?playerId=%s&type=%d";
// ������Ϣ
const char applyMsg[] = "%s/QQWar/melee/enroll";
const char applyInfoMsg[] = "id=%s&aid=%d&type=%s";
// ��������
const string applyTypeStr[] = { "goldcoins", "diamonds", "likenumber" };

// �һ���
const char exchangeMsg[] = "%s/QQWar/cdkey/convert?id=%s&keynum=%s";

class SunNetPublic
{
public:
	virtual ~SunNetPublic();

	//************************************
	// Method:    getInstance			����
	// FullName:  SunNetPublic::getInstance
	// Access:    public static 
	// Returns:   SunNetPublic*
	// Qualifier:
	//************************************
	static SunNetPublic* getInstance();

	//************************************
	// Method:    sendUrl				����httpЭ��
	// FullName:  SunNetPublic::sendUrl
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: string url			��ַ
	// Parameter: string tag			����
	// Parameter: sunHttpRequestCallback callback	�ص��¼�
	//************************************
	void sendUrl(string url, string tag, sunHttpRequestCallback callback);

	//************************************
	// Method:    sendUrlData			����httpЭ�� �Ӳ���
	// FullName:  SunNetPublic::sendUrlData
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: string url			��ַ
	// Parameter: string data			����
	// Parameter: string tag			tag
	// Parameter: sunHttpRequestCallback callback	�ص��¼�
	//************************************
	void sendUrlData(string url, string data, string tag, sunHttpRequestCallback callback);

	//************************************
	// Method:    addApplyLayer			��ӱ�������
	// FullName:  SunNetPublic::addApplyLayer
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: cocos2d::Node * node	���ڵ�
	//************************************
	void addApplyLayer(cocos2d::Node* node);

	//************************************
	// Method:    showTips				��ʾ��ʾ����
	// FullName:  SunNetPublic::showTips
	// Access:    public 
	// Returns:   cocos2d::Node*
	// Qualifier:
	// Parameter: std::string str
	//************************************
	cocos2d::Node* showTips(std::string str);

	//************************************
	// Method:    addExchangeLayer		��Ӷһ�����
	// FullName:  SunNetPublic::addExchangeLayer
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: cocos2d::Node * node	���ڵ�
	//************************************
	void addExchangeLayer(cocos2d::Node* node);

	cocos2d::Node* _labTips;			// ��ʾ��
	string playerId;					// ���id
private:
	SunNetPublic();
};

