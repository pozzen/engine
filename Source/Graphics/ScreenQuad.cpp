#include "ScreenQuad.h"

ST_NS_BEGIN

ScreenQuad::ScreenQuad()
{
	static const glm::vec2 fullScreenQuad[] = {
		glm::vec2(-1.0,  1.0), glm::vec2(0.0, 1.0),
		glm::vec2(-1.0, -1.0), glm::vec2(0.0, 0.0),
		glm::vec2( 1.0, -1.0), glm::vec2(1.0, 0.0),

		glm::vec2(-1.0,  1.0), glm::vec2(0.0, 1.0),
		glm::vec2( 1.0, -1.0), glm::vec2(1.0, 0.0),
		glm::vec2( 1.0,  1.0), glm::vec2(1.0, 1.0),
	};

	glGenVertexArrays(1, &_vao);
	glGenBuffers(1, &_vbo);

	glBindVertexArray(_vao);
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
	glBufferData(GL_ARRAY_BUFFER, 12 * sizeof(glm::vec2), &fullScreenQuad[0], GL_STATIC_DRAW);

	// Vertex Positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec2), (GLvoid*)0);

	// Vertex Texture Coords
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(glm::vec2), (GLvoid*)sizeof(glm::vec2));

	glBindVertexArray(0);
}

ScreenQuad::~ScreenQuad()
{
	glDeleteVertexArrays(1, &_vao);
}

void ScreenQuad::render()
{
	glBindVertexArray(_vao);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
}

ST_NS_END
