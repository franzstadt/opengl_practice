#include "terrain.h"

void Terrain::set_size(int size)
{
	_points = decltype(_points)(size*size, 0.0f);
}

void Terrain::set(int i, int j, float v)
{
	//_points
}

Terrain::Terrain()
{
	
}
