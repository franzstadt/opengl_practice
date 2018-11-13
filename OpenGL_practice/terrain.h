#pragma once
#include <string>
#include <vector>

class terrain
{
	std::vector<float> _points;
	int m_size;

	void set_size(int size);
	void set(int i, int j, float v);

public:
	
	terrain();
};

