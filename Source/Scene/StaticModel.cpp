#include "StaticModel.h"
#include "Core/RenderManager.h"

ST_NS_BEGIN

StaticModel::StaticModel(string fileName)
{
	_model = Model::load(fileName);
	_meshes = _model->getMeshes();
}

void StaticModel::addToBatch(RenderBatch &batch)
{
	mat4 model = getModelTransform();

	for (Mesh &mesh: _meshes)
	{
		batch.addRenderable(&mesh, model * mesh.getModelTransform(), 1);
	}
}

vector<Mesh> &StaticModel::getMeshes()
{
	return _meshes;
}

ModelRef StaticModel::getModel()
{
	return _model;
}

ST_NS_END
