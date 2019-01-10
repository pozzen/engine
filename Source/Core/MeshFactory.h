#ifndef _MESH_FACTORY_H_INCLUDED_
#define _MESH_FACTORY_H_INCLUDED_

#include "Engine.h"
#include "Graphics/Mesh.h"

ST_NS_BEGIN

class MeshFactory
{
public:
	static Mesh *createCube(float dimensions);

};

ST_NS_END

#endif // _MESH_FACTORY_H_INCLUDED_
