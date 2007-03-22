/*#io
docCopyright("Steve Dekorte", 2002)
docLicense("BSD revised")
*/

#ifndef IoCall_DEFINED
#define IoCall_DEFINED 1

#include "Common.h"
#include "IoState.h"

#ifdef __cplusplus
extern "C" {
#endif

#define ISACTIVATIONCONTEXT(self) IoObject_hasCloneFunc_(self, (IoTagCloneFunc *)IoCall_rawClone)

typedef IoObject IoCall;

typedef struct
{
	IoObject *sender;
	IoObject *message;
	IoObject *target;
	IoObject *slotContext;
	IoObject *activated;
	IoObject *coroutine;
        int stopStatus;
} IoCallData;

IoCall *IoCall_with(void *state, 
									 IoObject *sender,
									 IoObject *target,
									 IoObject *message,
									 IoObject *slotContext,
									 IoObject *activated,
									 IoObject *coroutine);

IoCall *IoCall_proto(void *state);
IoCall *IoCall_rawClone(IoCall *self);
IoCall *IoCall_new(IoState *state);

void IoCall_mark(IoCall *self);
void IoCall_free(IoCall *self);

void IoCall_writeToStream_(IoCall *self, BStream *stream);
void IoCall_readFromStream_(IoCall *self, BStream *stream);

IoObject *IoCall_sender(IoObject *self, IoObject *locals, IoMessage *m);
IoObject *IoCall_message(IoObject *self, IoObject *locals, IoMessage *m);
IoObject *IoCall_target(IoObject *self, IoObject *locals, IoMessage *m);
IoObject *IoCall_slotContext(IoObject *self, IoObject *locals, IoMessage *m);
IoObject *IoCall_activated(IoObject *self, IoObject *locals, IoMessage *m);
IoObject *IoCall_coroutine(IoObject *self, IoObject *locals, IoMessage *m);
IoObject *IoCall_evalArgAt(IoObject *self, IoObject *locals, IoMessage *m);
IoObject *IoCall_argAt(IoObject *self, IoObject *locals, IoMessage *m);

int IoCall_rawStopStatus(IoObject *self);
IoObject *IoCall_stopStatus(IoObject *self, IoObject *locals, IoMessage *m);
IoObject *IoCall_setStopStatus(IoObject *self, IoObject *locals, IoMessage *m);

#ifdef __cplusplus
}
#endif
#endif