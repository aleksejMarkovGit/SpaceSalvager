#pragma once

#include "WorldBound.h"
#include "BaseGameObject.h"
#include <vector>

enum class TypeCollision {
	OBJECT_WALL,
	OBJECT_OBJECT,
	NONE,
};

struct CollisionInfo{
	TypeCollision typeCollision{ TypeCollision::NONE };
	BaseGameObject* objectA{ nullptr };
	BaseGameObject* objectB{ nullptr };

	float impulseCollision{ 0.f };
};

using CollisionsInformation = std::vector<CollisionInfo>;

class CollisionManager
{

public:

	void Init(const WorldBound worldBound);
	void Reset();
	void PushObject(BaseGameObject& object);
	const CollisionsInformation& Update();

private:

	void SearchBoundCollision(BaseGameObject& object);
	void SearchObjectCollision(BaseGameObject& LeftObject, BaseGameObject& RightObject);

	void CollisionWallDetectInfo(BaseGameObject& object);
	void CollisionObjectsDetectInfo(BaseGameObject& LeftObject, BaseGameObject& RightObject, float impulse);
	
	WorldBound m_worldBound;
	std::vector<BaseGameObject*> m_objects;
	CollisionsInformation m_collisionsInfo;

	const float wallCollisionCoef{ -0.8f };
};

