
#include "identityRecognition.h"






















struct identityRecognition passwordRecognition = {
	.identityName = "passwordRecognition",
	.flagRecognition = 0,

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

