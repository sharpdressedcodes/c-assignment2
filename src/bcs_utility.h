/****************************************************************************
* COSC2138/CPT220 - Programming Principles 2A
* Study Period  2 2014 Assignment #2 - Brazilian Coffee Shop system
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Start up code provided by the CTEACH team
****************************************************************************/

#ifndef BCS_UTILITY_H
#define BCS_UTILITY_H

/* Function prototypes. */
void readRestOfLine();
void systemInit(BCSType* menu);
int loadData(BCSType* menu, char* menuFile, char* submenuFile);
void systemFree(BCSType* menu);


/* Custom */
bool fileExists(const char *fileName);
bool getIntegerFromStdIn(int *result, const int length, const char *message,
        const int min, const int max, bool showError, bool allowEmpty);
bool getStringFromStdIn(char *result, const int length, const char *message,
        const int min, bool showError);
bool allocateString(char **str, const int size);
void freeString(char **str);
void freeStringArray(char **arr, const int length);
void freeStrings(const int length, ...);
char *createDashes(const char *str);
menuoption_t *getMenuOptionByIndex(const int index);
menuoption_t *getMenuOptionByTitle(const char *title);
#endif
