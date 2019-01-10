#ifndef _COMPONENT_H_INCLUDED_
#define _COMPONENT_H_INCLUDED_

#include "Engine.h"

ST_NS_BEGIN

class Node;

class Component
{
public:
	static void updateAll(float deltaTime);

	virtual void update(float deltaTime) = 0;

	void scheduleUpdate();
	void unscheduleUpdate();

	Node *getParent();
	void setParent(Node *parent);

protected:
	Node *_parent;
	static vector<Component *> _scheduled;

};

ST_NS_END

#endif // _COMPONENT_H_INCLUDED_
