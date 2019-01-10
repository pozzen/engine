#include "Node.h"
#include "Light.h"
#include "Core/RenderManager.h"

ST_NS_BEGIN

Node::Node()
{
}

Node::~Node()
{
	for (Node *child: _children)
	{
		if (child->getOwner() == this) delete child;
	}
	_children.clear();

	for (Component *component: _components)
	{
		if (component->getParent() == this) delete component;
	}
	_components.clear();
}

Transform &Node::getTransform()
{
	return _transform;
}

const Transform &Node::getTransform() const
{
	return _transform;
}

void Node::addChild(Node *node)
{
	_children.push_back(node);
	node->setOwner(this);
}

void Node::removeChild(Node *node)
{
	for (auto it = _children.begin(); it != _children.end(); it++)
	{
		if (*it == node)
		{
			_children.erase(it);
			return;
		}
	}
}

void Node::deleteChild(Node *node)
{
	for (auto it = _children.begin(); it != _children.end(); it++)
	{
		if (*it == node)
		{
			if ((*it)->getOwner() == this) delete *it;
			_children.erase(it);
			return;
		}
	}
}

void Node::addComponent(Component *component)
{
	_components.push_back(component);
	component->setParent(this);
}

void Node::deleteComponent(Component *component)
{
	for (auto it = _components.begin(); it != _components.end(); it++)
	{
		if (*it == component)
		{
			if ((*it)->getParent() == this) delete *it;
			_components.erase(it);
			return;
		}
	}
}

//void Node::update(float deltaTime)
//{
//	for (Node *child: _children)
//	{
//		child->update(deltaTime);
//	}
//	for (Component *component: _components)
//	{
//		component->update(deltaTime);
//	}
//}

vec3 Node::getPositionTransformed() const
{
	return vec3(getModelTransform()[3]);
}

quat Node::getRotationTransformed() const
{
	return quat(getModelTransform());
}

vec3 Node::getScaleTransformed() const
{
	const mat4 &transform = getModelTransform();
	return vec3(length(transform[0]), length(transform[1]), length(transform[2]));
}

Node *Node::getOwner() const
{
	return _owner;
}

void Node::setOwner(Node *owner)
{
	_owner = owner;
}

mat4 Node::getModelTransform() const
{
	if (!_owner) return _transform.getModel();

	return _owner->getModelTransform() * _transform.getModel();
}

void Node::addToBatch(RenderBatch &batch)
{
	for (Node *child: _children)
	{
		child->addToBatch(batch);
	}
}

bool Node::isVisible(const Frustum &frustum)
{
	for (Node *child: _children)
	{
		if (child->isVisible(frustum)) return true;
	}

	return true;
}

const vector<Node *> &Node::getChildren() const
{
	return _children;
}

const vector<Component *> &Node::getComponents() const
{
	return _components;
}

string Node::name() const
{
	return _name;
}

void Node::setName(const string &name)
{
	_name = name;
}

ST_NS_END
