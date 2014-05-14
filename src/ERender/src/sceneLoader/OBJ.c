#include "SceneLoader.h"

EArrayInstance_p vertex;
EArrayInstance_p texcoord;
EArrayInstance_p normals;

MeshInfo_p readMesh(FILE* fp)
{
	MeshInfo_p mesh = EMem.alloc(sizeof(MeshInfo));
	EArrayInstance_p res = EArray.create(sizeof(float)*8);
	char buffer[1024];
	float tf[8];
	int ti[9];
	fpos_t startStrPos;
	bool hasTexcoord = false;
	bool hasNormals = false;
	int size;

	while( fgets(buffer, 1024, fp) )
	{
		switch(buffer[0]){
			case 'o':
				if(res->length==0){
					// store object name
					size = strlen(buffer+2);
					mesh->name = EMem.alloc(size);
					memcpy(mesh->name, buffer+2, size);
					mesh->name[size-1] = '\0';
				}else{
					fsetpos(fp, &startStrPos);
					goto END;
				}
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
		fgetpos(fp, &startStrPos);
	}

	END:

	mesh->vertexCount = res->length;
	mesh->mesh = EArray.getData(res);

	EArray.free(res);

	return mesh;
}



const SceneInfo_p loadOBJ(const char* filename)
{

	EArrayInstance_p meshes = EArray.create(sizeof(MeshInfo));

	vertex = EArray.create(sizeof(float)*3);
	texcoord = EArray.create(sizeof(float)*2);
	normals = EArray.create(sizeof(float)*3);

	FILE* fp;
	char buffer[1024];
	fpos_t startStrPos = 0;

	if (NULL == (fp = fopen(filename, "rb"))){
		return false;
	}

	while( fgets(buffer, 1024, fp) )
	{
		switch(buffer[0]){
			case 'm':

			break;
			case 'o':
			case 'v':
				fsetpos(fp, &startStrPos);
				EArray.push(meshes, readMesh(fp));
			break;
		}
		fgetpos(fp, &startStrPos);
	}

	EArray.free(vertex);
	EArray.free(texcoord);
	EArray.free(normals);

	SceneInfo_p scene = EMem.alloc(sizeof(SceneInfo));
	scene->meshes = EArray.getData(meshes);
	scene->meshCount = meshes->length;
	EArray.free(meshes);

	return scene;
}
