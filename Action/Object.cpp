#include "Object.hpp"

Draw Object::d(0, 0, 0);
Point<float> Object::gravity(1.0f, 0.0f);

void Object::draw() const
{
	d.circle((Point<int>)pos, 10, 0xffffff, true);
}

