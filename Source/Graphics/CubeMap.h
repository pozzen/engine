#ifndef _CUBEMAP_H_INCLUDED_
#define _CUBEMAP_H_INCLUDED_

#include <Engine.h>
#include "Graphics/GLState.h"
#include "Core/Resource.h"

ST_NS_BEGIN

class CubeMap;
typedef Reference<CubeMap> CubeMapRef;

class CubeMap: public Resource
{
public:
	static CubeMapRef load(const string &fileName, const string &suffix);

	CubeMap(const string &fileName, const string &suffix);
	~CubeMap();

	void bind(GLuint unit) const;

	GLuint getTexture() const;
	const string &getName() const;

private:
	GLuint _texture = 0;
	string _name;
	bool _loaded = false;

};

ST_NS_END

#endif // _CUBEMAP_H_INCLUDED_
