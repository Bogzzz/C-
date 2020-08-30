#include "wall.h"
#include "maze.h"

//this function accepts the maze, with the walls in it and a path from start cell to end cell
//returns the number of steps made within the shortest path

int runMaze(Maze& theMaze, int path[], int startCell, int endCell) {

	int count = 1; //counter for number of steps made

	int numCols = theMaze.numCols();
	int numRows = theMaze.numRows();
	int numCells = numCols * numRows;


	//base case: end point found
	if (endCell == startCell) {
		path[count - 1] = endCell;
		return count;
	}

	else {

		//going up
		if ((endCell - numCols) >= 0 && (endCell - numCols) <= numCells) {  //check if the next move within the bounds of the maze
			if (theMaze.canGo(endCell, endCell - numCols) && !theMaze.isMarked(endCell - numCols)) { //check if there is no wall and the cell wasn't visited
				theMaze.mark(endCell);
				int pathLength = runMaze(theMaze, path, startCell, endCell - numCols);
				if (pathLength > 0) { //if the path was found
					count += pathLength;    //increase the number of steps
					path[count - 1] = endCell;  //saves the cell into the path index
					return  count;
				}
			}
		}

		//going right
		if ((endCell + 1) >= 0 && (endCell + 1) <= numCells) {
			if (theMaze.canGo(endCell, endCell + 1) && !theMaze.isMarked(endCell + 1)) {
				theMaze.mark(endCell);
				int pathLength = runMaze(theMaze, path, startCell, endCell + 1);
				if (pathLength > 0) {
					count += pathLength;
					path[count - 1] = endCell;

					return count;
				}
			}
		}
		//going left
		if ((endCell - 1) >= 0 && (endCell - 1) <= numCells) {

			if (theMaze.canGo(endCell, endCell - 1) && !theMaze.isMarked(endCell - 1)) {
				theMaze.mark(endCell);
				int pathLength = runMaze(theMaze, path, startCell, endCell - 1);
				if (pathLength > 0) {
					count += pathLength;
					path[count - 1] = endCell;

					return count;
				}
			}
		}
		//going down
		if ((endCell + numCols) >= 0 && (endCell + numCols) <= numCells) {
			if (theMaze.canGo(endCell, endCell + numCols) && !theMaze.isMarked(endCell + numCols)) {
				theMaze.mark(endCell);
				int pathLength = runMaze(theMaze, path, startCell, endCell + numCols);
				if (pathLength > 0) {
					count += pathLength;
					path[count - 1] = endCell;

					return count;
				}
			}
		}
	}
	// unmark if the path was not found and return
	theMaze.unMark(endCell);

	return 0;
}