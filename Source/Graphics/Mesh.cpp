#include "Mesh.h"
#include <tinyxml2.h>

ST_NS_BEGIN

Mesh::Mesh(const vector<Vertex> &vertices, const vector<GLuint> &indices, const Material &material):
	_vertices(vertices), _indices(indices), _material(material)
{
	setupMesh();
}

Mesh::Mesh(const string &fileName, aiMesh *mesh, const aiScene *scene)
{
	for(GLuint i = 0; i < mesh->mNumVertices; i++)
	{
		Vertex vertex;

		// Process vertex positions, normals, coordinates, tangents, and bitangents
		vertex._position = vec3(mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z);
		vertex._normal = vec3(mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z);

		if (mesh->HasTextureCoords(0))
			vertex._texCoords = vec2(mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y);
		else
			vertex._texCoords = vec2(0.0f, 0.0f);

		if (mesh->HasTangentsAndBitangents())
		{
				vertex._tangent = vec3(mesh->mTangents[i].x, mesh->mTangents[i].y, mesh->mTangents[i].z);
				vertex._bitangent = vec3(mesh->mBitangents[i].x, mesh->mBitangents[i].y, mesh->mBitangents[i].z);
		}

		if (mesh->HasVertexColors(0))
			vertex._color = vec3(mesh->mColors[i]->r, mesh->mColors[i]->g, mesh->mColors[i]->b);

		_vertices.push_back(vertex);
	}

	// Process indices
	for(GLuint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for(GLuint j = 0; j < face.mNumIndices; j++)
			_indices.push_back(face.mIndices[j]);
	}

	// Process material
	_material = Material(scene->mMaterials[mesh->mMaterialIndex]);

	setupMesh();
}

Mesh::Mesh(const Mesh &mesh):
	_vertices(mesh.getVertices()), _indices(mesh.getIndices()),
	_VBO(mesh.getVAO()), _VAO(mesh.getVAO()), _EBO(mesh.getEBO()),
	_material(mesh._material), _owner(mesh.getOwner())
{
}

void Mesh::setupMesh()
{
	glGenVertexArrays(1, &_VAO);
	glGenBuffers(1, &_VBO);
	glGenBuffers(1, &_EBO);

	glBindVertexArray(_VAO);
	glBindBuffer(GL_ARRAY_BUFFER, _VBO);

	glBufferData(GL_ARRAY_BUFFER, _vertices.size() * sizeof(Vertex), &_vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, _indices.size() * sizeof(GLuint), &_indices[0], GL_STATIC_DRAW);

	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)0);

	// Vertex Normals
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, _normal));

	// Vertex Texture Coords
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, _texCoords));

	// Vertex Color
	glEnableVertexAttribArray(3);
	glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, _color));

	// Vertex Tangents
	glEnableVertexAttribArray(4);
	glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, _tangent));

	// Vertex Bitangents
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, _bitangent));

	glBindVertexArray(0);
}

mat4 Mesh::getModelTransform() const
{
	return _modelTransform;
}

void Mesh::setModelTransform(const mat4 &modelTransform)
{
	_modelTransform = modelTransform;
}

const Material &Mesh::getMaterial() const
{
	return _material;
}

void Mesh::setMaterial(const Material &material)
{
	_material = material;
}

Model *Mesh::getOwner() const
{
	return _owner;
}

void Mesh::setOwner(Model *owner)
{
	_owner = owner;
}

GLuint Mesh::getEBO() const
{
	return _EBO;
}

GLuint Mesh::getVBO() const
{
	return _VBO;
}

GLuint Mesh::getVAO() const
{
	return _VAO;
}

const vector<GLuint> &Mesh::getIndices() const
{
	return _indices;
}

const vector<Vertex> &Mesh::getVertices() const
{
	return _vertices;
}

Mesh::~Mesh()
{
	if (!_owner) glDeleteVertexArrays(1, &_VAO);
}

void Mesh::render() const
{
	glBindVertexArray(_VAO);
	glDrawElements(GL_TRIANGLES, _indices.size(), GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);
}

void Mesh::getBoundingBox(glm::vec3 &a, glm::vec3 &b) const
{
	// FIXME: account for transform

	for (int i = 0; i < _vertices.size(); i++)
	{
		vec3 pos = _vertices[i]._position;

		if (i == 0)
		{
			a = pos;
			b = pos;
		}
		else
		{
			if (pos.x > a.x) a.x = pos.x;
			if (pos.y > a.y) a.y = pos.y;
			if (pos.z > a.z) a.z = pos.z;

			if (pos.x < b.x) b.x = pos.x;
			if (pos.y < b.y) b.y = pos.y;
			if (pos.z < b.z) b.z = pos.z;
		}
	}
}

ST_NS_END
