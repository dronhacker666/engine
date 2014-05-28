#include <render/ERenderGroup.h>

ERenderGroupInstance_p ERenderGroup_create(void)
{
	ERenderGroupInstance_p group = EMem.alloc(sizeof(ERenderGroupInstance));
	group->type = ERENDEROBJECTTYPE_GROUP;
	group->child = EList.create();
	return group;
}

_ERenderGroup ERenderGroup = {
	create: ERenderGroup_create,
};