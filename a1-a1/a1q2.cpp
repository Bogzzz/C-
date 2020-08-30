#include<iostream>
#include "wall.h"
#include "disjointset.h"


int generateMaze(int row, int col, Wall walls[]) {

	int cellT = row * col;
	int numSets = cellT;
	int numWalls = (row - 1) * (col)+(col - 1) * (row);
	int num = 0;

	DisjointSet Maze(cellT);

	for (int i = 0; i < cellT; i++) {
		Maze.makeSet(i);
	}

	for (int i = 0; i < row; i++) {
		for (int j = 0; j < col; j++) {
			int c1 = i * col + j;
			int c2 = c1 + 1;
			int c3 = c1 + col;

			if (c3 < cellT) {
				walls[num++] = Wall(c1, c3);
			}
			if (j < col - 1) {
				walls[num++] = Wall(c1, c2);
			}
		}
	}

	while (numSets > 1) {
		int random = rand() % num - 1;
		Wall choice = walls[random];
		int c1 = choice.cell1();
		int c2 = choice.cell2();

		if (Maze.findSet(c1) != Maze.findSet(c2)) {
			Maze.unionSets(c1, c2);
			for (int i = 0; i < num; i++)
			{
				if (i == random)
				{
					for (int j = i; j < (num - 1); j++)
					{
						walls[j] = walls[j + 1];
					}
				}
			}
			--numSets;
			--numWalls;
		}
	}
	return numWalls;
}