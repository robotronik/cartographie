#include <stdio.h>
#include <stdlib.h>
#include "geometrie.h"
#include "obstacles.h"


Obstacle ObstaclesStatiques[NOMBRE_OBSTACLES_STATIQUES];
int nombreObstaclesNonStatiques=0;
Obstacle ObstaclesNonStatiques[NOMBRE_OBSTACLES_NON_STATIQUES_MAX];
// Tableau définissant les obstacles. À NE PAS MODIFIER POUR 2015 !

//Type, 1x/centrex,         1y/centrey,         2x,                 2y
const int obstacles[NOMBRE_OBSTACLES_STATIQUES][5]={
    // Bords de la table
    {0, 0+ROBOT_R,          0+ROBOT_R,      TABLE_H-ROBOT_R,    0+ROBOT_R},
    {0, TABLE_H-ROBOT_R,    0+ROBOT_R,      TABLE_H-ROBOT_R,    TABLE_W-ROBOT_R},
    {0, TABLE_H-ROBOT_R,    TABLE_W-ROBOT_R,0+ROBOT_R,          TABLE_W-ROBOT_R},
    {0, 0+ROBOT_R,          TABLE_W-ROBOT_R,0+ROBOT_R,          0+ROBOT_R},

    // Estrade
    {1, 100,                1200, 0, 0},
    {0, 100+ROBOT_R,        1200,           100+ROBOT_R,        1800+ROBOT_R},
    {1, 100,                1800, 0, 0},

    // Marches (Gros robot)
    {0, TABLE_H,            967-ROBOT_R,    TABLE_H-580,        967-ROBOT_R},
    {1, 580,                967, 0, 0},
    {0, TABLE_H-580-ROBOT_R,967,            TABLE_H-580-ROBOT_R,2033},
    {1, 580,                2033, 0, 0},
    {0, TABLE_H-580,        2033+ROBOT_R,   TABLE_H-580,        2033+ROBOT_R},

    // Zone de départ
    {0, 778-ROBOT_R,        0,              778-ROBOT_R,        400},
    {1, 788,                400, 0, 0},
    {0, 778,                400+ROBOT_R,    800,                400+ROBOT_R},
    {1, 800,                400, 0, 0},
    {0, 800+ROBOT_R,        0,              800+ROBOT_R,        400},

    {0, 800,                70+ROBOT_R,     800,                70+ROBOT_R},

    {0, 1200-ROBOT_R,       0,              1222-ROBOT_R,       400},
    {1, 1200,               400, 0, 0},
    {0, 1200,               400+ROBOT_R,    1222,               400+ROBOT_R},
    {1, 1222,               400, 0, 0},
    {0, 1222+ROBOT_R,       0,              1222+ROBOT_R,       400},

    // Zone de départ ennemie
    {0, 778-ROBOT_R,        TABLE_W,        778-ROBOT_R,        TABLE_W-400},
    {1, 788,                TABLE_W-400, 0, 0},
    {0, 778,                TABLE_W-400-ROBOT_R,800,            TABLE_W-400-ROBOT_R},
    {1, 800,                TABLE_W-400,    0, 0},
    {0, 800+ROBOT_R,        TABLE_W,        800+ROBOT_R,        TABLE_W-400},

    {0, 800,                70+ROBOT_R,     800,                70+ROBOT_R},

    {0, 1200-ROBOT_R,       0,              1222-ROBOT_R,       400},
    {1, 1200,               400, 0, 0},
    {0, 1200,               400+ROBOT_R,    1222,               400+ROBOT_R},
    {1, 1222,               400, 0, 0},
    {0, 1222+ROBOT_R,       0,              1222+ROBOT_R,       400}
};

// Fonctions d'initialisation
void addAllObstaclesStatiques(){
    int i;
    for (i = 0; i < NOMBRE_OBSTACLES_STATIQUES ; ++i)
        addObstacleStatique(obstacles[i], i);
}
void addObstacleStatique(const int valeurs[], int i){
    Obstacle obstacle;
    coord point;
    obstacle.type   = valeurs[0];
            point.x = valeurs[1];
            point.y = valeurs[2];
    obstacle.point1 = point;
            point.x = valeurs[3];
            point.y = valeurs[4];
    obstacle.point2 = point;

    obstacle.rayon  = 0;

    ObstaclesStatiques[i]=obstacle;
}


void addObstacleNonStatiqueRond(coord centre, int rayon) {
    Obstacle obstacle;
    obstacle.type   = 1;
    obstacle.point1 = centre;
    obstacle.rayon  = rayon;
    ObstaclesNonStatiques[nombreObstaclesNonStatiques++]=obstacle;
}




int passagePossible(coord a, coord b) {
    int i;
    for (i = 0; i < NOMBRE_OBSTACLES_STATIQUES; ++i)
        if (conflitPassageObstacle(a, b, ObstaclesStatiques[i]))
            return 0;
    for (i = 0; i < nombreObstaclesNonStatiques; ++i)
        if (conflitPassageObstacle(a, b, ObstaclesNonStatiques[i]))
            return 0;
    return 1;
}

int conflitPassageObstacle(coord a, coord b, Obstacle obstacle) {
    switch (obstacle.type) {
        case 0:     // Segment
            return SegmentsIntersectent(a, b, obstacle.point1, obstacle.point2);
            break;
        case 1:     // Cercle
            return (distancePointSegment(a, b, obstacle.point1) <= ROBOT_R + obstacle.rayon);
            break;
        default:
            return 1;
            break;
    }
}


coord pointLePlusProche(coord origine) {
    coord origine_new;
    origine_new.x = ((origine.x - GRID_DX) % GRID_X) + GRID_DX;
    origine_new.y = ((origine.y - GRID_DY) % GRID_Y) + GRID_DY;
    if (passagePossible(origine, origine_new)==0) {
        origine_new.x+=GRID_DX;
        if (passagePossible(origine, origine_new)==0) {
            origine_new.x+=GRID_DX;
            if (passagePossible(origine, origine_new)==0) {
                origine_new.x-=GRID_DX;
                if (passagePossible(origine, origine_new)==0)
                    origine_new.x=-1;
                    origine_new.y=-1;

            }
        }
    }
    return origine_new;
}

