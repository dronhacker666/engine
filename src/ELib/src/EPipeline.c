#include "ELib.h"

EPipelineInstance_p EPipeline_create(const int item_size, const int length)
{
	EPipelineInstance_p pipeline = EMem.alloc(sizeof(EPipelineInstance)+item_size*length);

	pipeline->_data = pipeline + sizeof(EPipelineInstance);
	pipeline->item_size = item_size;
	pipeline->length = length;

	return pipeline;
}

void EPipeline_push(EPipelineInstance_p pipeline, const void* data)
{
	if(pipeline->pos >= pipeline->length){
		pipeline->pos = 0;
	}
	pipeline->count_filed_items = pipeline->count_filed_items<=pipeline->length ? pipeline->count_filed_items+1 : pipeline->length;
	memcpy( pipeline->_data+(pipeline->item_size*pipeline->pos), data, pipeline->item_size );
	pipeline->pos++;
}

void* EPipeline_get(EPipelineInstance_p pipeline, int offset)
{
	if(abs(offset)>=pipeline->count_filed_items){
		printf("EPipeline error\n");
	}
	return pipeline->_data + ((pipeline->length + pipeline->pos - 1 - offset%pipeline->length)%pipeline->length) * pipeline->item_size;
}

_EPipeline EPipeline = {
	create: EPipeline_create,
	push: EPipeline_push,
	get: EPipeline_get,
};