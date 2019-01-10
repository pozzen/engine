#include "PhysicsWorld.h"

ST_NS_BEGIN

PhysicsWorld::PhysicsWorld(glm::vec3 gravity)
{
	// Create physics world
	_broadphase = new btDbvtBroadphase();
	_collisionConfiguration = new btDefaultCollisionConfiguration();
	_dispatcher = new btCollisionDispatcher(_collisionConfiguration);
	btGImpactCollisionAlgorithm::registerAlgorithm(_dispatcher);
	_solver = new btSequentialImpulseConstraintSolver;

	_dynamicsWorld = new btDiscreteDynamicsWorld(_dispatcher, _broadphase, _solver, _collisionConfiguration);
	_dynamicsWorld->setGravity(btVector3(gravity.x, gravity.y, gravity.z));
}

PhysicsWorld::~PhysicsWorld()
{
	for (vector<btRigidBody *>::iterator it = _bodies.begin(); it != _bodies.end(); it++)
	{
		_dynamicsWorld->removeRigidBody(*it);
		delete (*it)->getMotionState();
		delete *it;
	}

	delete _dynamicsWorld;
	delete _solver;
	delete _dispatcher;
	delete _collisionConfiguration;
	delete _broadphase;
}

btRigidBody *PhysicsWorld::addRigidBody(const glm::vec3 &position, const glm::vec3 &rotation, btCollisionShape *shape, float mass)
{
	btDefaultMotionState *motionState = new btDefaultMotionState(btTransform(btQuaternion(rotation.x, rotation.y, rotation.z, 1), btVector3(position.x, position.y, position.z)));

	btVector3 inertia(0, 0, 0);
	shape->calculateLocalInertia(mass, inertia);

	btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(mass, motionState, shape, inertia);
	btRigidBody *rigidBody = new btRigidBody(rigidBodyCI);

	_bodies.push_back(rigidBody);

	_dynamicsWorld->addRigidBody(rigidBody);

	return rigidBody;
}

void PhysicsWorld::removeRigidBody(btRigidBody *rigitBody)
{
	_dynamicsWorld->removeRigidBody(rigitBody);
}

void PhysicsWorld::update(float deltaTime)
{
	_dynamicsWorld->stepSimulation(deltaTime, 10);
}

glm::vec3 PhysicsWorld::rayTest(glm::vec3 from, glm::vec3 to)
{
	btVector3 btFrom = btVector3(from.x, from.y, from.z),
			btTo = btVector3(to.x, to.y, to.z);

	btCollisionWorld::AllHitsRayResultCallback results(btFrom, btTo);
	_dynamicsWorld->rayTest(btFrom, btTo, results);

	btVector3 res = btFrom.lerp(btTo, results.m_closestHitFraction);
	return glm::vec3(res.x(), res.y(), res.z());
}

ST_NS_END
