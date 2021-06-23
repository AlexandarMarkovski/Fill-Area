#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct pixel{
    int R;
    int G;
    int B;
};

double average(int a, int b, int c){
    double res = (a + b + c) / 3;
    return res;
}

bool checkAverages(double avgMain, double avgSecondary){
    if(avgMain > avgSecondary){
        if(avgMain - avgSecondary <= 1){
            return true;
        }
        return false;
    }
    else if(avgMain < avgSecondary){
        if(avgSecondary - avgMain <= 1){
            return true;
        }
        return false;
    }
    else{
        return true;
    }
}

int main()
{
    // Zapisvane na dannite ot faila

    int sizeX = 0;
    int sizeY = 0;

    FILE *file = fopen("proekt.txt", "r+");

    fseek(file, 0, SEEK_SET);

    fscanf(file, "%d", &sizeX);
    fscanf(file, "%d", &sizeY);

    struct pixel image[sizeX][sizeY];

    for(int i = 0; i < sizeY; i++){
        for(int j = 0; j < sizeX; j++){
            fscanf(file, "%d", &image[j][i].R);
            fseek(file, 1, SEEK_CUR);
            fscanf(file, "%d", &image[j][i].G);
            fseek(file, 1, SEEK_CUR);
            fscanf(file, "%d", &image[j][i].B);
        }
    }

    // Zanulqvane na suotvetnite koordinati

    int count = 0;

    int x = 0;
    int y = 0;
    scanf("%d %d", &y, &x);

    double avgMain = average(image[x][y].R, image[x][y].G, image[x][y].B);
    double avgAbove = average(image[x][y-1].R, image[x][y-1].G, image[x][y-1].B);
    double avgUnder = average(image[x][y+1].R, image[x][y+1].G, image[x][y+1].B);
    double avgLeft = average(image[x-1][y].R, image[x-1][y].G, image[x-1][y].B);
    double avgRight = average(image[x+1][y].R, image[x+1][y].G, image[x+1][y].B);

    if(y - 1 >= 0){
       if(checkAverages(avgMain, avgAbove)){
            image[x][y-1].R = 0; image[x][y-1].G = 0; image[x][y-1].B = 0; count++;
        }
    }
    if(y + 1 < sizeY){
        if(checkAverages(avgMain, avgUnder)){
            image[x][y+1].R = 0; image[x][y+1].G = 0; image[x][y+1].B = 0; count++;
        }
    }
    if(x - 1 >= 0){
        if(checkAverages(avgMain, avgLeft)){
            image[x-1][y].R = 0; image[x-1][y].G = 0; image[x-1][y].B = 0; count++;
        }
    }
    if(x + 1 < sizeX){
        if(checkAverages(avgMain, avgRight)){
            image[x+1][y].R = 0; image[x+1][y].G = 0; image[x+1][y].B = 0; count++;
        }
    }

    image[x][y].R = 0;
    image[x][y].G = 0;
    image[x][y].B = 0;
    count++;

    // Zapisvane na promenenite danni obratno vuv faila

    fseek(file, 4, SEEK_SET);

    for(int i = 0; i < sizeY; i++){
        for(int j = 0; j < sizeX; j++){
            fprintf(file, "%d:%d:%d ", image[j][i].R, image[j][i].G, image[j][i].B);
        }
        fprintf(file, "\n");
    }

    for(int i = 0; i < count; i++){
        fprintf(file, "         ");
    }

    fclose(file);

    return 0;
}
