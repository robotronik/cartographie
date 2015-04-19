#include <stdlib.h>
#include "astar.h"
#include "cartographie.h"

#include "debug.h"

int pathfinding_initialized = 0;
PointList cheminComplet;

void pathfinding_init() {
    addAllObstaclesStatiques();
    #if USE_SDL
    init_sdl_screen();
    dessine_fond();
    int i;
    for (i = 0; i < NOMBRE_OBSTACLES_STATIQUES; ++i) {
        Obstacle obstacle = getObstacleStatique(i);
        if (obstacle.type == 0)
            dessine_obstacle_ligne(obstacle.point1.x, obstacle.point1.y, obstacle.point2.x, obstacle.point2.y);
        else
            dessine_obstacle_rond (obstacle.point1.x, obstacle.point1.y, obstacle.rayon + ROBOT_R);
    }
    #endif
    pathfinding_initialized=1;
}


int pathfinding(int start_x, int start_y, int cible_x, int cible_y) {
    // On nettoie les tableaux, au cas où
    if (!pathfinding_initialized)
        pathfinding_init();


    coord start, cible;
    start.x = start_x;
    start.y = start_y;
    cible.x = cible_x;
    cible.y = cible_y;

    pre_astar();
    int astar_result = astar(start, cible);

    switch(astar_result) {
        case -1:
            debug("Il y a eu une erreur dans l'algorithme, à débugger !\n");
            break;
        case  0:
            debug("Pas de chemin trouvé…\n");
            break;
        case  1:
            reconstruct_path(&cheminComplet);
            break;
    }
    post_astar();
    return astar_result;

}
int return_length_of_path_found() {
    return cheminComplet.size;
}
void return_path_found(int tableau[][2]) {
    int i;
    for (i = 0; i < cheminComplet.size; ++i) {
        Point valeur = cheminComplet.data[i];
        tableau[i][0] = valeur.coord.x;
        tableau[i][1] = valeur.coord.y;
    }
}

int nouvel_obstacle_rond(int x, int y, int rayon) {
    coord centre;
    centre.x = x;
    centre.y = y;
    return addObstacleNonStatiqueRond(centre, rayon);
}
void reinitialise_obstacles_temporaires() {
    reinit_obstacles_non_statiques();

}