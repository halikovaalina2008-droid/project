#include <iostream>
#include <cstdlib>
#include <ctime>

enum {SIZE = 10, MINES = 10};

void mines(char pg[SIZE][SIZE])
{
    int a = rand() % 10;
    int b = rand() % 10;
    int count = 0;

    while (count < MINES) {
        if (pg[a][b] != '*' ) {
            pg[a][b] = '*';    
            count++;
        }
        a = rand() % 10;
        b = rand() % 10;
    }
    for(int i = 0; i < SIZE; i++) {
        for(int j = 0; j < SIZE; j++) {
            if (pg[i][j] != '*') {
                if (pg[i+1][j] == '*' ) pg[i][j] +=1;
                if (pg[i-1][j] == '*')  pg[i][j] +=1;
                if (pg[i][j+1] == '*')pg[i][j] +=1;
                if (pg[i][j-1] == '*') pg[i][j] +=1;
                if (pg[i+1][j+1] == '*') pg[i][j] +=1;
                if (pg[i-1][j-1] == '*')pg[i][j] +=1;
                if (pg[i-1][j+1] == '*') pg[i][j] +=1;
                if (pg[i+1][j-1] == '*') pg[i][j] +=1;
            }
        }
    }
}

void show(char ar[SIZE][SIZE])
{
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (int(ar[i][j]) <= -1) ar[i][j] = '#';
                
            if (ar[i][j] == '#') printf("%c ", ar[i][j]);
            else printf("%d ", ar[i][j]);
        }
        printf("\n");
        
    }
}

void open(char ar[SIZE][SIZE], char pg[SIZE][SIZE], int i, int j, bool& fl) 
{
    if (i < 0 || i >= SIZE || j < 0 || j >= SIZE) return;

    if (pg[i][j] == '*') {
        fl = false;
        return;
        
    }
    
    ar[i][j] = pg[i][j];

    if (int(pg[i][j]) != 0)
        return;
   
    if (i+1 < SIZE) open(ar, pg, i+1, j, fl);
    if (i-1 >= 0) open(ar, pg, i-1, j, fl);
    if (j+1 < SIZE) open(ar, pg, i, j+1, fl);
    if (j-1 >= 0) open(ar, pg, i, j-1, fl);
    if (i+1 < SIZE && j+1 < 10) open(ar, pg, i+1, j+1, fl);
    if (i-1 >= 0 && j-1 >= 0) open(ar, pg, i-1, j-1, fl);
    if (i-1 >= 0 && j+1 < SIZE) open(ar, pg, i-1, j+1, fl);
    if (i+1 < SIZE && j-1 >= 0) open(ar, pg, i+1, j-1, fl);
    
}

int main()
{
    srand(time(NULL));
    char pg[SIZE][SIZE] = {0};
    char ar[SIZE][SIZE];
    bool flag = true;
    int a, b;
    
    mines(pg);

    for (int i = 0; i < SIZE; i++) 
        for (int j = 0; j < SIZE; j++) 
            ar[i][j] = -1;
    
    show(ar);
    
    
    std::cout << "Вводите координаты для а и в (от 0 до 9)" << std::endl;

    while (flag) {
        std::cin >> a >> b;
        open(ar, pg, a, b, flag);
        show(ar);
        if (!(flag))
            std::cout << "Вы проиграли" << std::endl;

    }
    return 0;
}