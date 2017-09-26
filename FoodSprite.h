//
//  FoodSprite.h
//  qiuFight
//
//  Created by ÕÅÔ¾¶« on 16/3/2.
//
//

#ifndef FoodSprite_h
#define FoodSprite_h

#include "cocos2d.h"
USING_NS_CC;

class FoodSprite : public Node
{
public:
    FoodSprite();
    ~FoodSprite();
    CREATE_FUNC(FoodSprite);
    virtual bool init();
    void createWithRGB(uint16_t index, bool isFood,int baozi,std::string icon,std::string name);
    
    void setUpdateInfo(uint32_t nodeId, Point oldPos, Point destPos);
    virtual void update(float ft);
    
    void setImageHead(bool flag);
    bool getImageHead();
    
    int getImageIndex();
    void setImageIndex(int index, bool isFood);
    
    void addPlayerImage(int hero,int guanghuan,int baozi,int canying,std::string icon);
    void removePlayerImage();
    
    void setName(const char* name);
    void setWaiguan(int hero,int guanghuan,int baozi,int canying)
    {
        heroID = hero;
        mGuanghuan = guanghuan;
        mBaozi = baozi;
        mCanying = canying;
    }

	bool isFood()
	{
		return m_isFood;
	}

	virtual void setScale(float scale) override;

	void updateNameSize();
private:
    uint32_t m_spriteID;
    Point m_destPos;
    Point m_oldPos;
    Point m_diff;
    int     m_times;
    
    
    int     m_imageIndex;
    
    
    
    int heroID;
    int mGuanghuan;
    int mCanying;
    int mBaozi;
	bool    m_isFood;
	bool    m_isImageHead;
};

#endif /* FoodSprite_h */
