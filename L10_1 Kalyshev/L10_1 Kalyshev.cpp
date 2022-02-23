#include "Header.h"


// индексы входа и выхода
struct Position {
    int i, j;
};

// Уровень игры
struct Level {
    int map[10][10]; // карта уровня
// 0 – воздух
// 1 – земля
    int n; // количество строк
    int m; // количество столбцов
    struct Position entry; // вход
    struct Position exit; // выход
};

void printLevel(struct Level* level) {

    for (int i = 0; i < level->n; i++) {
        for (int j = 0; j < level->m; j++) {
            printf("%5d ", level->map[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("Entry i = %d; j = %d\n", level->entry.i, level->entry.j);
    printf("Exit i = %d; j = %d\n\n", level->exit.i, level->exit.j);
}

char filename[] = "C:\\Users\\yanka\\OneDrive\\stuff\\10laba.txt";

int loadLevel(struct Level* level) {
    FILE* fin = fopen(filename, "rt");

    if (fin == NULL) {
        printf("File %s is not opened", filename);
        return 0;
    }

    fscanf_s(fin, "%d", &level->n);
    fscanf_s(fin, "%d", &level->m);

    for (int i = 0; i < level->n; i++) {
        for (int j = 0; j < level->m; j++) {
            fscanf_s(fin, "%d", &level->map[i][j]);
        }
    }

    fscanf_s(fin, "%d", &level->entry.i);
    fscanf_s(fin, "%d", &level->entry.j);

    fscanf_s(fin, "%d", &level->exit.i);
    fscanf_s(fin, "%d", &level->exit.j);

    fclose(fin);
    return 1;
}

int saveLevel(struct Level* level) {
    FILE* fin = fopen(filename, "wt");

    if (fin == NULL) {
        printf("File %s is not opened", filename);
        return 0;
    }

    fprintf(fin, "%d", level->n);
    fprintf(fin, "%s", " ");
    fprintf(fin, "%d", level->m);
    fprintf(fin, "%s", "\n");

    for (int i = 0; i < level->n; i++) {
        for (int j = 0; j < level->m; j++) {
            fprintf(fin, "%d", level->map[i][j]);
            fprintf(fin, "%s", " ");
        }
        fprintf(fin, "%s", "\n");
    }

    fprintf(fin, "%d", level->entry.i);
    fprintf(fin, "%s", " ");
    fprintf(fin, "%d", level->entry.j);
    fprintf(fin, "%s", "\n");

    fprintf(fin, "%d", level->exit.i);
    fprintf(fin, "%s", " ");
    fprintf(fin, "%d", level->exit.j);
    fprintf(fin, "%s", "\n");

    fclose(fin);
    return 1;
}

void addInColumn(struct Level* level, int indexCol) {
    for (int i = level->n - 1; i >= 0; i--) {
        if (level->map[i][indexCol] == 0) {
            level->map[i][indexCol] = 1;
            break;
        }
    }
}

void deleteInColumn(struct Level* level, int indexCol) {
    for (int i = 0; i < level->n - 1; i++) {
        if (level->map[i][indexCol] == 1) {
            level->map[i][indexCol] = 0;
            break;
        }
    }
}

void deleteMaxColumn(struct Level* level) {
    int t;
    int tmax = 0;
    int indexCol;
    for (int i = 0; i < level->m; i++) {
        t = 0;
        for (int k = 0; k < level->n; k++) {
            if (level->map[k][i] == 1) {
                t++;
            }
        }
        if (t > tmax) {
            tmax = t;
            indexCol = i;
        }
    }

    for (int i = 0; i < level->n - 1; i++) {
        if (level->map[i][indexCol] == 1) {
            level->map[i][indexCol] = 0;
            break;
        }
    }
}

void enterMinColumn(struct Level* level) {
    int t;
    int tmin = 999;
    int indexCol;
    for (int i = 0; i < level->m; i++) {
        t = 0;
        for (int k = 0; k < level->n - 1; k++) {
            if (level->map[k][i] == 1) {
                t++;
            }
        }
        if (t < tmin) {
            tmin = t;
            indexCol = i;
        }
    }

    for (int i = level->n - 1; i >= 0; i--) {
        if (level->map[i][indexCol] == 0) {
            level->map[i][indexCol] = 1;
            break;
        }
    }
}

void main()
{
    struct Level g;
    int k = 0;
    do
    {
        if (k == 0) {
            loadLevel(&g);
        }
        if (k == 1) {
            int j;
            printf("\n Input j> ");
            scanf("%d", &j);
            addInColumn(&g, j);
        }
        if (k == 2) {
            int j;
            printf("\n Input j> ");
            scanf("%d", &j);
            deleteInColumn(&g, j);
        }
        if (k == 3) {
            saveLevel(&g);
        }
        if (k == 4) {
            deleteMaxColumn(&g);
        }
        if (k == 5) {
            enterMinColumn(&g);
        }

        printLevel(&g);

        printf("\n\n\n");
        printf("Please select action:\n");
        printf("0: Reload file\n");
        printf("1: addInColumn\n");
        printf("2: deleteInColumn\n");
        printf("3: saveLevel\n");
        printf("4: deleteMaxColumn\n");
        printf("5: enterMinColumn\n");
        printf("\n-1: Exit\n");

        scanf("%d", &k);
    } while (k != -1);
}