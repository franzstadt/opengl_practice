#include "terrain.h"

void terrain::set_size(int size)
{
	_points = decltype(_points)(size*size, 0.0f);
}

void terrain::set(int i, int j, float v)
{
	//_points
}

terrain::terrain()
{
	
}
