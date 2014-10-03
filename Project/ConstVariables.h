#pragma once
// Normal
#define INPUT_START ">"
#define INPUT_END "\n";
#define OUTPUT_BLANK " ";
#define OUTPUT_DOUBLE_QUOTES "\""
#define TYPE_NODE_NAME "Node"
#define TYPE_ROOT_NAME "Root"
#define PRINT_ACTION_END "---------------------------------------------------------"

//Menu Description
#define MENU_DESCRIPTION "Please enter your choice:"
#define MENU_CHOICE_1_DESCRIPTION "1. Create a new mind map"
#define MENU_CHOICE_2_DESCRIPTION "2. Insert a new node"
#define MENU_CHOICE_3_DESCRIPTION "3. Display mind map"
#define MENU_CHOICE_4_DESCRIPTION "4. Save mind map"
#define MENU_CHOICE_5_DESCRIPTION "5. Exit"

// Menu Choice
#define	CREATE_NEW_MIND_MAP "1"
#define INSERT_NEW_NODE "2"
#define DISPLAY_MIND_MAP "3"
#define SAVE_MIND_MAP "4"
#define EXIT "5"

// Create New Mind Map
#define CREATE_NEW_MIND_MAP_DESCRIPTION "Please enter the topic:"

// Insert Menu Description
#define ENTER_NODE_ID "Enter the node ID:"
#define INSERT_MENU_CHOICE_1_DESCRIPTION "a. Insert a parent node"
#define INSERT_MENU_CHOICE_2_DESCRIPTION "b. Insert a child node"
#define INSERT_MENU_CHOICE_3_DESCRIPTION "c. Insert a sibling node"
#define ENTER_NODE_NAME "Enter the node name:"

// Insert Menu Choice
#define INSERT_PARENT_NODE "a"
#define INSERT_CHILD_NODE "b"
#define INSERT_SIBLING_NODE "c"

// Save
#define SAVE_SUCCESS "Save MindMap Success"

// Print MindMap
#define PRINT_MIND_MAP_DESCRIPTION "The mind map %s is displayed as follows:"
#define PRINT_MIND_MAP_DESCRIPTION_START "The mind map "
#define PRINT_MIND_MAP_DESCRIPTION_END " is desplayed as follows:"
#define PRINT_MAP_BLANK "¡@¡@"
#define PRINT_MAP_LINE "¡U¡@"
#define PRINT_NODE_START "¡Ï¡Ð "
#define PRINT_NODE_LEFT " ("
#define PRINT_NODE_ID_START ", ID: "
#define PRINT_NODE_RIGHT ")"
#define PRINT_NODE "¡Ï¡Ð %s (%s, ID: %d)"

// Error Message
#define ROOT_CANNOT_INSERT_PARENT "Root can't insert parent node"
#define ROOT_CANNOT_INSERT_SIBLING "Root can't insert sibling node"