#pragma once
#include <Windows.h>
#include <vector>
#include "vector.h"

// cool padding shit
#ifndef PAD
#define PAD_INSERT(x, y) x ## y
#define PAD_DEFINE(x, y) PAD_INSERT(x, y)
#define PAD(size) char PAD_DEFINE(padding_, __LINE__)[size]
#endif

class Player
{
private:
    UINT32* v_table;        //0x000
    Vec3f   m_pos_head;     //0x004
    PAD     (0x18);         //0x010
    Vec3f   m_pos_origin;   //0x028
    Vec3f   m_view_angles;  //0x034
    PAD     (0xAC);         //0x040
    INT32   m_health;       //0x0EC
    INT32   m_armour;       //0x0F0
    PAD     (0X111);        //0x0F4
    CHAR    m_name[256];    //0x205
                            //0x304

public:
    Player();
    ~Player();

    Vec3f& GetPositionHead();
    Vec3f& GetPositionOrigin();
    Vec3f& GetViewAngles();
    INT32  GetHealth();
    INT32  GetArmour();
    CHAR*  GetName();

};

class Entities
{
private:
    Player*  m_local_player; //0x000
    //multi-level pointer (2 levels) as the pointer only points to the pointers of players. Need one more pointer to access the players. 
    Player** m_entities;     //0x004
    PAD      (0x4);          //0x008
	INT32    m_entity_count; //0x00C
                             //0x010

public:
	Entities();
	~Entities();

    Player*                GetLocalPlayer();
    std::vector< Player* > GetEntities();
    INT32                  GetEntityCount();
};

