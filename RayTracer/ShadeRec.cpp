#include "ShadeRec.h"


ShadeRec::ShadeRec(World& world)
	:world(world), hitObject(false), localHitPoint(),normal(), color(),ray(glm::vec3(0),glm::vec3(0)),
	depth(0),hitPoint(),direction(),u(0),v(0),material(NULL)
{
}


ShadeRec::~ShadeRec(void)
{
}

ShadeRec::ShadeRec(const ShadeRec& sr)
	:hitObject(sr.hitObject), localHitPoint(sr.localHitPoint),normal(sr.normal),
	color(sr.color), world(sr.world),material(sr.material),hitPoint(sr.hitPoint),
	ray(sr.ray),depth(sr.depth),direction(sr.direction),u(sr.u),v(sr.v),t(sr.t)
{
}
