#pragma once

#include <vector>


class TriangleMesh
{
	std::vector<float>			_vertices;
	std::vector<unsigned int>	_indices;



	unsigned int				_vertexBufferObject;
	unsigned int				_vertexArrayObject;
	unsigned int				_elementBufferObject;
public:

	typedef unsigned int triangleVertexIndex_t;

	TriangleMesh();
	~TriangleMesh();

	void setVertices(std::initializer_list<float> vertices) {
		_vertices.assign(vertices);
	}

	void addTriangle(
		triangleVertexIndex_t v1,
		triangleVertexIndex_t v2,
		triangleVertexIndex_t v3)
	{
		_indices.insert(_indices.end(), { v1, v2, v3 });
	}

	void finalize();

	void render();
};

