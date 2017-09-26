#ifndef __DIAMONDINFO_H__
#define __DIAMONDINFO_H__
#include "cocos2d.h"
#include "Common.h"

class Config : cocos2d::Ref
{
public:
	Config();
	~Config();
	static 	Config* getInstance();

	//std::vector<DiamondInfo>& getDiamondInfo(){ return s_vDiamondInfo; }
	//std::vector<GoodsInfo>& getGoodsInfo(){ return s_vGoodsInfo; }
	//std::vector<ItemInfo>& getItemsInfo(){ return s_vItemInfo; }

	bool init();
	bool initGoodsInfo();
	bool initDiamondInfo();
	bool initOtherInfo();

	ValueMap s_vGoodsInfo;
	ValueMap s_vDiamondInfo;
	ValueMap s_vItemInfo;
	static Config* s_pConfig;
};

#endif 