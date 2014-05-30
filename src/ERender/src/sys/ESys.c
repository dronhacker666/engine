#include <sys/ESys.h>
#include <ELib.h>
#include <stdio.h>
#include <windows.h>
#include <pthread.h>


int ESys_getCoreAmount(void)
{
#if (defined __WIN32__)
	SYSTEM_INFO sysinfo;
	GetSystemInfo(&sysinfo);
	return sysinfo.dwNumberOfProcessors;
#endif
#if (defined __linux__)
	return sysconf(_SC_NPROCESSORS_ONLN);
#endif
}



typedef struct {
	const char* filename;
	void (*callback) (void*);
} ASYNCLOADFILE_DATA;

void* _asyncLoadFile(void* _data)
{
	FILE* fp;
	int size;
	char* content;
	ASYNCLOADFILE_DATA* data = _data;

	fp = fopen(data->filename, "rb");
	fseek(fp, 0, SEEK_END);
	size = ftell(fp);
	rewind(fp);
	content = EMem.alloc( sizeof(char)*size );
	fread(content, sizeof(char)*size , 1, fp);
	fclose(fp);
	content[size] = '\0';

	data->callback(content);
}

void asyncLoadFile(const char* filename, void (*callback) (void*))
{
	pthread_t t;
	ASYNCLOADFILE_DATA data = {
		filename,
		callback,
	};
	pthread_create(&t, NULL, _asyncLoadFile, &data);
}

_ESys ESys = {
	getCoreAmount: ESys_getCoreAmount,
};