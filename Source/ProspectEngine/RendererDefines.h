#pragma once
#define GLEW_STATIC
#include <GL/glew.h>

#include <glm/vec3.hpp>

const int GL_NULL = 0;
const glm::vec3 POS_X(1, 0, 0);
const glm::vec3 POS_Y(0, 1, 0);
const glm::vec3 POS_Z(0, 0, 1);
const glm::vec3 NEG_X(-1, 0, 0);
const glm::vec3 NEG_Y(0, -1, 0);
const glm::vec3 NEG_Z(0, 0, -1);

const glm::vec3 DEFAULT_TRANSLATION(0, 0, 0);
const glm::vec3 DEFAULT_ROTATION(0, 0, 0);
const glm::vec3 DEFAULT_SCALE(1, 1, 1);