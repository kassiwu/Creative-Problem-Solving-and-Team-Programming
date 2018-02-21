/*
 *  hashit.cpp
 *  Created on: Feb 15, 2018
 *  Author: Dylan DiGeronimo, Jacob Fallin, Kexian Wu
 *  I pledge my honor that I have abided by the Stevens Honor System.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <memory.h>

#define TABLE_SIZE 101
#define OPERATION_BUF_SIZE  5
#define STRING_BUF_SIZE 16

// Define HashSet via typedef
typedef struct {
    char* keys[TABLE_SIZE];
    int num_keys;
} hash_set;


// Create a new HashSet
hash_set *new_set() {
	int i;
	hash_set* set = (hash_set*)malloc(sizeof(hash_set));
	set->num_keys=0;
	for(i=0;i<TABLE_SIZE;i++) {
		set->keys[i] = NULL;
	}
	return set;
}


// Free hash set
void clear_table(hash_set *set) {
	int i;
	for (i=0;i<TABLE_SIZE;i++) {
		free(set->keys[i]);
		set->keys[i]=NULL;
	}
	set->num_keys = 0;
	free(set);
}

// Generate hash key
int hash(char *key) {
	long sum = 0;
	long i = 1;
	 while(*key != '\0') {
		 sum += (*key) * i;
		 ++i;
		 ++key;
	  }
	  return (19 * sum) % 101;
}

// Examine each record in that entry to determine whether a match has been found
int search_key(hash_set *set, char *key) {
	int h = hash(key);
	int i, loc;
	for (i = 0;i<20;i++) {
		loc = (h+i*i+23*i)%101;
		if (set->keys[loc]==NULL) {
			continue;
		}
		// Returns 1 if the key exists in the table
		else if (!strcmp(set->keys[loc],key)) {
			return 1;
		}
	}
	// Return 0 if the key does not exist in the table
	return 0;
}

// Insert a new key into the table
int insert_key(hash_set *set, char *key) {
	// hash the key
	int h = hash(key);
	int i, loc;
	// Return 0 when the key has already existed in the table
	if (search_key(set, key) == 1) {
		return 0;
	}
	// Try to insert the key into the table at the first free position
	// Continue to examine other slots in the table until 20 table entries have been examined
	for (i = 0;i<20;++i) {
		loc = (h+i*i+23*i) % 101;
		if (set->keys[loc]==NULL) {
			set->keys[loc]= (char*)malloc(STRING_BUF_SIZE*sizeof(char));
			strcpy(set->keys[loc], key);
			(set->num_keys)++;
			return 1;
		}
	}
	return 0;
}

// Delete a key from a hash_set
int delete_key(hash_set *set, char *key) {
	// hash the key
	int h = hash(key);
	int i, loc;
	// Return 0 if the key does not exist in the table
	if (search_key(set, key) == 0) {
		return 0;
	}
	// Try to find the key in the table
	// Continue to examine other slots in the table until 20 table entries have been examined
	for (i = 0;i<20;i++) {
		loc = (h+i*i+23*i)%101;
		if (set->keys[loc]==NULL) {
			continue;
		}
		if (!strcmp(set->keys[loc],key)) {
			free(set->keys[loc]);
			set->keys[loc]=NULL;
			(set->num_keys)--;
			break;
		}
	}
	// Returns 1 if the key has been deleted in the table
	return 1;
}

// Print out a hashset
void display_keys(hash_set *set) {
	int i;
	// Print the the number of keys in the table
	printf("%d\n",set->num_keys);
	// Print all non-null-terminated strings
	for (i = 0;i<TABLE_SIZE;i++) {
		if(set->keys[i] != NULL) {
			printf("%d:%s\n",i,set->keys[i]);
		}
	}
}

int main(int argc, char const *argv[]) {
	int t;
	char command[OPERATION_BUF_SIZE];
    char string[STRING_BUF_SIZE];
    // Read in number of test cases
	scanf("%d\n", &t);
	// Loop until the number of test cases left is zero
	while (t--) {
		// Create a new hash_set
		hash_set *hash_table = new_set();
		int n,i;
		// Read in number of operations to perform
		scanf("%d\n", &n);
		// Loop n times
		for(i = 0;i<n;i++) {
			scanf( "%3s:%s", command, string);
			// Call the appropriate function based on the value of command
			if (!strcmp(command, "ADD")) {
				insert_key(hash_table, string);
			}
			else if (!strcmp(command, "DEL")) {
				delete_key(hash_table, string);
			}
		}
		display_keys(hash_table);
		clear_table(hash_table);
	}
	return 0;
}
