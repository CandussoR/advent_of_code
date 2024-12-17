/*
 * This program does not find the good solution for day 6 part 2.
 * For now, best guess with input is 2152, and it's false : should be 1919.
 * Giving up.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LINE_MAX 150
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

enum Direction {
	UP,
	DOWN,
	LEFT,
	RIGHT
};

typedef struct {
	int x;
	int y;
	enum Direction dir;
} pos;

pos set_guard_pos(char **map, const int height)
{
	pos p2 = {0, 0, UP};
	for (p2.x = 0 ; p2.x < height ; ++p2.x) {
		for (p2.y = 0 ; p2.y < strlen(map[p2.x]) ; ++p2.y) {
			if (map[p2.x][p2.y] == '^') {
				return p2;
			}
		}
	}
}

void switch_direction(pos *p) {
	switch (p->dir) {
		case UP:
			p->dir = RIGHT;
			break;
		case RIGHT:
			p->dir = DOWN;
			break;
		case DOWN:
			p->dir = LEFT;
			break;
		case LEFT:
			p->dir = UP;
			break;
	}
}

void update_coordinates(pos *p) {
	switch (p->dir) {
		case UP:
			--p->x;
			break;
		case RIGHT:
			++p->y;
			break;
		case DOWN:
			++p->x;
			break;
		case LEFT:
			--p->y;
			break;
	}
}

bool is_visited(pos *arr, int arr_len, pos p)
{
	for (int i = 0 ; i < arr_len ; ++i) {
		if (arr[i].x == p.x && arr[i].y == p.y && arr[i].dir == p.dir)
			return true;
	}
	return false;
}

int write_patrol(char **map, const int limit_height, pos starting_p, bool check, bool write) {
	int len = strlen(map[0]) * limit_height;
	pos visited[len];
	int visited_len = 0;
	pos *p_visited = visited;

	int count = 0;
	pos p = starting_p;
	pos last = p;

	while ((p.x >= 0 && p.x < limit_height) && (p.y >= 0 && p.y < strlen(map[p.x]))) {
		// For part 2, if we return on the same spot going the same direction, loop
		if (check && is_visited(visited, visited_len, p)) {
			printf("Already visited, -1!\n");
			return -1;
		}

		// keeping track of visited places for part 2.
		*p_visited = p;
		++p_visited;
		++visited_len;

		if (map[p.x][p.y] == '#') {
			switch_direction(&p);
			p.x = last.x;
			p.y = last.y;
		} else if (map[p.x][p.y] != 'X') {
			++count;
			if (write)
				map[p.x][p.y] = 'X';
		}
		last = p;
		update_coordinates(&p);
	}
	return count;
}

int check_for_loops(char **walked_map, const int limit_height, const pos guard_init)
{
	int loop_count = 0;
	int obs = 0;
	pos current = guard_init;
	while ((current.x >= 0 && current.x < limit_height) && 
		(current.y >= 0 && current.y < strlen(walked_map[current.x]))) {
		//printf("\nLoop %d: \n", loop_count);
		//printf("Current pos (%d, %d), dir: %d\n", current.x, current.y, current.dir);
		pos new_pound = current;
		update_coordinates(&new_pound);

		if (new_pound.x < 0 || new_pound.y < 0 || new_pound.x >= limit_height || new_pound.y >= strlen(walked_map[current.x])) {
			//printf("Out of bounds : we break.\n");
			break;
		}

		//printf("Loop %d: New_pound pos (%d, %d), dir: %d ; it's a %c\n", loop_count, new_pound.x, new_pound.y, new_pound.dir, walked_map[new_pound.x][new_pound.y]);
		if (walked_map[new_pound.x][new_pound.y] == '#') {
			switch_direction(&current);
			continue;
		}
		else
			walked_map[new_pound.x][new_pound.y] = '#';
		/*
		if (new_pound.x == (guard_init.x) && new_pound.y == (guard_init.y - 1)) {
		printf("Map sent\n");
		for (int i = 0 ; i < limit_height ; ++i)
			printf("%s\n", walked_map[i]);
		printf("\n");
		}
		*/
		++loop_count;
		int ret = write_patrol(walked_map, limit_height, current, true, false);
		if (ret == -1)
			++obs;
		walked_map[new_pound.x][new_pound.y] = 'X';
		update_coordinates(&current);
	}
	return obs;
}

void free_map(char **map, int length)
{
	for (int i = 0 ; i < length ; ++i)
		free(map[i]);
	free(map);
}

int main()
{
	char line[LINE_MAX];
	int nl = 0;
	pos p = {-1, -1, UP};
	int obs_count = 0;
	char **guard_map = malloc(LINE_MAX * sizeof(char *));
	if (!guard_map) {
		printf("Couldn't allocate memory to map\n");
		return 2;
	}

	while (scanf("%149s", line) == 1) {
		if (nl >= LINE_MAX)
			break;
		guard_map[nl] = malloc(LINE_MAX * sizeof(char));
		if (guard_map[nl])
			strncpy(guard_map[nl], line, LINE_MAX);
		++nl;
	}

	bool check_loop = true;
	pos guard_init = set_guard_pos(guard_map, nl);
	int count = write_patrol(guard_map, nl, guard_init, !check_loop, true);
	printf("Count is %i\n", count);
	int obs = check_for_loops(guard_map, nl, guard_init);
	printf("Obstacles found is %i\n", obs);
	free_map(guard_map, nl);
	return 0;
}
