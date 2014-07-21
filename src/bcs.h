/****************************************************************************
* COSC2138/CPT220 - Programming Principles 2A
* Study Period  2  2014 Assignment #2 - Brazilian Coffee Shop  system
* Full Name        : EDIT HERE
* Student Number   : EDIT HERE
* Start up code provided by the CTEACH team
****************************************************************************/


#ifndef BCS_H
#define BCS_H

/* System-wide header files. */
#include <stdio.h>
#include <stdlib.h>

/* Custom system-wide header files. */
#include <string.h>

/* System-wide constants. */
#define ID_LEN 5
#define MIN_NAME_LEN 1
#define MAX_NAME_LEN 25
#define MIN_DESC_LEN 1
#define MAX_DESC_LEN 250
#define NUM_PRICES 3
#define HOT 'H'
#define COLD 'C'


/* Custom Types */
#define MIN_ARGS 3
#define MAX_STRING_MEDIUM 256

typedef enum {
    FALSE = 0,
    TRUE = 1
} BOOLEAN;

typedef BOOLEAN bool;
#define false FALSE
#define true TRUE
#define null NULL

#define MESSAGE_ERROR_INVALID_ARGS "Error: You must enter 2 filenames after this executable's name\n"
#define MESSAGE_ERROR_FILE_NOT_EXIST "Error: Filename %s does not exist!\n"
#define MESSAGE_ERROR_FILENAME_TOO_LONG "Error: Filename %s is too long!\n"
/* End Custom Types */





typedef struct category* CategoryTypePtr;
typedef struct item* ItemTypePtr;

/* Structure definitions. */
typedef struct price
{
   unsigned dollars;
   unsigned cents;
} PriceType;

typedef struct item
{
   char itemID[ID_LEN + 1];
   char itemName[MAX_NAME_LEN + 1];
   PriceType prices[NUM_PRICES];
   char itemDescription[MAX_DESC_LEN + 1];
   ItemTypePtr nextItem;
} ItemType;

typedef struct category
{
   char categoryID[ID_LEN + 1];
   char categoryName[MAX_NAME_LEN + 1];
   char drinkType;      /* (H)ot or (C)old. */
   char categoryDescription[MAX_DESC_LEN + 1];
   CategoryTypePtr nextCategory;
   ItemTypePtr headItem;
   unsigned numItems;
} CategoryType;

typedef struct bcs
{
   CategoryTypePtr headCategory;
   unsigned numCategories;
} BCSType;

#endif
