#include "ConstantColor.h"
#include "DebugMemory.h"

ConstantColor::ConstantColor(void)
	:Texture()
{
}

glm::vec3 ConstantColor::getColor(const ShadeRec& sr)const
{
	return color;
}
