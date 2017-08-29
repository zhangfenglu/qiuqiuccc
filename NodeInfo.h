//
//  NodeInfo.h
//  qiuFight
//
//  Created by ÕÅÔ¾¶« on 16/3/2.
//
//

#ifndef NodeInfo_h
#define NodeInfo_h

#include "cocos2d.h"
#include "cocos-ext.h"
#include "Global.h"

USING_NS_CC;
USING_NS_CC_EXT;
class CNodeInfo
{
public:
    CNodeInfo(){}
    ~CNodeInfo(){}
    
    size_t GetNodeInfoSize();
    void SetNodeInfo(nodeInfo nodeInfo);
    nodeInfo GetNodeInfo();
    void SetID(uint32_t id);
    uint32_t GetID();
    
private:
    nodeInfo m_nodeInfo;
    uint32_t m_node_id;
    
};

#endif /* NodeInfo_h */
