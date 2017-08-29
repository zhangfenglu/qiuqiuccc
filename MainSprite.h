//
//  MainSprite.h
//  qiuFight
//
//  Created by ÕÅÔ¾¶« on 16/2/29.
//
//

#ifndef MainSprite_h
#define MainSprite_h

#include "cocos2d.h"
USING_NS_CC;

class MainSprite : public Node //public Sprite
{
public:
    MainSprite();
	void  reset();
    ~MainSprite();
    CREATE_FUNC(MainSprite);
    virtual bool init();
    //static MainSprite* createWithIDX();
    
    void setOriginPos(Point pos);
    void setSize(Size size);
    void updatePos(Point pos);
    
    void updateMainPos();
    void setPlayerUpdate(uint32_t nodeId, Point destPos);
    
    void addPlayerImage(int hero,int guanghuan,int baozi,int canying);
    void removePlayerImage();
    
    void setUpdateInfo(uint32_t nodeId, Point oldPos, Point destPos);
    virtual void update(float ft);
    void resetState();
    
    void setIamgeHead(bool flag);
    bool getIamgeHead();
    
    void setName(std::string name);
    
    void setSpSize(float size);
    float getSpSize();
    void setWaiguan(int hero,int guanghuan,int baozi,int canying)
    {
        heroID = hero;
        mGuanghuan = guanghuan;
        mBaozi = baozi;
        mCanying = canying;
    }
	
	virtual void setScale(float scale) override;

	void updateNameSize();
private:
    uint32_t m_sprID;
    Point  m_destPos;
    Point  m_diff;
    Point  m_oldPos;
	float   m_sp_scale;
    int     m_times;
    int heroID;
    int mGuanghuan;
    int mCanying;
    int mBaozi;
	bool   m_isImageHead;
};

#endif /* MainSprite_h */
