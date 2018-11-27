#include "TriangleMesh.h"
#include <glad/glad.h>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>


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

unsigned int				_uvBufferObject = 0;
unsigned int				_uvElementBufferObject = 0;

void TriangleMesh::create()
{
	return _create2();

	//^^^^^^^^
	// WHY IS IT NOT WORKING ?!
 
	if (_created) {
		return;
	}
	/////////////////////////////////////////////////////
	glBindVertexArray(_vertexArrayObject);


	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER,
		_vertices.size() * sizeof(_vertices[0]),
		&_vertices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		_vertexIndices.size() * sizeof(_vertexIndices[0]), &_vertexIndices[0], GL_STATIC_DRAW);

	//then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	
	glBindBuffer(GL_ARRAY_BUFFER, _uvBufferObject);
	glBufferData(GL_ARRAY_BUFFER,
		_uvs.size() * sizeof(_uvs[0]),
		&_uvs[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _uvElementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		_uvIndices.size() * sizeof(_uvIndices[0]), &_uvIndices[0], GL_STATIC_DRAW);

	//then set our vertex attributes pointers
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(1);
	

	glBindVertexArray(0);

	_created = true;
}

void TriangleMesh::_create2()
{
	if (_created)
		return;

	/////////////////////////////////////////////////////
	glBindVertexArray(_vertexArrayObject);

	std::vector<float> bufferData;

	bufferData.insert(bufferData.end(), _vertices.begin(), _vertices.end());
	bufferData.insert(bufferData.end(), _uvs.begin(), _uvs.end());

	glBindBuffer(GL_ARRAY_BUFFER, _vertexBufferObject);
	glBufferData(GL_ARRAY_BUFFER,
		bufferData.size() * sizeof(bufferData[0]),
		&bufferData[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _elementBufferObject);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,
		_vertexIndices.size() * sizeof(_vertexIndices[0]), &_vertexIndices[0], GL_STATIC_DRAW);

	//then set our vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	//then set our vertex attributes pointers
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)(_vertices.size() * sizeof(float)));
	glEnableVertexAttribArray(1);


	glBindVertexArray(0);

	_created = true;
}


void TriangleMesh::setTexture(const std::string& path)
{
	//load image
	int width, height, nrChannels;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrChannels, 0);

	//gen texture
	GLuint texture;
	glGenTextures(1, &texture);

	//
	glBindTexture(GL_TEXTURE_2D, texture);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);

	//
	stbi_image_free(data);
	
	///



}



void TriangleMesh::render()
{
	create();

	glBindVertexArray(_vertexArrayObject);

	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}