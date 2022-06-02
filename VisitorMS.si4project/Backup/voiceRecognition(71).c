
#include "identityRecognition.h"



struct identityRecognition voiceRecognition = {

};

/* 头插法 */
struct identityRecognition *addVoiceRecognitionToList(struct identityRecognition *phead)
{
	if (phead == NULL) {
		return &voiceRecognition;
	} else {
		voiceRecognition.next = phead;
		phead = &voiceRecognition;
	}
}

