#pragma once
#include "../Utilities/utilities.h"
#include "Vertex.h"

class Model
{
public:
	Model();
	~Model();
	bool LoadModel(char* fileName);
	GLuint& getVBO();
	GLuint& getIBO();
	void BufferIBO();
	void BufferVBO();
	static Model* GetInstance();
	int getVertices();
	int getIndices();
	Vertex* GetVerticesData();
private:
	int n_Vertices, n_Indices;
	GLuint vboId;
	GLuint iboId;
	Vertex* verticesData;
	int* indicesData;
	static Model* s_Instance;
};

