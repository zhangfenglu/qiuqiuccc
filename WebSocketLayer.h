//
//  WebSocketLayer.h
//  qiuFight
//
//  Created by ÕÅÔ¾¶« on 16/2/29.
//
//

#ifndef WebSocketLayer_h
#define WebSocketLayer_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "network/WebSocket.h"

USING_NS_CC;
USING_NS_CC_EXT;

class WebSocketLayer : public Layer, public cocos2d::network::WebSocket::Delegate
{
public:
    WebSocketLayer();
    virtual ~WebSocketLayer();
    
    virtual bool init();
    CREATE_FUNC(WebSocketLayer);
    
    virtual void onOpen(cocos2d::network::WebSocket* ws);
    virtual void onMessage(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::Data& data);
    virtual void onClose(cocos2d::network::WebSocket* ws);
    virtual void onError(cocos2d::network::WebSocket* ws, const cocos2d::network::WebSocket::ErrorCode&error);
    
    //Menu Callbacks
    void onSendMsg(const char* buf, int nLen);
    void onSendUIMsg(const char* buf, int nLen);
    
    bool openWebSocket(const char* ipAddress, const char* port);
    
    void closeNet();
    
private:
    cocos2d::network::WebSocket* _wsiSendBinary;
    
    cocos2d::network::WebSocket* _wsiUIBinary;
    
    int _sendBinaryTimes;
    std::string  uiUrl;
    
};



#endif /* WebSocketLayer_h */
