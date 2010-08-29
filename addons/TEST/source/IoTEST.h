//metadoc CFFIPointer copyright 2006 Trevor Fancher. All rights reserved.
//metadoc CFFIPointer license BSD revised
//metadoc CFFIPointer category Bridges
//metadoc CFFIPointer description An Io interface to C

#ifndef IoTEST_DEFINED
#define IoTEST_DEFINED 1

#include "IoObject.h"

#define ISTEST(self) IoObject_hasCloneFunc_(self, (IoTagCloneFunc *)IoTEST_rawClone)

typedef IoObject IoTEST;

typedef struct {
	union {
		char		c;
		unsigned char	C;
		short		s;
		unsigned short	S;
		int		i;
		unsigned int	I;
		long		l;
		unsigned long	L;
		long long		g;
		unsigned long long	G;
		float		f;
		double		d;
		char		*str;
	}			type;
	int			needToFreeStr;
	void			*valuePointer;
} IoTESTData;

IoTag		*IoTEST_newTag(void *state);
IoTEST	*IoTEST_proto(void *state);
IoTEST	*IoTEST_rawClone(IoTEST *self);
IoTEST	*IoTEST_new(void *state);
void		IoTEST_free(IoTEST *self);
void		IoTEST_mark(IoTEST *self);

IoTEST *IoTEST_test(IoTEST *self, IoObject *locals, IoMessage *m);

#endif
