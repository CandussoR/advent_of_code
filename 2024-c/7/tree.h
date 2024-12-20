enum operation { UP, ADD, CONCAT };

typedef struct node_t {
	enum operation operation;
	struct node_t **children;
	int children_len;
} node_t;

typedef struct {
	node_t *root;
} tree_t;

tree_t *create_tree(node_t *node);
node_t *create_node(enum operation op);
void add_children(node_t *parent_node, int number_possibilities, node_t *child_node);
void fill_tree(node_t *node, int number_possibilities, int curr_depth, int depth);
void walk_tree(node_t *node, int *path, int current_depth);
void release_nodes(node_t *node, int number_possibilities);
void release_tree(tree_t *tree, int number_possibilities);

