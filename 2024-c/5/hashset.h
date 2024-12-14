typedef struct entry_t {
	char *value;
	struct entry_t *next;
} entry_t;

typedef struct {
	entry_t **entries;
} hashset_t;

unsigned int hash(const char *value);
hashset_t *create_hashset(void);
entry_t *create_entry(const char *value);
void hs_set(hashset_t *hashset, const char *value);
char *hs_get(hashset_t *hashset, const char *value);
void free_hashset(hashset_t *hashset);
