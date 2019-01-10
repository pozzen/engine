#include "Component.h"

ST_NS_BEGIN

vector<Component *> Component::_scheduled;

void Component::updateAll(float deltaTime)
{
	for (Component *component: _scheduled)
	{
		component->update(deltaTime);
	}
}

void Component::scheduleUpdate()
{
	_scheduled.push_back(this);
}

void Component::unscheduleUpdate()
{
	for (vector<Component *>::iterator it = _scheduled.begin(); it != _scheduled.end(); it++)
	{
		if (*it == this)
		{
			_scheduled.erase(it);
			return;
		}
	}
}

Node *Component::getParent()
{
	return _parent;
}

void Component::setParent(Node *parent)
{
	_parent = parent;
}

ST_NS_END
