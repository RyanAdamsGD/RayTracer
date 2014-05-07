#include "Vertex.h"

using glm::vec2;
using glm::vec3;
using glm::vec4;

uint Vertex::POSITION_OFFSET = 0;
uint Vertex::COLOR_OFFSET = sizeof(glm::lowp_vec3);
uint Vertex::NORMAL_OFFSET = sizeof(glm::lowp_vec3) + sizeof(glm::lowp_vec4);
uint Vertex::UV_OFFSET = sizeof(glm::lowp_vec3) + sizeof(glm::lowp_vec4) + sizeof(glm::lowp_vec3);
uint Vertex::SKELETONID_OFFSET = sizeof(glm::lowp_vec3) + sizeof(glm::lowp_vec4) + sizeof(glm::lowp_vec3) + sizeof(glm::lowp_vec2);
uint Vertex::WEIGHT_OFFSET = sizeof(glm::lowp_vec3) + sizeof(glm::lowp_vec4) + sizeof(glm::lowp_vec3) + sizeof(glm::lowp_vec2) + sizeof(uint);
uint Vertex::STRIDE = sizeof(Vertex);
