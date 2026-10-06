#include <algorithm>
#include <cmath>

#include "CollisionManager.h"
#include "MathFunction.h"

void CollisionManager::Init(const WorldBound worldBound) {
	m_worldBound = worldBound;
}

void CollisionManager::Reset(){
	m_objects.clear();
	m_collisionsInfo.clear();
}

void CollisionManager::PushObject(BaseGameObject & object){
	m_objects.push_back(&object);
}

const CollisionsInformation& CollisionManager::Update(){

	m_collisionsInfo.clear();

	for (size_t indexLeftObject{0}; indexLeftObject < m_objects.size(); indexLeftObject++) {

		BaseGameObject* object = m_objects.at(indexLeftObject);
		SearchBoundCollision(*object);

		size_t indexRightObject = indexLeftObject + 1;

		for (; indexRightObject < m_objects.size(); indexRightObject++) {
			BaseGameObject* rightObject = m_objects.at(indexRightObject);
			SearchObjectCollision(*object, *rightObject);	
		}
	}

	m_objects.clear();

	return m_collisionsInfo;
}

void CollisionManager::SearchBoundCollision(BaseGameObject& object){

	sf::Vector2f &pos = object.getPhysicalBody().position;
	float radius = object.getPhysicalBody().collisionRadius;
	
	sf::Vector2f sideVector(0.f, 0.f);
	
	if (pos.x - radius < m_worldBound.left) { //left
		pos.x = m_worldBound.left + radius;
		CollisionWallDetectInfo(object);
		object.getPhysicalBody().velocity.x *= wallCollisionCoef;
	}
	else if (pos.x + radius > m_worldBound.right) { //right
		pos.x = m_worldBound.right - radius;
		CollisionWallDetectInfo(object);
		object.getPhysicalBody().velocity.x *= wallCollisionCoef;
	}
	
	if (pos.y - radius < m_worldBound.top) { //top
		pos.y = radius + m_worldBound.top;
		CollisionWallDetectInfo(object);
		object.getPhysicalBody().velocity.y *= wallCollisionCoef;
	}
	else if (pos.y + radius > m_worldBound.bottom) { //bottom
		pos.y = m_worldBound.bottom - radius;
		CollisionWallDetectInfo(object);
		object.getPhysicalBody().velocity.y *= wallCollisionCoef;
	}
	
}

void CollisionManager::SearchObjectCollision(BaseGameObject& LeftObject, BaseGameObject& RightObject){

	using namespace MyMath;

	sf::Vector2f normal(0.f, 0.f);

	sf::Vector2f& posLeft = LeftObject.getPhysicalBody().position;
	const float& radiusLeft = LeftObject.getPhysicalBody().collisionRadius;
	
	sf::Vector2f& posRight = RightObject.getPhysicalBody().position;
	const float& radiusRight = RightObject.getPhysicalBody().collisionRadius;

	sf::Vector2f delta = posRight - posLeft;
	float dist = MathFunction::getVectorLength(delta); 
	
	float collisonDist = radiusLeft + radiusRight;
	
	if (dist == 0.f) {
		posRight.x -= 1.f;
		posLeft.x += 1.f;

		delta = posRight - posLeft;
		dist = MathFunction::getVectorLength(delta);
	}

	if (dist <= collisonDist) {
	
		float inverseMassLeft = 1.f / LeftObject.getPhysicalBody().mass;
		float inverseMassRight = 1.f / RightObject.getPhysicalBody().mass;

		normal = (posRight - posLeft) / dist;

		float penetration = (collisonDist - dist) / (inverseMassLeft + inverseMassRight);
		posLeft -= normal * penetration * inverseMassLeft;
		posRight += normal * penetration * inverseMassRight;
		
		sf::Vector2f relativeVelocity = RightObject.getPhysicalBody().velocity - LeftObject.getPhysicalBody().velocity;
		float velocityAlongNormal = relativeVelocity.x * normal.x + relativeVelocity.y * normal.y;

		if (velocityAlongNormal > 0.f) {
			return;
		}

		float restitution = std::min(RightObject.getPhysicalBody().restitution, LeftObject.getPhysicalBody().restitution);
		float impulseMagnitude = (-1.f * (1.f + restitution) * velocityAlongNormal) / (inverseMassLeft + inverseMassRight);
		sf::Vector2f impulse = impulseMagnitude * normal;

		LeftObject.getPhysicalBody().velocity -= impulse * inverseMassLeft;
		RightObject.getPhysicalBody().velocity += impulse * inverseMassRight;

		float impulseSum = MathFunction::getVectorLength(impulse);
		impulseSum = std::abs(impulseSum);

		CollisionObjectsDetectInfo(LeftObject, RightObject, impulseSum);
	}
}

void CollisionManager::CollisionWallDetectInfo(BaseGameObject & object){
	CollisionInfo info;
	info.typeCollision = TypeCollision::OBJECT_WALL;
	info.objectA = &object;

	float impulse = MyMath::MathFunction::getVectorLength(object.getPhysicalBody().velocity) * object.getPhysicalBody().mass;
	impulse = std::abs(impulse);

	info.impulseCollision = impulse;

	m_collisionsInfo.push_back(info);
}

void CollisionManager::CollisionObjectsDetectInfo(BaseGameObject & LeftObject, BaseGameObject & RightObject, float impulse) {
	
	CollisionInfo info;

	info.typeCollision = TypeCollision::OBJECT_OBJECT;
	info.objectA = &LeftObject;
	info.objectB = &RightObject;
	info.impulseCollision = impulse;

	m_collisionsInfo.push_back(info);
}

