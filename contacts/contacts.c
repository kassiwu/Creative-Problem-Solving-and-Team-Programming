/*
 * contacts.c
 *
 *  Created on: Feb 10, 2018
 *  Author: Dylan DiGeronimo, Jacob Fallin, Kexian Wu
 *  I pledge my honor that I have abided by the Stevens Honor System.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define ALPHABET_LENGTH    26
#define OPERATION_BUF_SIZE  5
#define NAME_BUF_SIZE      22

// Basic trie node -- also, keep track of number of nodes below this one.
typedef struct node {
    int num_children;
    struct node *children[ALPHABET_LENGTH];
} trie_node;


// A utility function to create a new trie node
struct node *new_node() {
   struct node *temp = (struct node *)malloc(sizeof(struct node));
   temp->num_children = 0;
   for (int i = 0; i < ALPHABET_LENGTH; i++) {
		   temp->children[i] = NULL;
    }
   return temp;
}

// A utility function to add a word to the trie
void add(struct node *trieTree, const char *name) {
	struct node *currentNode = trieTree;
	while (*name != '\0') {
		if (currentNode->children[*name-'a'] == NULL) {
            // Make a new node
			currentNode->children[*name-'a'] = new_node();
		}
        // update current node and increment occurences
		currentNode = currentNode->children[*name++ - 'a'];
		currentNode->num_children++;
	}
	}

// A utility function to return the number of contact names starting with partial
int find(struct node *node, char *partial){
	while (node && *partial != '\0') {
		node = node->children[*partial++ - 'a'];
	}
	if (node == NULL) {
		return 0;
	}
	return node->num_children;
}

// Free a trie
void free_trie(struct node *trie) {
    if (trie != NULL) {
        for (int i = 0; i < ALPHABET_LENGTH; i++) {
            free_trie(trie->children[i]);
        }
        free(trie);
    }
}


int main(int argc, char const *argv[]) {
	int num_of_operations;
	char command[OPERATION_BUF_SIZE];
    char string[NAME_BUF_SIZE];
    
    // Create a new node
    struct node *trie = new_node();
    
    // Read in number of operations to perform
	scanf("%d\n", &num_of_operations);
	 if (num_of_operations <= 0) {
		 return 1;
	 }
    // Loop until the number of operations left is zero
	 while(num_of_operations--) {
		 scanf("%s", command);
	     scanf("%s", string);
         // Call the appropriate function based on the value of command
	     if (!strcmp(command, "add")) {
	    	 	 add(trie,string);
	     }
	     else if (!strcmp(command, "find")) {
	    	 	 printf("%d\n",find(trie,string));
	     }
	 }
    // Free a trie
    free_trie(trie);
    return 0;
}

