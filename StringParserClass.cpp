/*
 * StringParserClass.cpp
 *
 *  Created on: Oct 8, 2017
 *      Author: keith
 */

#include <vector>
#include <string>
#include <string.h>
#include "../327_proj3_test/includes/StringParserClass.h"
#include "../327_proj3_test/includes/constants.h"

//dont forget to initialize member variables
KP_StringParserClass::StringParserClass::StringParserClass() {
	pEndTag = NULL;
	pStartTag = NULL;
	areTagsSet = false;
}

//call cleanup to release any allocated memory
KP_StringParserClass::StringParserClass::~StringParserClass(void) {
	cleanup();
}

//these are the start tag and the end tags that we want to find,
//presumably the data of interest is between them, please make a
//COPY of what pStartTag and pEndTag point to.  In other words
//DO NOT SET pStartTag = pStart
//returns:
//SUCCESS
//ERROR_TAGS_NULL if either pStart or pEnd is null
int KP_StringParserClass::StringParserClass::setTags(const char *pStart,
		const char *pEnd) {

	if (pStart == NULL || pEnd == NULL) {
		return ERROR_TAGS_NULL;
	}

	pEndTag = (char*) malloc(strlen(pStart) * sizeof(char));
	pStartTag = (char*) malloc(strlen(pEnd) * sizeof(char));

	strcpy(pStartTag, pStart);
	strcpy(pEndTag, pEnd);

	return SUCCESS;
}

//First clears myVector
//going to search thru pDataToSearchThru, looking for info bracketed by
//pStartTag and pEndTag, will add that info only to myVector
//returns
//SUCCESS  finished searching for data between tags, results in myVector (0 or more entries)
//ERROR_TAGS_NULL if either pStart or pEnd is null
//ERROR_DATA_NULL pDataToSearchThru is null
int KP_StringParserClass::StringParserClass::getDataBetweenTags(
		char *pDataToSearchThru, std::vector<std::string> &myVector) {

	myVector.clear();

	if (pStartTag == NULL || pEndTag == NULL) {
		return ERROR_TAGS_NULL;
	}

	if (pDataToSearchThru == NULL) {
		return ERROR_DATA_NULL;
	}

	char *startTagStartPtr = pDataToSearchThru;
	char *startTagEndPtr;

	char *endTagStartPtr = pDataToSearchThru;
	char *endTagEndPtr;

	while (findTag(pStartTag, startTagStartPtr, startTagEndPtr) == SUCCESS
			&& findTag(pEndTag, endTagStartPtr, endTagEndPtr) == SUCCESS) {
		std::string info = "";
		startTagEndPtr++;
		while (startTagEndPtr != endTagStartPtr) {
			info += *startTagEndPtr;
			startTagEndPtr++;
		}
		myVector.push_back(info);
		startTagStartPtr = endTagEndPtr++;
		endTagStartPtr = startTagStartPtr;
	}

	return SUCCESS;
}

void KP_StringParserClass::StringParserClass::cleanup() {

}

//Searches a string starting at pStart for pTagToLookFor
//returns:
//SUCCESS  found pTagToLookFor, pStart points to beginning of tag and pEnd points to end of tag
//FAIL did not find pTagToLookFor and pEnd points to 0
//ERROR_TAGS_NULL if either pStart or pEnd is null
int KP_StringParserClass::StringParserClass::findTag(char *pTagToLookFor,
		char *&pStart, char *&pEnd) {

	if (pStart == NULL || pEnd == NULL) {
		return ERROR_TAGS_NULL;
	}

	pEnd = pStart;

	while (*pEnd != '\0') {

		if (*pStart == *pTagToLookFor) {

			char *tempTag = pTagToLookFor;

			while (*pEnd == *tempTag) {
				tempTag++;
				if (*tempTag == '\0') {
					return SUCCESS;
				}
				pEnd++;
			}

		}

		pStart++;
		pEnd = pStart;

	}

	return FAIL;

}

