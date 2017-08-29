//
//  FoodSprite.cpp
//  qiuFight
//
//  Created by ÕÅÔ¾¶« on 16/3/2.
//
//

#include "CurCularNode.h"
#include "Common.h"



CirCularNode::CirCularNode()
{
    m_clipNode = NULL;
}
CirCularNode::~CirCularNode()
{
    CC_SAFE_RELEASE_NULL(m_clipNode);
}
CirCularNode* CirCularNode::create(float radius)
{
    auto pClipNode = new CirCularNode();
    if (pClipNode && pClipNode->init(radius)) {
        pClipNode->autorelease();
    }
    else
    {
        delete pClipNode;
        pClipNode = NULL;
    }
    return pClipNode;
}
CirCularNode* CirCularNode::create(float radius,Node* pNode)
{
    auto clipNode = CirCularNode::create(radius);
    if (clipNode) {
        clipNode->setClipNode(pNode);
    }
    
    return clipNode;
}
bool CirCularNode::init(float radius)
{
    if (!ClippingNode::init()) {
        return false;
    }
    
    auto circleNode = DrawNode::create();
    
    const int maxTrangle = 360;
    
    Point circleVec2[maxTrangle];
    
    for (int i = 0; i < maxTrangle; i++) {
        float x = cosf(i*(M_PI/180.0f))*radius;
        float y = sinf(i*(M_PI/180.0f))*radius;
        circleVec2[i] = Vec2(x, y);
    }
    
    auto circleColor = Color4F(0, 1, 0, 1);
    
    circleNode->drawPolygon(circleVec2, maxTrangle, circleColor, 1, circleColor);
    setStencil(circleNode);
    
    return true;
}
void CirCularNode::setClipNode(Node* pNode)
{
    CC_SAFE_RELEASE_NULL(m_clipNode);
    m_clipNode = pNode;
    CC_SAFE_RETAIN(m_clipNode);
    addChild(pNode);
}

Node* CirCularNode::getClipNode()const
{
    return m_clipNode;
}
