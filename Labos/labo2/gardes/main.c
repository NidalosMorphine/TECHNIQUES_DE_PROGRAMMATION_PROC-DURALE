#include <stdio.h>
#include <stdlib.h>
#include "point.h"
#include "geo.h"


int distanceManhattan(Point a, Point b) {
    return abs(a.x - b.x) + abs(a.y - b.y);
}


int main(void) {

    Point a = { 1, 2 };
    Point b = { 4, 6 };

    printf("Distance : %d\n", distanceManhattan(a, b));

    return 0;
}
