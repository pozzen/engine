#ifndef _ENGINE_H_INCLUDED_
#define _ENGINE_H_INCLUDED_

#include "Common.h"

#define ST_NS_BEGIN namespace ST {
#define ST_NS_END }
#define ST_NS_USE using namespace ST

#define NODE_TYPE(name) virtual inline string type() { return #name; }

ST_NS_BEGIN
#define SHADER_PATH(pp) ("Assets/Shaders/" pp)
//#define TEXTURE_PATH(pp) ("Assets/Textures/" pp)
ST_NS_END

#endif // _ENGINE_H_INCLUDED_
