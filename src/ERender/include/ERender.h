#ifndef erender_h
#define erender_h

// INCLUDES
#include "../../ELib/include/ELib.h"

// TYPES
typedef int ERenderHandler;
typedef EArray EScene;

typedef struct {
	int width;
	int height;
	char* title;
} ERenderCreateOptions;

typedef struct {
	EScene* scene;
	int viewport_x;
	int viewport_y;
	int viewport_width;
	int viewport_height;
} ERenderInstance;

// API
typedef struct {
	bool 	(*create)		(ERenderCreateOptions*);
	void 	(*render)		(void);
	void 	(*setScene)		(EScene*);
	EScene* (*createScene)	(void);
} _ERender;
extern _ERender ERender;

#endif