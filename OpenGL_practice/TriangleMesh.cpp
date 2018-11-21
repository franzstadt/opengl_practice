#include "TriangleMesh.h"


#include <glad/glad.h>

TriangleMesh::TriangleMesh()
{
	glGenVertexArrays(1, &_vertexArrayObject);
	glGenBuffers(1, &_vertexBufferObject);
	glGenBuffers(1, &_elementBufferObject);
}


TriangleMesh::~TriangleMesh()
{
	glDeleteVertexArrays(1, &_vertexArrayObject);
	glDeleteBuffers(1, &_vertexBufferObject);
	glDeleteBuffers(1, &_elementBufferObject);
}


void TriangleMesh::finalize()
{
	glBindVertexArray(_vertexArrayObject);

	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER,
		_vertices.size() * sizeof(_vertices[0]),
		&_vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		_vertices.size() * sizeof(_indices[0]), &_indices[0], GL_STATIC_DRAW);

	//then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindVertexArray(0);
}

void TriangleMesh::render()
{
	glBindVertexArray(_vertexArrayObject);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}