#ifndef MGDV_CUBE_H
#define MGDV_CUBE_H

#include "Primitive.h"

class Cube : public Primitive {
private:
	static Cube instance;
public:
	virtual ~Cube();
	virtual void Render() override;
	//static Cube Get();

private:
	Cube();
};

#endif