#pragma once
#include <string>
#include <vector>

class Terrain
{
	std::vector<float> _points;
	int m_size;

	void setSize(int size);
	void set(int i, int j, float v);
public:

	//generate random terrain data
	void generateRandom(int count);
	
	Terrain();
};

