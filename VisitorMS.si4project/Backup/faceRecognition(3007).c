
#include "identityRecognition.h"




















struct identityRecognition faceRecognition = {
	.identityName = "faceRecognition",
	.flagRecognition = 0,

};








/* 头插法 */
struct identityRecognition *addFaceRecognitionToList(struct identityRecognition *phead)
{
	if (phead == NULL) {
		return &faceRecognition;
	} else {
		faceRecognition.next = phead;
		phead = &faceRecognition;
	}
}


