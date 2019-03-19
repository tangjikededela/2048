#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdio.h>

class GameMain
{
public:
    GameMain(int _max_score = 2048): max_score(_max_score)
    {
        N = 4;//How big the game board is
        memset((void*)(matrix[0]), 0, sizeof(matrix));
    }
    ~GameMain() {}
    void LeftOperator();
    void RightOperator();
    void UpOperator();
    void DownOperator();
    void PrintMatrix(int);
    void AddRandNum();
    int Check();
private:
    int max_score;
    int N;
    int matrix[4][4];//Number should be as same as N is.
    int arr[4];//Number should be as same as N is.
    void Move();
    void Merge();
    void MoveAndMerge();
};


void GameMain::Move()
{
    int pos0;
    for(pos0 = 0; pos0 < N; ++pos0)
    {
        if(!arr[pos0]) break;
    }
    for(int i = pos0 + 1; i < N; ++i)
    {
        if(arr[i]) arr[pos0++] = arr[i];
    }
    while(pos0 < N) {
        arr[pos0++] = 0;
    }
}

void GameMain::Merge()
{
    int pos;
    for(pos = 0; pos < N && !arr[pos]; ++pos) {}
    for(int i = pos + 1; i < N; ++i)
    {
        if(arr[i]) {
            if(arr[i] == arr[pos])
            {
                arr[pos] <<= 1;
                arr[i] = 0;
            }
            else {
                pos = i;
            }
        }
    }
}

void GameMain::MoveAndMerge()
{
    for(int i = 0; i < 3; ++i) Merge();
    Move();

}

void GameMain::LeftOperator()
{
    for(int ver = 0; ver < N; ++ver)
    {
        memcpy((void*)arr, (void*)matrix[ver], sizeof(arr));
        MoveAndMerge();
        memcpy((void*)matrix[ver], (void*)arr, sizeof(arr));
    }
}

void GameMain::RightOperator()
{
    for(int ver = 0; ver != N; ++ver)
    {
        for(int hor = 0; hor < N; ++hor) arr[hor] = matrix[ver][N-1-hor];
        MoveAndMerge();
        for(int hor = 0; hor < N; ++hor) matrix[ver][hor] = arr[N-1-hor];
    }
}

void GameMain::UpOperator()
{
    for(int hor = 0; hor < N; ++hor)
    {
        for(int i = 0; i < N; ++i) arr[i] = matrix[i][hor];
        MoveAndMerge();
        for(int i = 0; i < N; ++i) matrix[i][hor] = arr[i];
    }
}

void GameMain::DownOperator()
{
    for(int hor = 0; hor < N; ++hor)
    {
        for(int i = 0; i < N; ++i) arr[i] = matrix[N-1-i][hor];
        MoveAndMerge();
        for(int i = 0; i < N; ++i) matrix[i][hor] = arr[N-1-i];
    }
}

void GameMain::AddRandNum()
{
    int num = 2;
    srand(unsigned(time(NULL)));
    if((rand() % 4) == 3) num = 4;

    int zero = 0;
    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            if(!matrix[i][j]) zero++;
        }
    }

    int pos = rand() % zero + 1;
    int count = 0;
    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            if(!matrix[i][j])
            {
                count++;
                if(count == pos)
                {
                    matrix[i][j] = num;
                    break;
                }
            }
        }
    }
}

void GameMain::PrintMatrix(int step)
{
    printf("\nstep: %d\n", step);
    printf("MMMMMMMMMMMMMMMMMMMMMMMMMMM\n");
    for(int i = 0; i < N; ++i)
    {
        printf("! ");
        for(int j = 0; j < N; ++j)
        {
            if(matrix[i][j]) printf("%-6d", matrix[i][j]);
            else printf("      ");
        }
        printf("!\n");
    }
    printf("WWWWWWWWWWWWWWWWWWWWWWWWWWW\n");
}

int GameMain::Check()
{
    int count = 0;
    for(int i = 0; i < N; ++i)
    {
        for(int j = 0; j < N; ++j)
        {
            if(matrix[i][j] == max_score) return 1;
            if(matrix[i][j]) count++;
        }
    }
    if(N * N == count) return -1;
    return 0;
}

int main()
{
    while(1)
        {
        GameMain game(2048);
        game.AddRandNum();
        game.AddRandNum();
        printf("Enter direction, w for up, s for down, a for left, d for right, and then push enter\n");
        int step = 0;
        game.PrintMatrix(step++);

        while(1)
            {
            printf("Enter direction: ");
            char temp, c = 'e';
            while( (temp = getchar()) != 10) {
                if(('e' == c) && ('w' == temp || 'a' == temp || 's' == temp || 'd' == temp) )
                {
                        c = temp;
                }
            }

            switch (c)
            {
                case 'a': game.LeftOperator(); break;
                case 'd': game.RightOperator(); break;
                case 'w': game.UpOperator(); break;
                case 's': game.DownOperator(); break;
                default: break;
            }

            if('e' == c)
            {
                printf("\nInput Error!\n");
                continue;
            }

            game.AddRandNum();
            game.PrintMatrix(step++);
            int res = game.Check();
            if(1 == res)
            {
                printf("\nYou Win!\n\n");
                break;
            }
            if(-1 == res)
            {
                printf("\nYou Lose!\n\n");
                break;
            }
        }
    }

    return 0;
}

