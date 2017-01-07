#include "DoorStencil.h"

DoorStencil::DoorStencil()
{
	stencil.push_back(std::pair<CubeCoords, int>(CubeCoords(0, 0, 0), 1000));
}
