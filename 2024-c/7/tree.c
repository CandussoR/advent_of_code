/*
 * Tree exhausting combinations given a certain number of choices.
 * Made for part2, some things to reconsider for a general purpose tree.
 */

#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

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


void add_children(node_t *parent_node, int number_possibilities, node_t *child_node)
{
	if (parent_node->children_len) {
		parent_node->children[parent_node->children_len] = child_node;
		++parent_node->children_len;
		return;
	}

	parent_node->children = malloc(sizeof(node_t *) * number_possibilities);
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

void fill_tree(node_t *node, int number_possibilities, int curr_depth, int depth)
{
	if (curr_depth >= depth)
		return;

	for (int j = 0 ; j < number_possibilities ; ++j) {
		// j is cast as operation
		node_t *new_node = create_node(j);
		if (!new_node) {
			printf("An error occured.\n");
			return;
		}
		add_children(node, number_possibilities, new_node);
		fill_tree(new_node, number_possibilities, curr_depth + 1, depth);
	}
}

void release_nodes(node_t *node, int number_possibilities)
{
	if (!node->children_len) {
		free(node);
		return;
	}

	
	for (int i = 0 ; i < number_possibilities ; ++i) {
		release_nodes(node->children[i], number_possibilities);
	}
	node->children_len = 0;
	free(node->children);
}


void release_tree(tree_t *tree, int number_possibilities)
{
	release_nodes(tree->root, number_possibilities);
	free(tree);
}

int main()
{
	int tree_depth = 2;
	int path[tree_depth];
	node_t *root = create_node(ADD);
	tree_t *tree = create_tree(root);
	fill_tree(tree->root, 3, 0, tree_depth);
	walk_tree(tree->root, path, 0);
	release_tree(tree, 3);
	return 0;
}
