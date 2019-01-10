#ifndef _STATIC_MODEL_H_INCLUDED_
#define _STATIC_MODEL_H_INCLUDED_

#include "Engine.h"
#include "Node.h"
#include "Graphics/Model.h"

ST_NS_BEGIN

class StaticModel: public Node
{
public:
	StaticModel(string fileName);

	virtual void addToBatch(RenderBatch &batch);
	vector<Mesh> &getMeshes();
	ModelRef getModel();

	NODE_TYPE(StaticModel)

private:
	ModelRef _model;
	vector<Mesh> _meshes;

};

ST_NS_END

#endif // _STATIC_MODEL_H_INCLUDED_
