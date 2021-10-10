#include "ECS\ECS.h"

void Entity::AddGroup(Group mGroup)
{
	groupBitset[mGroup] = true;
	manager.AddToGroup(this, mGroup);
}
