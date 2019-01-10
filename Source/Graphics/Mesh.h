#ifndef _MESH_H_INCLUDED_
#define _MESH_H_INCLUDED_

#include "Engine.h"
#include "Texture.h"
#include "Shader.h"
#include "Material.h"
#include "Core/Renderable.h"

ST_NS_BEGIN

class Model;

struct Vertex {
	vec3 _position;
	vec3 _normal;
	vec2 _texCoords;
	vec3 _color;
	vec3 _tangent;
	vec3 _bitangent;
};

class Mesh: public Renderable
{
public:
	Mesh(const vector<Vertex> &vertices, const vector<GLuint> &indices, const Material &material);
	Mesh(const string &fileName, aiMesh *mesh, const aiScene *scene);
	Mesh(const Mesh &mesh);
	~Mesh();

	virtual void render() const;
	void getBoundingBox(vec3 &a, vec3 &b) const;

	const vector<Vertex> &getVertices() const;
	const vector<GLuint> &getIndices() const;
	GLuint getVAO() const;
	GLuint getVBO() const;
	GLuint getEBO() const;

	Model *getOwner() const;
	void setOwner(Model *owner);

	virtual const Material &getMaterial() const;
	void setMaterial(const Material &material);

	mat4 getModelTransform() const;
	void setModelTransform(const mat4 &modelTransform);

private:
	void setupMesh();

	Model *_owner = nullptr;

	vector<Vertex> _vertices;
	vector<GLuint> _indices;

	GLuint _VAO, _VBO, _EBO;

	Material _material;

	mat4 _modelTransform;
};

ST_NS_END

#endif // _MESH_H_INCLUDED_
