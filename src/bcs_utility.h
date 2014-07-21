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

#endif
