#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "network/HttpClient.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;

struct SunTime {
	int year;		// ��
	int month;		// ��
	int day;		// ��
	int week;		// ����
	int hour;		// Сʱ
	int minute;		// ��
	int second;		// ��
};

// �������
struct PlayerData
{
	std::string playerId;	// ���id
	std::string timeStr;	// ʱ��
	int monthcard;			// �¿��ȼ�
	int yearcard;			// �꿨�ȼ�
	int diamonds;			// ��ʯ
	int goldcoins;			// ���
	int likenumber;			// ϲ��ֵ
	int week;				// ����
	int grade;				// �ȼ�
	SunTime time;			// ʱ��
};

class ApplyScene : public cocos2d::Layer
{
public:
    virtual bool init();

    // implement the "static create()" method manually
    CREATE_FUNC(ApplyScene);

	//************************************
	// Method:    applyReturn		����������
	// FullName:  ApplyScene::applyReturn
	// Access:    public 
	// Returns:   void
	// Qualifier:
	// Parameter: std::string data	��������
	//************************************
	void applyReturn(std::string data);
private:
	// msg
	//************************************
	// Method:    _initPlayerInfoMsg	����û�����
	// FullName:  HelloWorld::_initPlayerInfoMsg
	// Access:    private 
	// Returns:   void
	// Qualifier:
	// Parameter: std::string data		��������
	//************************************
	void _initPlayerInfoMsg(std::string data);

	//************************************	
	// Method:    _initGroupMsg			��ȡ��Ӧ��ʥ������
	// FullName:  HelloWorld::_initGroupMsg	
	// Access:    private 
	// Returns:   void
	// Qualifier:
	// Parameter: std::string data		��������
	//************************************
	void _initGroupMsg(std::string data);

	//************************************
	// Method:    _checkLeftButton		���ʥ����ť
	// FullName:  HelloWorld::_checkLeftButton
	// Access:    private 
	// Returns:   void
	// Qualifier:
	// Parameter: int tag
	//************************************
	void _checkLeftButton(int tag);
private:

	Node* _mainNode;					// ���ڵ�
	ActionTimeline* _rightMoveAction;	// ����

	Node* _rightNode;					// �ұ߽ڵ�
	Button* _leftCheckBox;				// ��߰�ť
	Button* _rightCheckBox;				// �ұ߰�ť
	ImageView* _leftImage;				// ���ͼƬ
	ImageView* _RightImage;				// �ұ�ͼƬ
	Button* _smallGrail[5];				// Сʥ������
	Button* _bigGrail;					// ��ʥ��

	Text* _textTime;					// ʱ��
	Text* _ruleText;					// ����
	Text* _title;						// ����

	ImageView* _prograssBg[3];			// ����������
	LoadingBar* _bar[3];				// ������

	ImageView* _titleImage;				// ʥ��ͼƬ

	Text* _diamondText;					// ��ʯ����
	Text* _numberText;					// ��������
	ImageView* _icon;					// ����ͼƬ
	Button* _applyBtn;					// ��ʼ��ť
	Text* _applyText;					// ��ʼ��ʾ
	bool _useType;						// ʹ������
	int _useConsumeType;				// ��������

	PlayerData _playerData;				// �������
	ValueMap _stringData;				// ��������

	int _checkIndex;					// ʥ�����
	int _week;							// ʹ��ʥ��������
	int _useGold;						// ʹ�õĽ����
	int _useDiamond;					// ʹ�õ���ʯ��
	int _gouldId;						// �����

	Node* _nodeAction;					// �����ڵ�
private:

	//************************************
	// Method:    _initLeftUI			��ʼ�����ui
	// FullName:  HelloWorld::_initLeftUI
	// Access:    private 
	// Returns:   void
	// Qualifier:
	//************************************
	void _initLeftUI();				
	
	//************************************
	// Method:    _initRightUI			��ʼ���ұ�ui
	// FullName:  HelloWorld::_initRightUI
	// Access:    private 
	// Returns:   void
	// Qualifier:
	//************************************
	void _initRightUI();

	//************************************
	// Method:    _initRightData		��ʼ���ұ�����
	// FullName:  HelloWorld::_initRightData
	// Access:    private 
	// Returns:   void
	// Qualifier:
	// Parameter: bool enroll			�Ƿ����
	// Parameter: int playerNumber		�������
	// Parameter: std::string openTime	����ʱ��
	// Parameter: int week				����
	// Parameter:  SunTime time			ϵͳʱ��
	//************************************
	void _initRightData(bool enroll, int playerNumber, std::string openTime, int week, SunTime time);

	//************************************
	// Method:    _openGrailByState		����ʥ��״̬
	// FullName:  HelloWorld::_openGrailByState
	// Access:    private 
	// Returns:   void
	// Qualifier:
	// Parameter: bool state			true ΪСʥ����false Ϊ��ʥ��
	//************************************
	void _openGrailByState(bool state);

	//************************************
	// Method:    _openAllGrail			��������ʥ��
	// FullName:  HelloWorld::_openAllGrail
	// Access:    private 
	// Returns:   void
	// Qualifier:
	//************************************
	void _openAllGrail();

	//************************************
	// Method:    _changeStrTimeToNumberת���ַ�ʱ��Ϊ����
	// FullName:  ApplyScene::changeStrTimeToNumber
	// Access:    private 
	// Returns:   SunTime
	// Qualifier:
	// Parameter: string timeStr		ʱ���ַ���
	//************************************
	SunTime _changeStrTimeToNumber(std::string timeStr);

	//************************************
	// Method:    _openBtnAction		������ť����
	// FullName:  ApplyScene::_openBtnAction
	// Access:    private 
	// Returns:   Node*					�����ڵ�
	// Qualifier:
	// Parameter: bool state true Ϊ��ť false ΪС��ť
	//************************************
	Node* _openBtnAction(bool state);

};



#endif // __HELLOWORLD_SCENE_H__
