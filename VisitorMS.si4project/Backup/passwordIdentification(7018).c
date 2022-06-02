
#include "identityRecognition.h"



struct identityRecognition passwordRecognition = {

};

/* 头插法 */
struct identityRecognition *addPasswordRecognitionToList(struct identityRecognition *phead)
{
	if (phead == NULL) {
		return &passwordRecognition;
	} else {
		passwordRecognition.next = phead;
		phead = &passwordRecognition;
	}
}

