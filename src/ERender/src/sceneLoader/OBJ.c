#include "SceneLoader.h"

EArrayInstance_p vertex;
EArrayInstance_p texcoord;
EArrayInstance_p normals;

EHashInstance_p mtl;

bool hasTexcoord = false;
bool hasNormals = false;

void filePath(char* out, const char* filename)
{
	int length = strlen(filename);
	char* ch = filename + length-1;
	while(*ch != '/') ch--;
	memcpy(out, filename, ch-filename+1);
	out[ch-filename+1] = '\0';
}

void fixStr(char* str){
	char* ch = str;
	while(*ch!='\0' && *ch!='\n' && *ch!='\r') ch++;
	*ch = '\0';
}

void readMesh(ERenderSceneInstance_p scene, FILE* fp)
{
	ERenderModelInstance_p model = ERenderModel.create();
	EArrayInstance_p res = EArray.create(sizeof(float)*8);
	char buffer[1024];
	float tf[8];
	int ti[9];
	fpos_t startStrPos;
	int size;

	while( fgets(buffer, 1024, fp) )
	{
		fixStr(buffer);
		switch(buffer[0]){
			case 'o':
				if(res->length==0){
					// store object name
					size = strlen(buffer+2);
					model->name = EMem.clone(buffer+2, size);
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
				if(memcmp(buffer, "usemtl", 6)==0){
					model->mtl = EHash.get1p(mtl, buffer+7);
				}
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

	ERenderModel.loadMesh(model, res->length, res->_data);
	EArray.free(res);

	ERenderScene_addObject(scene, (ERenderObjectInstance_p)model);
}

void readMtl(const char* filename)
{
	FILE* fp;
	char buffer[1024];
	char path[1024];
	char current_mtl[128];
	ERenderMaterialInstance_p material;

	if (NULL == (fp = fopen(filename, "rb"))){
		return;
	}
	while( fgets(buffer, 1024, fp) )
	{
		fixStr(buffer);
		switch(buffer[0]){
			case 'n':
				if(memcmp(buffer, "newmtl", 6)==0){
					strcpy(current_mtl, buffer+7);
					material = ERenderMaterial.create();
					EHash.set1p(mtl, current_mtl, material);
				}
			break;
			case 'm':
				if(memcmp(buffer, "map_Kd", 6)==0){
					filePath(path, filename);
					strcat(path, buffer+7);
					ERenderMaterial.loadTexture(material, path, 0);
				}
			break;
		}
	}
}

bool SceneLoader_loadOBJ(ERenderSceneInstance_p scene, const char* filename)
{
	vertex = EArray.create(sizeof(float)*3);
	texcoord = EArray.create(sizeof(float)*2);
	normals = EArray.create(sizeof(float)*3);

	mtl = EHash.create();

	FILE* fp;
	char buffer[1024];
	fpos_t startStrPos = 0;

	if (NULL == (fp = fopen(filename, "rb"))){
		return false;
	}

	while( fgets(buffer, 1024, fp) )
	{
		fixStr(buffer);
		switch(buffer[0]){
			case 'm':
				if(memcmp(buffer, "mtllib", 6)==0){
					char path[1024];
					filePath(path, filename);
					strcat(path, buffer+7);
					readMtl( path );
				}
			break;
			case 'o':
			case 'v':
				fsetpos(fp, &startStrPos);
				readMesh(scene, fp);
			break;
		}
		fgetpos(fp, &startStrPos);
	}

	EArray.free(vertex);
	EArray.free(texcoord);
	EArray.free(normals);

	EHash.free(mtl);

	return true;
}
