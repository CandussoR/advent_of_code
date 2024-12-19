#include <stdio.h>
#include <stdlib.h>

#define POSSIBILITIES 3
enum operation { UP, ADD, CONCAT };

typedef struct node_t {
	enum operation operation;
	struct node_t **children;
	int children_len;
} node_t;

typedef struct {
	node_t *root;
} tree_t;

tree_t *create_tree(node_t *node)
{
	tree_t *tree = malloc(sizeof(tree_t));
	if (!tree) {
		printf("Couldn't allocate memory for the tree.\n");
		return NULL;
	}
	tree->root = node;
	return tree;
}


/*
 * Create a node from operation (or int cast as operation) or returns NULL if fail.
 */
node_t *create_node(enum operation op)
{
	node_t *node = malloc(sizeof(node_t));
	if (!node) {
		printf("Couldn't allocate memory to the node.\n");
		return NULL;
	}

	node->operation = (enum operation) op; 
	node->children = NULL;
	node->children_len = 0;

	return node;
	}


void add_children(node_t *parent_node, node_t *child_node)
{
	if (parent_node->children_len) {
		parent_node->children[parent_node->children_len] = child_node;
		++parent_node->children_len;
		return;
	}

	parent_node->children = malloc(sizeof(node_t *) * POSSIBILITIES);
	if (!parent_node->children) {
		printf("Couldn't allocate memory for the children of this node.\n");
		return;
	}

	parent_node->children[parent_node->children_len] = child_node;
	++parent_node->children_len;
}

void walk_tree(node_t *node, int *path, int current_depth)
{
	if (!node) return;

	path[current_depth] = node->operation;

	printf("Walking the tree...\n");
	if (node->children_len) {
		for (int i = 0 ; i < node->children_len ; ++i)
			walk_tree(node->children[i], path, current_depth+1);
	}
	else {
		printf("Path: ");
		for (int i = 0; i <= current_depth; ++i) {
			printf("%d ", path[i]);
		}
		printf("\n");
		return;
	}
}

void fill_tree(node_t *node, int curr_depth, int depth)
{
	if (curr_depth >= depth)
		return;

	for (int j = 0 ; j < POSSIBILITIES ; ++j) {
		// j is cast as operation
		node_t *new_node = create_node(j);
		if (!new_node) {
			printf("An error occured.\n");
			return;
		}
		add_children(node, new_node);
		fill_tree(new_node, curr_depth + 1, depth);
	}
}

void release_nodes(node_t *node)
{
	if (!node->children_len) {
		printf("No children_len\n");
		free(node);
		return;
	}

	
	for (int i = 0 ; i < POSSIBILITIES ; ++i) {
		release_nodes(node->children[i]);
	}
	node->children_len = 0;
	free(node->children);
}


void release_tree(tree_t *tree)
{
	release_nodes(tree->root);
	free(tree);
}

int main()
{
	int tree_depth = 2;
	int path[tree_depth];
	node_t *root = create_node(ADD);
	printf("Node : %i, %li, %i\n", root->operation, sizeof(root->children), root->children_len);
	tree_t *tree = create_tree(root);
	printf("Tree created\n");
	fill_tree(tree->root, 0, tree_depth);
	walk_tree(tree->root, path, 0);
	release_tree(tree);
	return 0;
}
