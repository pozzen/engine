#ifndef _SKYBOX_H_INCLUDED_
#define _SKYBOX_H_INCLUDED_

#include "Engine.h"
#include "Node.h"
#include "Graphics/CubeMap.h"
#include "Graphics/Shader.h"

ST_NS_BEGIN

class Skybox: public Node, public Renderable
{
public:
	Skybox(string fileName, string suffix);
	~Skybox();

	virtual void render() const;
	virtual const Material &getMaterial() const;

	virtual void addToBatch(RenderBatch &batch);
	virtual bool isVisible(const Frustum &frustum);

	NODE_TYPE(Skybox)

private:
	CubeMapRef _cubemap;

	GLuint _vao;
	GLuint _vbo;

	static Shader _shader;

};

ST_NS_END

#endif // _SKYBOX_H_INCLUDED_
