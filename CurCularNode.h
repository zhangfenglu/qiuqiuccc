//
//  FoodSprite.h
//  qiuFight
//
//  Created by ÁõÈ¨Íþ on 16/3/2.
//
//

#ifndef _CirCularNode_
#define _CirCularNode_

#include "cocos2d.h"
//#include "extensions/cocos-ext.h"
USING_NS_CC;

class CirCularNode : public ClippingNode
{
public:
    CirCularNode();
    virtual ~CirCularNode();
    static CirCularNode* create(float radius);
    static CirCularNode* create(float radius,Node* pNode);
    virtual bool init(float radius);
    
    CC_PROPERTY(Node*,m_clipNode,ClipNode);
};

#endif /* PlayerSprite_h */
