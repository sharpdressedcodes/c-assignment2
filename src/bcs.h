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
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <stdarg.h>

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

#define DRINK_LEN 1
#define PRICE_TOKEN_COUNT 2

/* Size of extra space for terminating strings with '\0' */
#define EXTRA_SPACE 1
/* This is used to compensate for the extra character spaces taken up by the
 *  '\n' and '\0' when user is asked for input through fgets(). */
#define EXTRA_SPACES 2
/* Used when creating dashes in output.
 * 3 = string\nstring\n\0
 * \n\n\0 */
#define EXTRA_SPACES_DASH 3

/* This specifies that there is no string minimum. */
#define MIN_STRING_NONE 0
/* This specifies that there is a string minimum. */
#define MIN_STRING 1
#define MIN_ARGS 3

#define MAX_STRING_SMALL 32
#define MAX_STRING_MEDIUM 256
#define MAX_STRING_LARGE 1024

/* This is used when using 1 based index instead of usual 0 based */
#define BASE1 1
/* Normal human number system is decimal which is base 10. This is used
 * when converting with strtol() */
#define BASE10 10

/* Menu starts at 1 and not 0 */
#define MIN_MENU_OPTION BASE1
#define MAX_MENU_OPTION 9

typedef enum {
    FALSE = 0,
    TRUE = 1
} BOOLEAN;

typedef BOOLEAN bool;
#define false FALSE
#define true TRUE
#define null NULL

/* Message shown to user when memory allocation fails (out of memory?). */
#define MESSAGE_ERROR_NO_MEMORY "Error: memory allocation failed.\n"
#define MESSAGE_ERROR_INVALID_ARGS "Error: You must enter 2 filenames!\n"
#define MESSAGE_ERROR_FILE_NOT_EXIST "Error: Filename %s does not exist!\n"
#define MESSAGE_ERROR_FILENAME_TOO_LONG "Error: Filename %s is too long! (max: %d)\n"
#define MESSAGE_ERROR_LOAD_DATA_FAIL "Error: Can't load data from file %s and %s\n"
#define MESSAGE_ERROR_INVALID_TOKEN "Error: %s token %s is invalid (index: %d)!\n"
#define MESSAGE_ERROR_CATEGORY_EXIST "Error: Category %s already exists!\n"
#define MESSAGE_ERROR_CATEGORY_NOT_EXIST "Error: Category %s doesn't exist!\n"
#define MESSAGE_ERROR_MENU_EXIST "Error: Item %s already exists!\n"
#define MESSAGE_ERROR_MENU_NOT_EXIST "Error: Item %s doesn't exist!\n"
#define MESSAGE_ERROR_INVALID_TOKEN_ARGS "Error: Invalid number of tokens. Read %d, expecting %d\n"

/* Menu Option Titles. */
#define MENU_TITLE_SUMMARY_HOT "Hot Drinks Summary"
#define MENU_TITLE_SUMMARY_COLD "Cold Drinks Summary"
#define MENU_TITLE_REPORT "Detailed Menu Report"
#define MENU_TITLE_ADD_CATEGORY "Add Menu Category"
#define MENU_TITLE_DELETE_CATEGORY "Delete Menu Category"
#define MENU_TITLE_ADD_ITEM "Add Menu Item"
#define MENU_TITLE_DELETE_ITEM "Delete Menu Item"
#define MENU_TITLE_EXIT "Save & Exit"
#define MENU_TITLE_ABORT "Abort"

/* Header Titles/ */
#define HEADER_TITLE_ID "ID"
#define HEADER_TITLE_NAME "Name"
#define HEADER_TITLE_SMALL "Small"
#define HEADER_TITLE_MEDIUM "Med"
#define HEADER_TITLE_LARGE "Large"

#define FORMAT_DASHED_HEADER_TITLE "%s Drinks Summary"
#define FORMAT_DASHED_HEADER_TOP1 "%s - %s (%d items)"
#define FORMAT_DASHED_HEADER_TOP2 "%-42s"
#define FORMAT_DASHED_HEADER_BOTTOM "   %-5s %-25s %-5s %-5s %-5s\n   "

#define FORMAT_ITEM "%8s %-25s"
#define FORMAT_PRICE " $%u.%02u"

#define TITLE_HOT "Hot"
#define TITLE_COLD "Cold"

#define SPACE_CHAR ' '
#define DASH_CHAR '-'
#define INPUT_SEPARATOR_CHAR '|'
#define PRICE_SEPARATOR_CHAR '.'
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






/* This structure defines the main menu options. */
typedef struct {

    /* index is the number shown to the user.
     * The user will select this number. */
    int index;

    /* str is the menu title shown to the user.
     * This is also used when retrieving an
     * element from the array. */
    const char* str;

    /* Track statistics for this method?
     * This is used in Session Summary. */
    /*bool tracked;*/

    /* This pointer points to the method that should be invoked when the user
     * selects this menu option. This effectively removes the need for a
     * switch statement  */
    /*void (*method)(int*);*/
    void (*method)(BCSType* menu, ...);
    /*void (*method)(...);*/

} menuoption_t;

typedef enum {
    eCategoryId,
    eCategoryType,
    eCategoryName,
    eCategoryDescription,
    eCategoryMax
} CategoryToken;

typedef enum {
    eMenuId,
    eMenuCategoryId,
    eMenuType,
    eMenuPrice1,
    eMenuPrice2,
    eMenuPrice3,
    eMenuDescription,
    eMenuMax
} MenuToken;

typedef enum {
    ePriceDollars,
    ePriceCents
} PriceToken;

typedef enum {
    eDrinkHot = HOT,
    eDrinkCold = COLD
} CategoryDrink;

typedef enum {
    eSortOrderAsIs,
    eSortOrderAscending,
    eSortOrderDescending
} SortOrder;

void exitApplication(int *abort);
menuoption_t *getMenuOptions();

#endif
