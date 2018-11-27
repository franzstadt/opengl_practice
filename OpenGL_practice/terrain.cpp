#include "terrain.h"

void Terrain::setSize(int size)
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

void Terrain::generateRandom(int count) {

}