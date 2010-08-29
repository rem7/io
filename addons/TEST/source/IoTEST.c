//metadoc CFFIPointer copyright 2006 Trevor Fancher. All rights reserved.
//metadoc CFFIPointer license BSD revised
//metadoc CFFIPointer category Bridges
//metadoc CFFIPointer description An Io interface to C

#include "IoTEST.h"
#include "IoSeq.h"
#include "IoNumber.h"
#include "IoObject.h"
#include "IoState.h"
#include <stdlib.h>
#include <string.h>

#define DATA(self) ((IoTESTData *)(IoObject_dataPointer(self)))
#define POINTER(data) ((data)->valuePointer)

void *IoTEST_null = NULL;

IoTag *IoTEST_newTag(void *state)
{
	IoTag *tag = IoTag_newWithName_("DataType");
	IoTag_state_(tag, state);
	IoTag_freeFunc_(tag, (IoTagFreeFunc *)IoTEST_free);
	IoTag_cloneFunc_(tag, (IoTagCloneFunc *)IoTEST_rawClone);
	//IoTag_markFunc_(tag, (IoTagMarkFunc *)IoTEST_mark);
	return tag;
}

IoTEST *IoTEST_proto(void *state)
{
	IoObject *self = IoObject_new(state);
	IoObject_tag_(self, IoTEST_newTag(state));

	IoObject_setDataPointer_(self, calloc(1, sizeof(IoTESTData)));
	memset(DATA(self), 0, sizeof(IoTESTData));
	DATA(self)->valuePointer = &(DATA(self)->type);

	IoState_registerProtoWithFunc_(state, self, IoTEST_proto);

	{
		IoMethodTable methodTable[] = {
			{"test", IoTEST_test},
			{NULL, NULL},
		};
		IoObject_addMethodTable_(self, methodTable);
	}

	return self;
}

IoTEST *IoTEST_rawClone(IoTEST *proto)
{
	IoObject *self = IoObject_rawClonePrimitive(proto);
	IoObject_setDataPointer_(self, calloc(1, sizeof(IoTESTData)));
	memset(DATA(self), 0, sizeof(IoTESTData));
	DATA(self)->valuePointer = &(DATA(self)->type);

	return self;
}

IoTEST *IoTEST_new(void *state)
{
	IoObject *proto = IoState_protoWithInitFunction_(state, IoTEST_proto);
	return IOCLONE(proto);
}

void IoTEST_free(IoTEST *self)
{
	IoTESTData *data;
	data = DATA(self);

	if ( data->needToFreeStr ) {
		free(data->type.str);
		data->needToFreeStr = 0;
	}
	free(DATA(self));
}

void IoTEST_mark(IoTEST *self)
{
}

/* ---------------------------------------------------------------- */

IoTEST *IoTEST_test(IoTEST *self, IoObject *locals, IoMessage *m)
{
	IoNumber *n = IoMessage_locals_valueArgAt_(m, locals, 0);
	IoSeq *s = IoMessage_locals_valueArgAt_(m, locals, 1);
	
	printf("n: %p %p\n", IoObject_tag(n)->cloneFunc, *(IoTagCloneFunc **)IoNumber_rawClone);
	printf("s: %p %p\n", IoObject_tag(s)->cloneFunc, (IoTagCloneFunc *)IoSeq_rawClone);
	printf("TEST: %p\n", IoTEST_rawClone);
	if(ISNUMBER(n)) {
		printf("is number\n");
		IoObject_print(n);
		return n;
	}
	else {
		printf("is NOT number\n");
		return IONIL(self);
	}
}

