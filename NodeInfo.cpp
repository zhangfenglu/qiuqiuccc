//
//  NodeInfo.cpp
//  qiuFight
//
//  Created by ÕÅÔ¾¶« on 16/3/2.
//
//

#include "NodeInfo.h"

size_t CNodeInfo::GetNodeInfoSize()
{
    size_t size = sizeof(nodeInfo);
    return size;
}

void CNodeInfo::SetNodeInfo(nodeInfo nodeInfo)
{
    m_nodeInfo = nodeInfo;
}

void CNodeInfo::SetID(uint32_t id)
{
    m_node_id = id;
}

nodeInfo CNodeInfo::GetNodeInfo()
{
    return m_nodeInfo;
}

uint32_t CNodeInfo::GetID()
{
    return m_node_id;
}

