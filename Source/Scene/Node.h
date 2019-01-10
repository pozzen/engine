#ifndef _NODE_H_INCLUDED_
#define _NODE_H_INCLUDED_

#include "Engine.h"
#include "Core/Transform.h"
#include "Core/Frustum.h"
#include "Graphics/Shader.h"
#include "Graphics/Mesh.h"
#include "Component.h"

ST_NS_BEGIN

class Light;
class RenderBatch;

class Node
{
public:
	Node();
	~Node();

	Transform &getTransform();
	const Transform &getTransform() const;

	virtual void addChild(Node *node);
	virtual void removeChild(Node *node);
	virtual void deleteChild(Node *node);

	virtual void addComponent(Component *component);
	virtual void deleteComponent(Component *component);

	vec3 getPositionTransformed() const;
	quat getRotationTransformed() const;
	vec3 getScaleTransformed() const;

	string name() const;
	void setName(const string &name);

	Node *getOwner() const;
	void setOwner(Node *owner);

	mat4 getModelTransform() const;

	virtual void addToBatch(RenderBatch &batch);
	virtual bool isVisible(const Frustum &frustum);

	const vector<Node *> &getChildren() const;
	const vector<Component *> &getComponents() const;

	NODE_TYPE(Node)

protected:
	vector<Node *> _children;
	vector<Component *> _components;

private:
	Transform _transform;
	string _name;
	// _owner is the Node responsible for deleting this Node
	Node *_owner = nullptr;

};

ST_NS_END

#endif // _NODE_H_INCLUDED_
