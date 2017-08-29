/*!
 * \class SimpleTools
 *
 * TODO: 工具类
 *
 * \note
 *
 * \author 张锋露
 *
 * \version 1.0
 *
 * \date 八月 2017
 *
 * Contact: 373510848@qq.com
 *
 */

#ifndef __SIMPLE_TOOLS_H__
#define __SIMPLE_TOOLS_H__
#include <iostream>
#include "cocos2d.h"
#include "network/HttpClient.h"

using namespace std;
USING_NS_CC;
Node * seekNodeByName(Node * root,const std::string & name);

void requestFroGet(std::string url, std::function<void(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)> func, const char * tag);

void requestForPost(std::string url, const char* buffer, std::function<void(cocos2d::network::HttpClient *sender, cocos2d::network::HttpResponse *response)> func, const char * tag);
std::string getDataFromResponse(cocos2d::network::HttpResponse * response);

string & replace_all_distinct(string & str, const string & old_value = "null", const string & new_value = "\"\"");



void setCanTouchOtherLayer(Node* node, bool isTouch);


#endif
