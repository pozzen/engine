#ifndef _UNIFORM_BUFFER_OBJECT_H_INCLUDED_
#define _UNIFORM_BUFFER_OBJECT_H_INCLUDED_

#include "Engine.h"

ST_NS_BEGIN

class UniformBufferObject
{
public:
	UniformBufferObject();
	~UniformBufferObject();

	void update(const glm::mat4 &viewProjection, const glm::vec3 &cameraPosition, float time);

private:
	GLuint _ubo;

};

ST_NS_END

#endif // _UNIFORM_BUFFER_OBJECT_H_INCLUDED_
