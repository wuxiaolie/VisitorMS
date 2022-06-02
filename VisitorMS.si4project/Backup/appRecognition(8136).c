
#include "identityRecognition.h"



















struct identityRecognition appRecognition = {
	.identityName = "appRecognition",
	.flagRecognition = 0,





	
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



