//
//  msgStru.h
//  qiuFight
//
//  Created by ��Ծ�� on 16/2/29.
//
//

#ifndef msgStru_h
#define msgStru_h

#pragma pack(1)

#define MSG_HEAD \
    uint8_t msgid;

// ----- request

// 255 ��������
struct EnterBoard {
    MSG_HEAD;
    uint32_t protocol;      // �����ֶΣ���ǰΪ0
    uint8_t index;          // ������index
    uint32_t roleID;        // ��ɫid
    uint32_t key;           // ������key
	uint32_t roomId;           // ����
    uint8_t name_len;       // ���ֳ���
    char name[];             // �����ֽ�
};

// 21 �³�������������
struct EjectMass {
    MSG_HEAD;
};

// 17 ���� ��������
struct SplitCell
{
    MSG_HEAD;
};

// 16 �ƶ���Ŀ��
struct sMoveTo{
    MSG_HEAD;
    int32_t target_x;
    int32_t target_y;
    
    int32_t dir_x;
    int32_t dir_y;
};

// 22 ���󸴻�
struct ReqRebirth
{
    MSG_HEAD;
};

// response

// 64 ֪ͨ���̴�С
struct SetBorder
{
    MSG_HEAD;
    int32_t left;
    int32_t top;
    int32_t right;
    int32_t bottom;
};

// 32 ����Լ����Ƶ�ϸ������������
struct AddNode
{
    MSG_HEAD;
    uint32_t nodeid;
};

// 16 ���±仯�Ľڵ㣨ɾ���ġ����ɼ������������������ƶ���
struct UpdateNodes
{
    MSG_HEAD;
    uint16_t destroy_count;
    struct{
        uint32_t killerid;
        uint32_t nodeid;
    } vector;
    
    uint16_t unvisible_count;
    struct
    {
        uint32_t nodeid;
    } vector1;
    
    uint16_t visible_count;
    struct
    {
        uint32_t nodeid;
        int32_t posx;
        int32_t posy;
        int16_t size;
        uint16_t indx;  //��ӦͼƬ��index
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t spike; //��
        uint16_t mass;  // ����
        uint8_t name_len; // ���ֳ���
        char name[]; // ��Ч����
    } vector2;
    
};

// 17 ս����������
struct UpdateRank
{
    uint16_t rank_count;
    struct
    {
        uint32_t roleid;
        uint8_t name_len;
        char name[];
    } vector;
};

// 18 ս�����㣨���һ��Ԫ��Ϊ�Լ���
struct GameOver
{
    uint16_t over_count;
    struct
    {
        uint32_t rank; // ����
        uint32_t roleid;
        uint8_t sex;
        uint32_t province;
        uint32_t city;
        uint32_t mass;
        uint32_t eat;
        uint32_t copper;
        uint32_t exp;
        uint8_t name_len;
        char name[];
    } vector;
};

#endif /* msgStru_h */
