#ifndef MGDV_PRIMITIVE_H
#define MGDV_PRIMITIVE_H

class Primitive {
public:
	Primitive() {};
	virtual ~Primitive() {};

	virtual void Render() = 0;
};

#endif