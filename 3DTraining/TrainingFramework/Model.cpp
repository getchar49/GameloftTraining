#include "stdafx.h"
#include "Model.h"

Model* Model::s_Instance = NULL;



Model::Model()
{

}

Model* Model::GetInstance() {
	if (!s_Instance) {
		s_Instance = new Model;
	}
	return s_Instance;
}


Model::~Model()
{
	if (verticesData) {
		delete[] verticesData; verticesData = NULL;
	}
	if (indicesData) {
		delete[] indicesData; indicesData = NULL;
	}
}

GLuint& Model::getIBO() {
	return this->iboId;
}

GLuint& Model::getVBO() {
	return this->vboId;
}

int Model::getVertices() {
	return this->n_Vertices;
}
int Model::getIndices() {
	return this->n_Indices;
}

bool Model::LoadModel(char* fileName) {
	char s[50];
	//Vertex *verticesData;
	FILE* f = fopen(fileName, "r");
	if (!f) return false;
	fscanf(f, "%s", s);
	if (strcmp(s, "NrVertices:") == 0) {
		//printf("asdad\n");
		fscanf(f, "%d", &n_Vertices);
		verticesData = new Vertex[n_Vertices];
		int id;
		for (int i = 0; i < n_Vertices; i++) {
			fscanf(f, "%d", &id);
			fscanf(f, ". pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f,%f];", &verticesData[id].pos.x, &verticesData[id].pos.y, &verticesData[id].pos.z, &verticesData[id].normal.x, &verticesData[id].normal.y, &verticesData[id].normal.z, &verticesData[id].binormal.x, &verticesData[id].binormal.y, &verticesData[id].binormal.z, &verticesData[id].tangent.x, &verticesData[id].tangent.y, &verticesData[id].tangent.z, &verticesData[id].uv.x, &verticesData[id].uv.y);
		}
//		printf("%f %f %f\n", verticesData[511].pos.x, verticesData[511].pos.y, verticesData[511].pos.z);
	}
	//int *indicesData;
	fscanf(f, "%s", s);
	if (strcmp(s, "NrIndices:") == 0) {
		fscanf(f, "%d", &n_Indices);
		indicesData = new int[n_Indices];
		for (int i = 0; i < n_Indices; i++) {
			int id;
			fscanf(f, "%d", &id);
			fscanf(f, ". %d, %d, %d", &(indicesData[id * 3]), &(indicesData[id * 3 + 1]), &(indicesData[id * 3 + 2]));

		}
	//	printf("%d %d %d\n", indicesData[2151], indicesData[2152], indicesData[2153]);
	}
	fclose(f);
	
	return true;
}

void Model::BufferVBO() {
	glGenBuffers(1, &vboId);
	glBindBuffer(GL_ARRAY_BUFFER, vboId);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex)*n_Vertices, verticesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Model::BufferIBO() {
	glGenBuffers(1, &iboId);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, iboId);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int)*n_Indices, indicesData, GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Vertex* Model::GetVerticesData() {
	return this->verticesData;
}
