#pragma once

#include <vector>


class TriangleMesh
{
	bool _created = false;

	std::vector<float>			_vertices;
	std::vector<float>			_uvs;

	std::vector<unsigned int>	_vertexIndices;
	std::vector<unsigned int>	_uvIndices;


	unsigned int				_vertexArrayObject = 0;

	unsigned int				_vertexBufferObject  = 0;
	unsigned int				_elementBufferObject = 0;

	unsigned int				_uvBufferObject = 0;
	unsigned int				_uvElementBufferObject = 0;

	void						create();
	void						_create2();
public:

	typedef unsigned int vertexIndex_t;
	typedef unsigned int uvIndex_t;

	TriangleMesh();
	~TriangleMesh();

	void setVertices(std::initializer_list<float> vertices) {
		_vertices.assign(vertices);
	}

	void setUVs(std::initializer_list<float> uvs) {
		_uvs.assign(uvs);
	}


	void addTriangle(
		vertexIndex_t	v1,
		vertexIndex_t	v2,
		vertexIndex_t	v3,
		uvIndex_t		t1,
		uvIndex_t		t2,
		uvIndex_t		t3)
	{
		_vertexIndices.insert(_vertexIndices.end(), { v1, v2, v3 });
		_uvIndices.insert(_uvIndices.end(), { t1, t2, t3 });
	}

	void setTexture(const std::string& path);


	void render();

};

