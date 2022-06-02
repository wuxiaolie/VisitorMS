
#include "identityRecognition.h"



struct identityRecognition appRecognition = {

};

/* 头插法 */
struct identityRecognition *addAppRecognitionToList(struct identityRecognition *phead)
{
	if (phead == NULL) {
		return &appRecognition;
	} else {
		appRecognition.next = phead;
		phead = &appRecognition;
	}
}



