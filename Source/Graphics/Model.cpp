#include "Model.h"
#include "Core/ResourceManager.h"

ST_NS_BEGIN

ModelRef Model::load(const string &fileName)
{
	ModelRef modelRef = ResourceManager::get<Model>(fileName);

	if (!modelRef)
	{
		Model *model = new Model(fileName);
		modelRef = ResourceManager::add<Model>(fileName, model);
	}

	return modelRef;
}

Model::Model(const string &fileName)
{
	Assimp::Importer import;
	const aiScene* scene = import.ReadFile(fileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_GenNormals | aiProcess_CalcTangentSpace);

	if(!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		cerr << "Assimp: " << import.GetErrorString() << endl;
		return;
	}

	processNode(fileName, scene->mRootNode, scene, mat4(1.0));

	_loaded = true;
}

Model::~Model()
{
	for (Mesh &mesh: _meshes)
	{
		mesh.setOwner(nullptr);
	}
}

void Model::processNode(const string &fileName, aiNode *node, const aiScene *scene, const mat4 &transform)
{
	glm::mat4 nodeTransform = transform * glm::transpose(glm::make_mat4(&node->mTransformation.a1));

	for(GLuint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];

		Mesh m(fileName, mesh, scene);
		m.setModelTransform(nodeTransform);
		m.setOwner(this);
		_meshes.push_back(m);
	}

	for(GLuint i = 0; i < node->mNumChildren; i++)
	{
		processNode(fileName, node->mChildren[i], scene, nodeTransform);
	}

	_loaded = true;
}

void Model::getBoundingBox(vec3 &a, vec3 &b) const
{
	for (unsigned int i = 0; i < _meshes.size(); i++)
	{
		vec3 bba, bbb;
		_meshes[i].getBoundingBox(bba, bbb);

		if (i == 0)
		{
			a = bba;
			b = bbb;
		}
		else
		{
			if (bba.x > a.x) a.x = bba.x;
			if (bba.y > a.y) a.y = bba.y;
			if (bba.z > a.z) a.z = bba.z;

			if (bbb.x < b.x) b.x = bbb.x;
			if (bbb.y < b.y) b.y = bbb.y;
			if (bbb.z < b.z) b.z = bbb.z;
		}
	}
}

vector<Mesh> &Model::getMeshes()
{
	return _meshes;
}

ST_NS_END
