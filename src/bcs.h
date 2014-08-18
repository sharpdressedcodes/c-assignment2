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
#include <time.h>

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
#define MESSAGE_ERROR_INVALID_PRICE "Error: price is invalid!\n"
#define MESSAGE_ERROR_INVALID_CATEGORY_TYPE "Error: Invalid Category Type.\n"
#define MESSAGE_ERROR_CATEGORY_EXIST "Error: Category %s already exists!\n"
#define MESSAGE_ERROR_CATEGORY_NOT_EXIST "Error: Category %s doesn't exist!\n"
#define MESSAGE_ERROR_MENU_EXIST "Error: Item %s already exists!\n"
#define MESSAGE_ERROR_MENU_NOT_EXIST "Error: Item %s doesn't exist!\n"
#define MESSAGE_ERROR_INVALID_TOKEN_ARGS "Error: Invalid number of tokens. Read %d, expecting %d\n"
#define MESSAGE_ERROR_ARG_CATEGORY_ORDER "Error: You must have the menu file as #%d command-line arg.\n"
#define MESSAGE_ERROR_ARG_ITEM_ORDER "Error: You must have the sub menu file as #%d command-line arg.\n"
#define MESSAGE_DELETE_CATEGORY "Warning: All menu data for a menu category will be deleted if you proceed.\n"
#define MESSAGE_DELETED_CATEGORY "Category \"%s - %s\" deleted from the system.\n"
#define MESSAGE_DELETED_ITEM "Item \"%s - %s\" deleted from the system.\n"
#define MESSAGE_CREATED_REPORT "File %s.report has been created.\n"

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

#define INPUT_CATEGORY_ID "Category ID (%d characters): "
#define INPUT_ITEM_ID "Item ID (%d characters): "
#define INPUT_NEW_CATEGORY_ID "New Category ID is: "
#define INPUT_NEW_ITEM_ID "New Item ID is: "
#define INPUT_CATEGORY_NAME "Category Name (%d-%d characters): "
#define INPUT_CATEGORY_TYPE "(H)ot or (C)old drink?: "
#define INPUT_DESCRIPTION "Description (%d-%d characters): "
#define INPUT_ITEM_NAME "Item name (%d-%d characters): "
#define INPUT_ITEM_PRICE_SMALL "Small Price (%c%s-%c%s): "
#define INPUT_ITEM_PRICE_MEDIUM "Medium Price (%c%s-%c%s): "
#define INPUT_ITEM_PRICE_LARGE "Large Price (%c%s-%c%s): "

#define FORMAT_DASHED_HEADER_TITLE "%s Drinks Summary"
#define FORMAT_DASHED_HEADER_TOP1 "%s - %s (%d items)"
#define FORMAT_DASHED_HEADER_TOP2 "%-42s"
#define FORMAT_DASHED_HEADER_BOTTOM "   %-5s %-25s %-5s %-5s %-5s\n   "

#define FORMAT_DASHED_HEADER_REPORT "Category %s - %s - Detailed Report"
#define TITLE_REPORT_ITEM_ID "Item ID"
#define TITLE_REPORT_ITEM_NAME "Item Name"
#define TITLE_REPORT_ITEM_PRICES "Prices"
#define TITLE_REPORT_ITEM_DESCRIPTION "Description"

#define FORMAT_ITEM "%8s %-25s"
#define FORMAT_PRICE " $%u.%02u"
#define FORMAT_REPORT_NAME "../%s.report"

#define TITLE_HOT "Hot"
#define TITLE_COLD "Cold"

#define SPACE_CHAR ' '
#define DASH_CHAR '-'
#define INPUT_SEPARATOR_CHAR '|'
#define PRICE_SEPARATOR_CHAR '.'
#define CATEGORY_PREFIX_CHAR 'C'
#define ITEM_PREFIX_CHAR 'I'
#define CURRENCY_CHAR '$'

#define EXPECTED_CATEGORY_ARG_INDEX 1
#define EXPECTED_ITEM_ARG_INDEX EXPECTED_CATEGORY_ARG_INDEX + 1

#define DEFAULT_SORT_ORDER eSortOrderAscending

#define RANDOM_ID_MIN 1
#define RANDOM_ID_MAX 9999

#define MIN_ITEM_PRICE "0.05"
#define MAX_ITEM_PRICE "9.95"

#define PRICE_LEN 4
#define DOLLARS_LEN 1
#define CENTS_LEN 2

#define WORD_WRAP_LIMIT 78

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

typedef enum {
    eMethodDisplayHot = MIN_MENU_OPTION,
    eMethodDisplayCold,
    eMethodReport,
    eMethodAddCategory,
    eMethodDeleteCategory,
    eMethodAddItem,
    eMethodDeleteItem,
    eMethodSaveData,
    eMethodExitApp
} Methods;

#endif
