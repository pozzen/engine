#ifndef _PHYSICSWORLD_H_INCLUDED_
#define _PHYSICSWORLD_H_INCLUDED_

#include "Engine.h"

ST_NS_BEGIN

class PhysicsWorld
{
private:
	btDiscreteDynamicsWorld *_dynamicsWorld;
	btBroadphaseInterface *_broadphase;
	btDefaultCollisionConfiguration *_collisionConfiguration;
	btCollisionDispatcher *_dispatcher;
	btSequentialImpulseConstraintSolver *_solver;

	vector<btRigidBody *> _bodies;

public:
	PhysicsWorld(glm::vec3 gravity);
	~PhysicsWorld();
	btRigidBody *addRigidBody(const glm::vec3 &position, const glm::vec3 &rotation, btCollisionShape *shape, float mass);
	void removeRigidBody(btRigidBody *rigitBody);
	void update(float deltaTime);
	glm::vec3 rayTest(glm::vec3 from, glm::vec3 to);

};

ST_NS_END

#endif // _PHYSICSWORLD_H_INCLUDED_
