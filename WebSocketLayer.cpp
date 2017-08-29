//
//  WebSocketLayer.cpp
//  qiuFight
//
//  Created by 张跃东 on 16/2/29.
//
//

#include "WebSocketLayer.h"
#include "MainScene.h"
#include "GridLayer.h"
#include "SceneLayer.h"
#include "msg_client.pb.h"

//#define IP_ADDRESS "60.174.233.70"
//#define IP_ADDRESS "42.157.5.70"
#define IP_ADDRESS "47.93.50.101"
#define IP_PORT "1448"
#define IP_UI_PORT "8080"

WebSocketLayer::WebSocketLayer()
: _wsiSendBinary(NULL)
, _sendBinaryTimes(0)
{
    _wsiUIBinary = new cocos2d::network::WebSocket();
    
    uiUrl = "ws://";
    uiUrl.append(IP_ADDRESS);
    uiUrl.append(":");
    uiUrl.append(IP_UI_PORT);
    uiUrl.append("/QQWar/websocket");
    
    //log("url is:%s", uiUrl.c_str());
    
    
    if( !_wsiUIBinary->init(*this, uiUrl.c_str()))
    {
        CC_SAFE_DELETE(_wsiUIBinary);
    }
    
}

WebSocketLayer::~WebSocketLayer()
{
    if(_wsiSendBinary)
        _wsiSendBinary->close();
    
    if(_wsiUIBinary)
        _wsiUIBinary->close();
}

bool WebSocketLayer::openWebSocket(const char *ipAddress, const char *port)
{
    _wsiSendBinary = new cocos2d::network::WebSocket();
    
    std::string url = "ws://";
    url.append(ipAddress);
    url.append(":");
    url.append(port);
    url.append("/");
    
    log("url is:%s", url.c_str());
    
    if( !_wsiSendBinary->init(*this, url.c_str()))
    {
        CC_SAFE_DELETE(_wsiSendBinary);
        return false;
    }
    
    return true;
}

bool WebSocketLayer::init()
{
    if(!Layer::init())
        return false;
    
    return true;
}


//Delegate methods
void WebSocketLayer::onOpen(cocos2d::network::WebSocket *ws)
{
    log("Websocket (%p) opened", ws);
    
    if(ws == _wsiSendBinary)
    {
        Global::getInstance()->setConnectState(true);
        log("wsi send binary");
    }
    else if(ws == _wsiUIBinary)
    {
        log("wsi ui send binary");
    }
}

void WebSocketLayer::onMessage(cocos2d::network::WebSocket *ws, const cocos2d::network::WebSocket::Data &data)
{
    if(ws == _wsiSendBinary)
    {
        uint8_t msg_head = (uint32_t)data.bytes[0];
        switch (msg_head) {
            case 16:  //更新变化的节点
            {
                CCScene* pScene = dynamic_cast<CCScene*>(getParent());
                MainScene* layer = dynamic_cast<MainScene*>(pScene->getChildByTag(0));
                layer->updateNodes(data);
            }
                break;
                
            case 64:    // 通知棋盘大小
            {
                CCScene* pScene = dynamic_cast<CCScene*>(getParent());
                MainScene* layer = dynamic_cast<MainScene*>(pScene->getChildByTag(0));
                layer->setWinSize(data);
            }
                break;
                
            case 32:    // 添加自己
            {
                CCScene* pScene = dynamic_cast<CCScene*>(getParent());
                MainScene* layer = dynamic_cast<MainScene*>(pScene->getChildByTag(0));
                layer->addSelfNode(data);
            }
                break;
                
            case 17:    // 战斗排名
            {
                CCScene* pScene = dynamic_cast<CCScene*>(getParent());
                MainScene* layer = dynamic_cast<MainScene*>(pScene->getChildByTag(0));
                layer->updateRankeInFight(data);
            }
                break;
                
            case 18:    // 战斗结算
            {
                CCScene* pScene = dynamic_cast<CCScene*>(getParent());
                MainScene* layer = dynamic_cast<MainScene*>(pScene->getChildByTag(0));
                layer->GameOverState(data);
            }
                break;
                
            case 33:
            {
                CCScene* pScene = dynamic_cast<CCScene*>(getParent());
                MainScene* layer = dynamic_cast<MainScene*>(pScene->getChildByTag(0));
                layer->UpdateFightLife(data);
            }
                break;
                
            case 34:
            {
                CCScene* pScene = dynamic_cast<CCScene*>(getParent());
                MainScene* layer = dynamic_cast<MainScene*>(pScene->getChildByTag(0));
                layer->SetDeath(data);
            }
                
            default:
                break;
        }
    }
    else if(ws == _wsiUIBinary)
    {
        uint16_t header;
        memcpy(&header, data.bytes , sizeof(uint16_t));
        //log("header si::%d", header);
        IDUM_CLI head = (IDUM_CLI)header;
        switch (head) {
            case IDUM_CLIB:
            {
                log("开始");
            }
                break;
                
            case IDUM_Response:
            {
                CCScene* pScene = dynamic_cast<CCScene*>(getParent());
                MainScene* layer = dynamic_cast<MainScene*>(pScene->getChildByTag(0));
                layer->respErrors(data);
            }
                break;
                
            case IDUM_Logout:
            {
                
            }
                break;
                
            case IDUM_EnterGame:
            {
                CCScene* pScene = dynamic_cast<CCScene*>(getParent());
                MainScene* layer = dynamic_cast<MainScene*>(pScene->getChildByTag(0));
                layer->setPlayerInfo(data);
            }
                break;
                
            case IDUM_SyncRole:
            {
                CCScene* pScene = dynamic_cast<CCScene*>(getParent());
                MainScene* layer = dynamic_cast<MainScene*>(pScene->getChildByTag(0));
                layer->respSyncRole(data);
            }
                break;
                
            case IDUM_ItemUpdate:
            {
                CCScene* pScene = dynamic_cast<CCScene*>(getParent());
                MainScene* layer = dynamic_cast<MainScene*>(pScene->getChildByTag(0));
                layer->respItemUpdate(data);
            }
                break;
                
            case IDUM_Shop:
            {
                CCScene* pScene = dynamic_cast<CCScene*>(getParent());
                MainScene* layer = dynamic_cast<MainScene*>(pScene->getChildByTag(0));
                layer->respShopList(data);
            }
                break;
                
            case IDUM_Hero:
            {
                CCScene* pScene = dynamic_cast<CCScene*>(getParent());
                MainScene* layer = dynamic_cast<MainScene*>(pScene->getChildByTag(0));
                layer->respHeroUp(data);
            }
                break;
                
            case IDUM_EquipUpdate:
            {
                CCScene* pScene = dynamic_cast<CCScene*>(getParent());
                MainScene* layer = dynamic_cast<MainScene*>(pScene->getChildByTag(0));
                layer->respEquipUpdate(data);
            }
                break;
                
            case IDUM_ServerList:
            {
                CCScene* pScene = dynamic_cast<CCScene*>(getParent());
                MainScene* layer = dynamic_cast<MainScene*>(pScene->getChildByTag(0));
                layer->respServerList(data);
            }
                break;
                
            case IDUM_LoginFightKey:
            {
                CCScene* pScene = dynamic_cast<CCScene*>(getParent());
                MainScene* layer = dynamic_cast<MainScene*>(pScene->getChildByTag(0));
                layer->respServerKey(data);
            }
                break;
                
            case IDUM_RoleInfo:
            {
                CCScene* pScene = dynamic_cast<CCScene*>(getParent());
                MainScene* layer = dynamic_cast<MainScene*>(pScene->getChildByTag(0));
                layer->respRoleInfo(data);
            }
                break;
                
            case IDUM_Fans:
            {
                CCScene* pScene = dynamic_cast<CCScene*>(getParent());
                MainScene* layer = dynamic_cast<MainScene*>(pScene->getChildByTag(0));
                layer->respFans(data);
            }
                break;
                
            case IDUM_Ranks:
            {
                CCScene* pScene = dynamic_cast<CCScene*>(getParent());
                MainScene* layer = dynamic_cast<MainScene*>(pScene->getChildByTag(0));
                layer->respRanks(data);
            }
                break;
                
            case IDUM_FightLikes:
            {
                CCScene* pScene = dynamic_cast<CCScene*>(getParent());
                MainScene* layer = dynamic_cast<MainScene*>(pScene->getChildByTag(0));
                layer->respFightLikes(data);
            }
                break;
                
            case IDUM_TopMsg:
            {
                CCScene* pScene = dynamic_cast<CCScene*>(getParent());
                MainScene* layer = dynamic_cast<MainScene*>(pScene->getChildByTag(0));
                layer->respHotMsg(data);
            }
                break;
                
            case IDUM_MsgList:
            {
                CCScene* pScene = dynamic_cast<CCScene*>(getParent());
                MainScene* layer = dynamic_cast<MainScene*>(pScene->getChildByTag(0));
                layer->respMsgList(data);
            }
                break;
                
            case IDUM_Friends:
            {
                CCScene* pScene = dynamic_cast<CCScene*>(getParent());
                MainScene* layer = dynamic_cast<MainScene*>(pScene->getChildByTag(0));
                layer->respFriendList(data);
            }
                break;
                
            case IDUM_AddFriend:
            {
                CCScene* pScene = dynamic_cast<CCScene*>(getParent());
                MainScene* layer = dynamic_cast<MainScene*>(pScene->getChildByTag(0));
                layer->respAddFriend(data);
            }
                break;
                
            case IDUM_AddInvite:
            {
                CCScene* pScene = dynamic_cast<CCScene*>(getParent());
                MainScene* layer = dynamic_cast<MainScene*>(pScene->getChildByTag(0));
                layer->respAddInvite(data);
            }
                break;
                
            case IDUM_DelInvite:
            {
                CCScene* pScene = dynamic_cast<CCScene*>(getParent());
                MainScene* layer = dynamic_cast<MainScene*>(pScene->getChildByTag(0));
                layer->respDelInvite(data);
            }
                break;
                
            case IDUM_SeasonRank:
            {
                CCScene* pScene = dynamic_cast<CCScene*>(getParent());
                MainScene* layer = dynamic_cast<MainScene*>(pScene->getChildByTag(0));
                layer->respSeasonRank(data);
            }
                break;
                
            case IDUM_GameRecord:
            {
                CCScene* pScene = dynamic_cast<CCScene*>(getParent());
                MainScene* layer = dynamic_cast<MainScene*>(pScene->getChildByTag(0));
                layer->respGameRecord(data);
            }
                break;
                
            case IDUM_Photos:
            {
                CCScene* pScene = dynamic_cast<CCScene*>(getParent());
                MainScene* layer = dynamic_cast<MainScene*>(pScene->getChildByTag(0));
                layer->respPhotos(data);
            }
                break;
                
            case IDUM_Icons:
            {
                CCScene* pScene = dynamic_cast<CCScene*>(getParent());
                MainScene* layer = dynamic_cast<MainScene*>(pScene->getChildByTag(0));
                layer->respIcons(data);
            }
                break;
                
            case IDUM_AwardList:
            {
                CCScene* pScene = dynamic_cast<CCScene*>(getParent());
                MainScene* layer = dynamic_cast<MainScene*>(pScene->getChildByTag(0));
                layer->respAwardList(data);
            }
                break;
                
            case IDUM_CLIE:
            {
                
            }
                break;
            default:
                break;
        }
    }
}

void WebSocketLayer::onClose(cocos2d::network::WebSocket *ws)
{
    log("websocket instance (%p) closed.", ws );
    if(ws == _wsiSendBinary)
    {
        _wsiSendBinary = NULL;
        Global::getInstance()->setConnectState(false);
        
        CC_SAFE_DELETE(ws);
    }
    else if(ws == _wsiUIBinary)
    {
        _wsiUIBinary = NULL;
        
        CC_SAFE_DELETE(ws);
        
        _wsiUIBinary = new cocos2d::network::WebSocket();
        
        if( !_wsiUIBinary->init(*this, uiUrl.c_str()))
        {
            CC_SAFE_DELETE(_wsiUIBinary);
        }
        
        CCScene* pScene = dynamic_cast<CCScene*>(getParent());
        if(pScene)
        {
            MainScene* layer = dynamic_cast<MainScene*>(pScene->getChildByTag(0));
            layer->reqReLogin();
        }
    }
}

void WebSocketLayer::onError(cocos2d::network::WebSocket *ws, const cocos2d::network::WebSocket::ErrorCode &error)
{
    log("Error was fired, error code: %d", error);
    if(ws == _wsiSendBinary)
    {
        Global::getInstance()->setConnectState(false);
        log("Error was wsi send binary");
    }
    else if(ws == _wsiUIBinary)
    {
        log("Error was wsi ui");
    }
}

void WebSocketLayer::onSendMsg(const char* buf, int nLen)
{
    if(_wsiSendBinary != NULL &&_wsiSendBinary->getReadyState() == cocos2d::network::WebSocket::State::OPEN)
    {
        _wsiSendBinary->send((unsigned char*)buf, nLen);
    }
}

void WebSocketLayer::closeNet()
{
    if(_wsiSendBinary != NULL &&_wsiSendBinary->getReadyState() == cocos2d::network::WebSocket::State::OPEN)
    {
        _wsiSendBinary->close();
        CC_SAFE_DELETE(_wsiSendBinary);
        _wsiSendBinary = NULL;
        Global::getInstance()->setConnectState(false);
    }
}

void WebSocketLayer::onSendUIMsg(const char *buf, int nLen)
{
    if(_wsiUIBinary != NULL && _wsiUIBinary->getReadyState() == cocos2d::network::WebSocket::State::OPEN)
    {
        _wsiUIBinary->send((unsigned char*)buf, nLen);
    }
}

