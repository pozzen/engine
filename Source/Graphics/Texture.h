#ifndef _TEXTURE_H_INCLUDED_
#define _TEXTURE_H_INCLUDED_

#include <Engine.h>
#include "Graphics/GLState.h"
#include "Core/Resource.h"

ST_NS_BEGIN

enum TextureType
{
	TEXTURE_DIFFUSE = 0,
	TEXTURE_SPECULAR,
	TEXTURE_AMBIENT,
	TEXTURE_NORMAL,
	TEXTURE_CUBEMAP,

	TEXTURE_TYPE_COUNT
};

class Texture;
typedef Reference<Texture> TextureRef;

class Texture: public Resource
{
public:

	static TextureRef load(const string &fileName, GLuint textureWrap = GL_REPEAT);

	Texture(const string &fileName, GLuint textureWrap = GL_REPEAT, GLuint filter = GL_LINEAR_MIPMAP_NEAREST);
	~Texture();

	void bind(GLuint unit) const;

	GLuint getTexture() const;
	const string &getName() const;

	int getWidth() const;
	int getHeight() const;

private:
	GLuint _texture = 0;
	string _name;
	int _width = 0;
	int _height = 0;
	bool _loaded = false;

};

ST_NS_END

#endif // _TEXTURE_H_INCLUDED_
