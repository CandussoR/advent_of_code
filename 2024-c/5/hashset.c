/*
 * Hash set implementing separate chaining method.
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define SET_SIZE 1200

typedef struct entry_t {
	char *value;
	// in case of collision, linked list style
	struct entry_t *next;
} entry_t;

typedef struct {
	// Array of pointer to an entry
	entry_t **entries;
} hashset_t;

// hash must be between 0 and hash SET_SIZE - 1
unsigned int hash(const char *value)
{
	unsigned long int hash_val = 0;
	unsigned int val_len = strlen(value);

	for (int i = 0 ; i < val_len ; ++i)
		hash_val = hash_val * 37 + value[i];

	// Keep 0 <= hash_val =< SET_SIZE
	hash_val = hash_val % SET_SIZE;

	return hash_val;
}

/*
* Creates the hash set.
*/
hashset_t *create_hashset(void) {
	// Allocating memory for the hashset
	hashset_t *hashset = malloc(sizeof(hashset_t));
	if (hashset == NULL) {
		printf("Couldn't allocate memory for the hash table!");
		return NULL;
	}

	// Allocating memory for all the potential pointers of the hash table
	hashset->entries = malloc(sizeof(entry_t *) * SET_SIZE);
	if (!hashset->entries) {
		printf("Error: Could not allocate memory for hash table entries.\n");
		free(hashset);
		return NULL;
	}

	for (int i = 0 ; i < SET_SIZE ; ++i)
		hashset->entries[i] = NULL;

	return hashset;
}

entry_t *create_entry(const char *value)
{
	// Since we only allocate memory for pointers of each entry_t
	// we have to allocate memory for every pointer in the entry_t struct
	entry_t *entry = malloc(sizeof(entry_t));
	if (!entry) {
		printf("Couldn't allocate memory for entry.\n");
		return NULL;
	}

	entry->value = malloc(strlen(value) + 1);
	if (!entry->value) {
		printf("Couldn't allocate memory in ht_pair.");
		return NULL;
	}

	strcpy(entry->value, value);
	entry->next = NULL;

	return entry;
}

void hs_set(hashset_t *hashset, const char *value) {
	unsigned int hash_value = hash(value);
	// is value in hashset ?
	entry_t *entry = hashset->entries[hash_value];
	if (entry == NULL) {
		entry_t *v = create_entry(value);
		if (v == NULL) {
			printf("Couldn't allocate memory for value.\n");
			return;
		}
		hashset->entries[hash_value] = create_entry(value);
		return;
	}

	entry_t *prev;
	while (entry != NULL) {
		// If entry is not null and the value is the one we're searching for
		// we replace it.
		if (strcmp(entry->value, value) == 0) {
			printf("Value already present in set, moving on.\n");
			return;
			}
		// else we walk the list in search of key
		prev = entry;
		entry = prev->next;
	}

	// if we reached end of linked list without a match, we add a new pair
	prev->next = create_entry(value);
};


char *hs_get(hashset_t *hashset, const char *value)
{
	unsigned int hash_value = hash(value);
	// is value in hashset ?
	entry_t *entry = hashset->entries[hash_value];

	if (entry == NULL)
		return NULL;

	while (entry != NULL) {
		if (strcmp(entry->value, value) == 0)
			return entry->value;

		entry = entry->next;
	}

	// If we reach the end of the linked list without a match...
	return NULL;
}


void free_hashset(hashset_t *hashset)
{
    for (int i = 0; i < SET_SIZE; ++i) {
        entry_t *entry = hashset->entries[i];
        while (entry) {
            entry_t *temp = entry;
            entry = entry->next;
            free(temp->value);
            free(temp);
        }
    }
    free(hashset->entries);
    free(hashset);
}
