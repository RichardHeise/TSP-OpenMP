#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <omp.h>
#include <time.h>
#include <string.h>
#include <sys/time.h>

#ifndef ENABLE_PROFILING
#define ENABLE_PROFILING 0
#endif

int min_distance;
int nb_towns;
int *dist_to_origin;

typedef struct {
    int to_town;
    int dist;
} d_info;

d_info **d_matrix;

double get_time() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double)tv.tv_sec + (double)tv.tv_usec / 1e6;
}

void tsp(int depth, int current_length, int *path, int *paths) {
    double start_time, end_time;

    if (current_length >= min_distance) return;

    if (depth == nb_towns) {
        current_length += dist_to_origin[path[nb_towns - 1]];
        if (current_length < min_distance)
            min_distance = current_length;
    } else if (depth == 1) {
        int me = path[depth - 1];

        #if ENABLE_PROFILING
        start_time = get_time();
        #endif

        #pragma omp parallel for schedule(dynamic) reduction(min:min_distance)
        for (int i = 0; i < nb_towns; i++) {
            int *path_local = (int *)malloc(nb_towns * sizeof(int));
            int *paths_local = (int *)malloc(nb_towns * sizeof(int));
            memcpy(path_local, path, nb_towns * sizeof(int));
            memcpy(paths_local, paths, nb_towns * sizeof(int));

            int town = d_matrix[me][i].to_town;
            if (!paths_local[town]) {
                int dist = d_matrix[me][i].dist;
                path_local[depth] = town;
                paths_local[town] = 1;
                tsp(depth + 1, current_length + dist, path_local, paths_local);
                paths_local[town] = 0;
            }

            free(path_local);
            free(paths_local);
        }

        #if ENABLE_PROFILING
        end_time = get_time();
        printf("Depth 1 took %lf seconds\n", end_time - start_time);
        #endif
    } else {
        int me = path[depth - 1];

        #if ENABLE_PROFILING
        start_time = get_time();
        #endif

        for (int i = 0; i < nb_towns; i++) {
            int town = d_matrix[me][i].to_town;
            if (!paths[town]) {
                int dist = d_matrix[me][i].dist;
                path[depth] = town;
                paths[town] = 1;
                tsp(depth + 1, current_length + dist, path, paths);
                paths[town] = 0;
            }
        }

        #if ENABLE_PROFILING
        end_time = get_time();
        printf("Depth %d took %lf seconds\n", depth, end_time - start_time);
        #endif
    }
}

void greedy_shortest_first_heuristic(int *x, int *y) {
    int i, j, k, dist;
    int *tempdist;

    tempdist = (int*) malloc(sizeof(int) * nb_towns);

    for (i = 0; i < nb_towns; i++) {
        for (j = 0; j < nb_towns; j++) {
            int dx = x[i] - x[j];
            int dy = y[i] - y[j];
            tempdist [j] = dx * dx + dy * dy;
        }
        for (j = 0; j < nb_towns; j++) {
            int tmp = INT_MAX;
            int town = 0;
            for (k = 0; k < nb_towns; k++) {
                if (tempdist [k] < tmp) {
                    tmp = tempdist [k];
                    town = k;
                }
            }
            tempdist [town] = INT_MAX;
            d_matrix[i][j].to_town = town;
            dist = (int)sqrt(tmp);
            d_matrix[i][j].dist = dist;
            if (i == 0)
                dist_to_origin[town] = dist;
        }
    }

    free(tempdist);
}

void init_tsp() {
    int i, st;
    int *x, *y;

    min_distance = INT_MAX;

    st = scanf("%u", &nb_towns);

    if (st != 1) exit(1);
 
    d_matrix = (d_info**) malloc (sizeof(d_info*) * nb_towns);
    for (i = 0; i < nb_towns; i++)
        d_matrix[i] = (d_info*) malloc (sizeof(d_info) * nb_towns);
    dist_to_origin = (int*) malloc(sizeof(int) * nb_towns);
   
    x = (int*) malloc(sizeof(int) * nb_towns);
    y = (int*) malloc(sizeof(int) * nb_towns);
    

    for (i = 0; i < nb_towns; i++) {
        st = scanf("%u %u", x + i, y + i);
        if (st != 2) exit(1);
    }
    
    greedy_shortest_first_heuristic(x, y);

    free(x);
    free(y);
}

int run_tsp() {
    int i, *path, *paths;

    init_tsp();
    
    path = (int*) malloc(sizeof(int) * nb_towns);
    paths = calloc(sizeof(int), nb_towns);
    path[0] = 0;
    paths[0] = 1;
    
    tsp (1, 0, path, paths);

    free(path);
    for (i = 0; i < nb_towns; i++)
        free(d_matrix[i]);
    free(d_matrix);

    return min_distance;
}

int main (int argc, char **argv) {
    int num_instances, st;
    st = scanf("%u", &num_instances);
    if (st != 1) exit(1);
    while(num_instances-- > 0)
        printf("%d\n", run_tsp());
    return 0;
}
