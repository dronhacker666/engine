#include "ModelLoader.h"

const Model_p loadOBJ(const char* filename)
{
	char buffer[1024];
	unsigned int size;
	FILE* fp;

	if (NULL == (fp = fopen(filename, "r"))){
		return false;
	}

	float tf[8];
	int ti[9];
	EArrayInstance_p vertex = EArray.create(sizeof(float)*3);
	EArrayInstance_p texcoord = EArray.create(sizeof(float)*2);
	EArrayInstance_p normals = EArray.create(sizeof(float)*3);

	EArrayInstance_p res = EArray.create(sizeof(float)*8);

	bool hasTexcoord = false;
	bool hasNormals = false;

	while( fgets(buffer, 1024, fp) ){

		switch(buffer[0]){
			case 'm':

			break;
			case 'o':

			break;
			case 'v':
				switch(buffer[1]){
					case ' ': // vertext position
						sscanf(buffer, "v %f %f %f", &tf[0], &tf[1], &tf[2]);
						EArray.push(vertex, tf);
					break;
					case 't': // texcoord
						hasTexcoord = true;

						sscanf(buffer, "vt %f %f", &tf[0], &tf[1]);
						EArray.push(texcoord, tf);
					break;
					case 'n': // normal
						hasNormals = true;

						sscanf(buffer, "vn %f %f %f", &tf[0], &tf[1], &tf[2]);
						EArray.push(normals, tf);
					break;
				}
			break;
			case 'u':

			break;
			case 'f':

				if(hasTexcoord && hasNormals){
					sscanf(buffer, "f %i/%i/%i %i/%i/%i %i/%i/%i", &ti[0],&ti[1],&ti[2],&ti[3],&ti[4],&ti[5],&ti[6],&ti[7],&ti[8]);

					memcpy(&tf[0], EArray.get(vertex, ti[0]-1), sizeof(float)*3);
					memcpy(&tf[3], EArray.get(texcoord, ti[1]-1), sizeof(float)*2);
					memcpy(&tf[5], EArray.get(normals, ti[2]-1), sizeof(float)*3);
					EArray.push(res, tf);

					memcpy(&tf[0], EArray.get(vertex, ti[3]-1), sizeof(float)*3);
					memcpy(&tf[3], EArray.get(texcoord, ti[4]-1), sizeof(float)*2);
					memcpy(&tf[5], EArray.get(normals, ti[5]-1), sizeof(float)*3);
					EArray.push(res, tf);

					memcpy(&tf[0], EArray.get(vertex, ti[6]-1), sizeof(float)*3);
					memcpy(&tf[3], EArray.get(texcoord, ti[7]-1), sizeof(float)*2);
					memcpy(&tf[5], EArray.get(normals, ti[8]-1), sizeof(float)*3);
					EArray.push(res, tf);
				}
				else if(hasTexcoord){
					sscanf(buffer, "f %i/%i %i/%i %i/%i", &ti[0],&ti[1],&ti[2],&ti[3],&ti[4],&ti[5]);

					memcpy(&tf[0], EArray.get(vertex, ti[0]-1), sizeof(float)*3);
					memcpy(&tf[3], EArray.get(texcoord, ti[1]-1), sizeof(float)*2);
					EArray.push(res, tf);

					memcpy(&tf[0], EArray.get(vertex, ti[2]-1), sizeof(float)*3);
					memcpy(&tf[3], EArray.get(texcoord, ti[3]-1), sizeof(float)*2);
					EArray.push(res, tf);

					memcpy(&tf[0], EArray.get(vertex, ti[4]-1), sizeof(float)*3);
					memcpy(&tf[3], EArray.get(texcoord, ti[5]-1), sizeof(float)*2);
					EArray.push(res, tf);
				}
				else if(hasNormals){
					sscanf(buffer, "f %i//%i %i//%i %i//%i", &ti[0],&ti[1],&ti[2],&ti[3],&ti[4],&ti[5]);

					memcpy(&tf[0], EArray.get(vertex, ti[0]-1), sizeof(float)*3);
					memcpy(&tf[5], EArray.get(normals, ti[1]-1), sizeof(float)*3);
					EArray.push(res, tf);

					memcpy(&tf[0], EArray.get(vertex, ti[2]-1), sizeof(float)*3);
					memcpy(&tf[5], EArray.get(normals, ti[3]-1), sizeof(float)*3);
					EArray.push(res, tf);

					memcpy(&tf[0], EArray.get(vertex, ti[4]-1), sizeof(float)*3);
					memcpy(&tf[5], EArray.get(normals, ti[5]-1), sizeof(float)*3);
					EArray.push(res, tf);
				}
				else{
					sscanf(buffer, "f %i %i %i", &ti[0],&ti[1],&ti[2]);

					memcpy(&tf[0], EArray.get(vertex, ti[0]-1), sizeof(float)*3);
					EArray.push(res, tf);

					memcpy(&tf[0], EArray.get(vertex, ti[1]-1), sizeof(float)*3);
					EArray.push(res, tf);

					memcpy(&tf[0], EArray.get(vertex, ti[2]-1), sizeof(float)*3);
					EArray.push(res, tf);
				}

			break;
		}

	}

	EArray.free(vertex);
	EArray.free(texcoord);
	EArray.free(normals);

	Model_p model = EMem.alloc(sizeof(Model));
	model->vertexCount = res->length;
	model->mesh = res->_data;

	EMem.free(res);

	return model;
}
