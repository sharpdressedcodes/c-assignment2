/****************************************************************************
* COSC2138/CPT220 - Programming Principles 2A
* Study Period  2 2014 Assignment #2 - Brazilian Coffee Shop system
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Start up code provided by the CTEACH team
****************************************************************************/

#ifndef BCS_OPTIONS_H
#define BCS_OPTIONS_H

/* Function prototypes. */
void displaySummary(BCSType* menu, char drinkType);
void categoryReport(BCSType* menu);
void addCategory(BCSType* menu);
void deleteCategory(BCSType* menu);
void addItem(BCSType* menu);
void deleteItem(BCSType* menu);
void saveData(BCSType* menu, char* menuFile, char* submenuFile);

#endif
