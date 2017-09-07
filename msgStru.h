//
//  msgStru.h
//  qiuFight
//
//  Created by 张跃东 on 16/2/29.
//
//

#ifndef msgStru_h
#define msgStru_h

#pragma pack(1)

#define MSG_HEAD \
    uint8_t msgid;

// ----- request

// 255 进入棋盘
struct EnterBoard {
    MSG_HEAD;
    uint32_t protocol;      // 保留字段，当前为0
    uint8_t index;          // 创建的index
    uint32_t roleID;        // 角色id
    uint32_t key;           // 服务器key
	uint32_t roomId;           // 房间
    uint8_t name_len;       // 名字长度
    char name[];             // 名字字节
};

// 21 吐出质量（按键）
struct EjectMass {
    MSG_HEAD;
};

// 17 分裂 （按键）
struct SplitCell
{
    MSG_HEAD;
};

// 16 移动到目标
struct sMoveTo{
    MSG_HEAD;
    int32_t target_x;
    int32_t target_y;
    
    int32_t dir_x;
    int32_t dir_y;
};

// 22 请求复活
struct ReqRebirth
{
    MSG_HEAD;
};

// response

// 64 通知棋盘大小
struct SetBorder
{
    MSG_HEAD;
    int32_t left;
    int32_t top;
    int32_t right;
    int32_t bottom;
};

// 32 添加自己控制的细胞，进入棋盘
struct AddNode
{
    MSG_HEAD;
    uint32_t nodeid;
};

// 16 更新变化的节点（删除的、不可见、变更、包括自身和移动）
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
        uint16_t indx;  //对应图片的index
        uint8_t r;
        uint8_t g;
        uint8_t b;
        uint8_t spike; //刺
        uint16_t mass;  // 质量
        uint8_t name_len; // 名字长度
        char name[]; // 有效名字
    } vector2;
    
};

// 17 战斗排名更新
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

// 18 战斗结算（最后一个元素为自己）
struct GameOver
{
    uint16_t over_count;
    struct
    {
        uint32_t rank; // 名次
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
