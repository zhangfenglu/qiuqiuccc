#ifndef RotateMenu_h__
#define RotateMenu_h__

#include "cocos2d.h"  
/*
*ģ���Ҷ��������������ת�˵�
*/
class RotateMenu :public cocos2d::Layer{
public:
	//���췽��  
	CREATE_FUNC(RotateMenu);
	//��Ӳ˵���  
	void addMenuItem(cocos2d::MenuItem *item);
	//����λ��  
	void updatePosition();
	//����λ�ã��ж���  
	void updatePositionWithAnimation();
	//λ�ý���  �޸ĽǶ� forwardΪ�ƶ�����  ������1/3����1  
	//true Ϊ����  false ��  
	void rectify(bool forward);
	//��ʼ��  
	virtual bool init();
	//����  ��������ת�Ƕ���Ϊ0  
	void reset();
private:
	//���ýǶ� ����  
	void setAngle(float angle);
	float getAngle();
	//���õ�λ�Ƕ� ����  
	void setUnitAngle(float angle);
	float getUnitAngle();
	//��������ת���Ƕ�,ת������Ϊ  �ƶ����Menu.width����_unitAngle  
	float disToAngle(float dis);
	//���ر�ѡ�е�item  
	cocos2d::MenuItem * getCurrentItem();
private:
	bool zheng;
	//�˵��Ѿ���ת�Ƕ� ����  
	float _angle;
	//�˵����,_children˳���仯���½����鱣��˳��  
	cocos2d::Vector<cocos2d::MenuItem *> _items;
	//��λ�Ƕ� ����  
	float _unitAngle;
	//��������  
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* event);
	virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* event);
	//���������ú���  
	void actionEndCallBack(float dx);
	//��ǰ��ѡ���item  
	cocos2d::MenuItem *_selectedItem;
	//��������ʱ��  
	float animationDuration = 0.3f;
};
#endif // RotateMenu_h__
