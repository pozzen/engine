#ifndef _RENDERABLE_H_INCLUDED_
#define _RENDERABLE_H_INCLUDED_

#include "Engine.h"
#include "Graphics/Material.h"

ST_NS_BEGIN

class Renderable
{
public:
	virtual void render() const = 0;
	virtual const Material &getMaterial() const = 0;

};

ST_NS_END

#endif // _RENDERABLE_H_INCLUDED_
