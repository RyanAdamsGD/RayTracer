#ifndef MATERIAL_H
#define MATERIAL_H
#include "glm\gtx\transform.hpp"
class ShadeRec;

class Material
{
protected:
	bool hasShadows;
public:
	virtual ~Material();

	virtual glm::vec3 shade(const ShadeRec& sr)const;
	virtual glm::vec3 areaLightShade(const ShadeRec& sr)const;
	virtual glm::vec3 getRadiance(const ShadeRec& sr)const;
	virtual glm::vec3 pathShade(const ShadeRec& sr)const;
	
	inline void setHasShadows(bool value) { hasShadows = value; }
	inline bool getHasShadows() { return hasShadows; }
};

#endif