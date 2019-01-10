#include <string>
#include <vector>
#include <algorithm>
#include <unordered_map>
#include <memory>
#include <iostream>
#include <stdlib.h>
#include <fstream>

#include <GL/glew.h>
#include <SDL.h>
#include <SDL_opengl.h>

#include <glm/common.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/norm.hpp>

#include <BulletDynamics/btBulletDynamicsCommon.h>
#include <bullet/BulletCollision/Gimpact/btGImpactCollisionAlgorithm.h>

#include "tinyxml2.h"

using std::string;
using std::vector;
using std::unordered_map;
using std::cout;
using std::cerr;
using std::endl;
using std::shared_ptr;

using glm::vec2;
using glm::vec3;
using glm::vec4;
using glm::quat;
using glm::mat3;
using glm::mat4;
using glm::abs;
using glm::clamp;
using glm::distance;
using glm::distance2;
using glm::radians;
using glm::normalize;
using glm::perspective;
using glm::cross;

using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;
