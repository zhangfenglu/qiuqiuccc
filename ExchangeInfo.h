//
//  ExchangeInfo.h
//  qiuFight
//
//  Created by ÕÅÔ¾¶« on 16/5/18.
//
//

#ifndef ExchangeInfo_h
#define ExchangeInfo_h

#include "cocos2d.h"
#include "MainScene.h"

USING_NS_CC;


class ExchangeInfo : public CCObject
{
public:
    static std::string getIdentifier();
    //static CIImage* createQRForString(const char* str);
    //static UIImage* createNonInterpolatedUIImageFormCIImage(CIImage* image,CGFloat size);
    //static UIImage* imageBlackToTransparent(UIImage* image, CGFloat red ,CGFloat green, CGFloat blue);
    
    static void CreateQRFImage(const char* str,const char* headIcon,float mSize);
    static std::map<int,std::string> getProvinces();
    static int getLocationProvince();
    static void OpenScan();
    static void SaomaAddFriend(const char* str);
    static void AddPhoto(int idex);
    static void UpLoadPhoto(const char* str, int index);
    static cocos2d::CCTexture2D * GetTextureForData(const char* data);
    
    static void UpLoadIcon(int index);
    
    static bool regexStr(const char* str,const char* dec);
    static void SaveImag(const char* imgdata,const char* destpath);
};

#endif /* ExchangeInfo_h */
