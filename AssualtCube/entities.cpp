#include "entities.h"

Vec3f& Player::GetPositionHead()
{
	return this->m_pos_head;
}

Vec3f& Player::GetPositionOrigin()
{
	return this->m_pos_origin;
}

Vec3f& Player::GetViewAngles()
{
	return this->m_view_angles;
}

INT32 Player::GetHealth()
{
	return this->m_health;
}

INT32 Player::GetArmour()
{
	return this->m_armour;
}

CHAR* Player::GetName()
{
	return this->m_name;
}

Player* Entities::GetLocalPlayer()
{
	return this->m_local_player;
}

std::vector< Player* > Entities::GetEntities()
{
	std::vector< Player* > entities;
	//multi-level pointer (2 levels) as the pointer only points to the pointers of players. Need one more pointer to access the players. 
	for (std::size_t i = 1; i < this->m_entity_count; i++)
	{
		if( this->m_entities[ i ] ) //check if player is valid
			entities.push_back( this->m_entities[ i ] );
	}
	return entities;
}

INT32 Entities::GetEntityCount()
{
	return this->m_entity_count;
}
