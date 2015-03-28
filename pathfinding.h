#ifndef PATHFINDING_H
#define PATHFINDING_H
void pathfinding_init();
void pathfinding(coord start, coord cible);

PointList reconstruct_path();

PointList visitedPoints();


#endif // PATHFINDING_H