#include <stdio.h>
#include <stdlib.h>
#include "mbgldef.h"

int n, m;
int r1, c1;
int r2, c2;

int* h;

int* hget(u32 i, u32 j) {
    return &h[ i * m + j ];
}

void print_array() {
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < m; j++) {
            printf("%d ", *hget(i, j));
        }
        printf("\n");
    }
}

int distance(i1, j1, i2, j2) {
    return abs(i2 - i1) + abs(j2 - j1);
}

int main() {

    h = (int*)malloc(n * m * sizeof(int));
    
    scanf("%d %d", &n, &m);

    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < m; j++) {
            scanf(" %d", hget(i, j));
        }
    }

    scanf("%d %d", &r1, &c1);
    scanf("%d %d", &r2, &c2);

    print_array();

    int water_height = *hget(r2, c2);
    int rabbit_height = *hget(r1, c1);
    
    int min_height = 9000000; 
    for (int i = 0; i < n; i++) { 
        for (int j = 0; j < m; j++) {
            int* c_height = hget(i, j);
            if (*c_height > water_height && *c_height < min_height) {
                if (distance(i, j, r1, c1) <= distance(i, j, r2, c2)) {
                    min_height = *c_height;
                }

            }
        }
    }

}
