#ifndef _MODEL_H_INCLUDED_
#define _MODEL_H_INCLUDED_

#include "Common.h"
#include "Mesh.h"
#include "Texture.h"
#include "Shader.h"
#include "Core/Resource.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

ST_NS_BEGIN

class Model;
typedef Reference<Model> ModelRef;

class Model: public Resource
{
public:
	static ModelRef load(const string &fileName);

	Model(const string &fileName);
	~Model();

	void getBoundingBox(vec3 &a, vec3 &b) const;

	vector<Mesh> &getMeshes();

private:
	bool _loaded = false;
	vector<Mesh> _meshes;

	void processNode(const string &fileName, aiNode *node, const aiScene *scene, const mat4 &transform);

};

ST_NS_END

#endif // _MODEL_H_INCLUDED_
