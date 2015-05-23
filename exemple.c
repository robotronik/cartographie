#include "debug.h"

#include "cartographie.h"

int x_actuel = 300;
int y_actuel = 1000;


void set_trajectoire_xy_absolu(int x, int y) {
    new_xy_absolu(x, y);
}
void new_xy_absolu(int x, int y) {

    // On appelle le pathfinding et on regarde si il y a un chemin
    int on_a_un_chemin = pathfinding(x_actuel, y_actuel, x, y);
    debug(1, "chemin trouvé ? %d\n", on_a_un_chemin);

    if (on_a_un_chemin) {

        // On récupère le nombre de points de ce chemin
        int taille = return_length_of_path_found();

        // On récupère le chemin lui-même
        int chemin_trouve[taille][2];
        return_path_found(chemin_trouve);

        // On l'affiche
        int i;
        for (i = 0; i < taille; ++i)
            debug(1, "%d -- %d\n", chemin_trouve[i][0], chemin_trouve[i][1]);

        // Et on l'exécute !
        x_actuel = x;
        y_actuel = y;
    }
}


int main() {
    pathfinding_init();
    nouvel_obstacle_rond(1500, 1200, 200);
    new_xy_absolu(2700,1600);
    new_xy_absolu(300,1600);
    new_xy_absolu(2700,1600);

   // pathfinding(330, 1800,
   //            2600, 1003);

/*    PointList cheminFinal = reconstruct_path();

    debug(1, "visited, %d\n", visitedPoints().size);
    debug(1, "final, %d\n", cheminFinal.size);

    //PointList visitedPointsV = visitedPoints();
    list_printf(&cheminFinal);
*/
#if USE_SDL
    while(!sdl_manage_events());
#endif

    return 0;
}

