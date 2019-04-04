#include<stdio.h>
#include<Windows.h>

const int ROW = 3;
const int COL = 3;
int chessboard[ROW][COL];
int score[ROW][COL];

void Initmap();
void Showmap();        //打印棋局
bool isWin();        //判断是否有一方获胜
bool isFull();        //判断棋盘是否为满
void PcPlay();        //电脑下棋
void HumanPlay();    //人下棋

int main()
{
    Initmap();
    Showmap();
    while ((!isFull()) && (!isWin()))
    {
        HumanPlay();
        //system("cls");
        Showmap();
        if (isWin())
            break;
        Sleep(500);
        PcPlay();
        //system("cls");
        Showmap();
    }

    if (isFull())
        printf("\n\n棋逢对手，201621123011与AI平局\n");

    return 0;
}

void Initmap()
{
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
            chessboard[i][j] = 1;
}

void Showmap()
{
	printf("\n");
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
        {
            if (chessboard[i][j] == 1)    //"1"代表空
                printf("□");
            if (chessboard[i][j] == 2)    //"2"代表人
                printf("■");
            if (chessboard[i][j] == 5)    //"5"代表电脑
                printf("●");
        }
        printf("\n");
    }
}

bool isWin()
{
    int sum = 0;
    for (int i = 0; i < ROW; i++)      //对每行判断是否获胜
    {
        for(int j = 0; j < COL; j++)
            sum += chessboard[i][j];

        if(sum == 6)
        {
            printf("恭喜你，击败了AI！\n");
            return true;
        }
        if(sum == 15)
        {
            printf("很遗憾，AI获得了胜利！\n");
            return true;
        }
        sum = 0;
    }

    for (int j = 0; j < ROW; j++)      //对每列判断是否获胜
    {
        for(int i = 0; i < COL; i++)
            sum += chessboard[i][j];

        if(sum == 6)
        {
            printf("恭喜你，击败了AI！\n");
            return true;
        }
        if(sum == 15)
        {
            printf("很遗憾，AI获得了胜利！\n");
            return true;
        }
        sum = 0;
    }

    for (int i = 0; i < ROW; i++)     //对对角线判断是否获胜
        sum += chessboard[i][i];
    if (sum == 6)
    {
        printf("恭喜你，击败了AI！\n");
        return true;
    }
    if (sum == 15)
    {
        printf("很遗憾，AI获得了胜利！\n");
        return true;
    }

    sum = 0;
    for (int i = 0; i < ROW; i++)     //对反对角线判断是否获胜
        sum += chessboard[i][2 - i];
    if (sum == 6)
    {
        printf("恭喜你，击败了AI！\n");
        return true;
    }
    if (sum == 15)
    {
        printf("很遗憾，AI获得了胜利！\n");
        return true;
    }

    return false;
}

bool isFull()
{
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
            if (chessboard[i][j] == 1)
                return false;
    return true;
}

void HumanPlay()
{
    int x, y;
    printf("请输入棋子的坐标(1~3,1~3):");
    scanf("%d,%d", &x,&y);

    while (x < 1 || x>3 || y < 1 || y>3)
    {
        printf("\n请正确输入！\n");
        printf("x,y均属于1~3\n\n");
        printf("请输入棋子的坐标(1~3,1~3):");
		scanf("%d,%d", &x,&y);
    }

    while (chessboard[3 - y][x - 1] != 1)
    {
        printf("\n\n该位置已被占用！\n");
        printf("请选择正确的位置\n\n");
        Sleep(1000);
		printf("请输入棋子的坐标(1~3,1~3):");
		scanf("%d,%d", &x,&y);
    }

    chessboard[3 - y][x - 1] = 2;
}

void PcPlay()
{
    int sum = 0;
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
            score[i][j] = 0;

    // 对每行进行分数统计
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
            sum += chessboard[i][j];

        switch (sum)
        {
        case 3:                     //1+1+1;重要性：最低;权重：1
            for (int k = 0; k < COL; k++)
            {
                if (chessboard[i][k] == 1)
                    score[i][k] += 1;
            }
            break;
        case 4:                     //1+1+2;重要性：次低;权重：10
            for (int k = 0; k < COL; k++)
            {
                if (chessboard[i][k] == 1)
                    score[i][k] += 10;
            }
            break;
        case 8:                    //1+2+5;重要性：较低，权值50
            for (int k = 0; k < COL; k++)
            {
                if (chessboard[i][k] == 1)
                    score[i][k] += 50;
            }
            break;
        case 7:                     //1+1+5;重要性：较高;权重：200
            for (int k = 0; k < COL; k++)
            {
                if (chessboard[i][k] == 1)
                    score[i][k] += 200;     //把行列的重要性比对角线高
            }
            break;
        case 5:                     //1+2+2;重要性：次高;权重：500
            for (int k = 0; k < COL; k++)
            {
                if (chessboard[i][k] == 1)
                    score[i][k] += 500;
            }
            break;
        case 11:                     //1+5+5;重要性：最高;权重：1000
            for (int k = 0; k < COL; k++)
            {
                if (chessboard[i][k] == 1)
                    score[i][k] += 1000;
            }
            break;
        }
        sum = 0;
    }

    // 对每列进行分数统计
    for (int j = 0; j < COL; j++)
    {
        for (int i = 0; i < ROW; i++)
            sum += chessboard[i][j];

        switch (sum)
        {
        case 3:                   
            for (int k = 0; k < COL; k++)
            {
                if (chessboard[k][j] == 1)
                    score[k][j] += 1;
            }
            break;
        case 4:                    
            for (int k = 0; k < COL; k++)
            {
                if (chessboard[k][j] == 1)
                    score[k][j] += 10;
            }
            break;
        case 8:                    
            for (int k = 0; k <
                COL; k++)
            {
                if (chessboard[k][j] == 1)
                    score[k][j] += 50;
            }
            break;
        case 7:                    
            for (int k = 0; k < COL; k++)
            {
                if (chessboard[k][j] == 1)     //1+1+5;重要性：较高;权重：200
                    score[k][j] += 200;  
            }
            break;
        case 5:                    
            for (int k = 0; k < COL; k++)
            {
                if (chessboard[k][j] == 1)
                    score[k][j] += 500;
            }
            break;
        case 11:                  
            for (int k = 0; k < COL; k++)
            {
                if (chessboard[k][j] == 1)
                    score[k][j] += 1000;
            }
            break;
        }
        sum = 0;
    }

    //对对角线进行分数统计
    for (int i = 0; i < ROW; i++)
        sum += chessboard[i][i];
    switch (sum)
    {
    case 3:                    
        for (int i = 0; i < COL; i++)
        {
            if (chessboard[i][i] == 1)
                score[i][i] += 1;
        }
        break;
    case 4:                   
        for (int i = 0; i < COL; i++)
        {
            if (chessboard[i][i] == 1)
                score[i][i] += 10;
        }
        break;
    case 8:                
        for (int i = 0; i < COL; i++)
        {
            if (chessboard[i][i] == 1)
                score[i][i] += 50;
        }
        break;
    case 7:                     //1+1+5;权重：100
        for (int i = 0; i < COL; i++)
        {
            if (chessboard[i][i] == 1)
                score[i][i] += 100;
        }
        break;
    case 5:                
        for (int i = 0; i < COL; i++)
        {
            if (chessboard[i][i] == 1)
                score[i][i] += 500;
        }
        break;
    case 11:                    
        for (int i = 0; i < COL; i++)
        {
            if (chessboard[i][i] == 1)
                score[i][i] += 1000;
        }
        break;
    }

    // 对反对角线进行分数统计
    sum = 0;
    for (int i = 0; i < ROW; i++)
        sum += chessboard[i][2 - i];
    switch (sum)
    {
    case 3:                    
        for (int i = 0; i < COL; i++)
        {
            if (chessboard[i][2 - i] == 1)
                score[i][2 - i] += 1;
        }
        break;
    case 4:                    
        for (int i = 0; i < COL; i++)
        {
            if (chessboard[i][2 - i] == 1)
                score[i][2 - i] += 10;
        }
        break;
    case 8:
        for (int i = 0; i < COL; i++)
        {
            if (chessboard[i][2 - i] == 1)
                score[i][2 - i] += 50;
        }
        break;
    case 7:                     
        for (int i = 0; i < COL; i++)
        {
            if (chessboard[i][2 - i] == 1)    //1+1+5;权重：100
                score[i][2 - i] += 100;
        }
        break;
    case 5:                   
        for (int i = 0; i < COL; i++)
        {
            if (chessboard[i][2 - i] == 1)
                score[i][2 - i] += 500;
        }
        break;
    case 11:                    
        for (int i = 0; i < COL; i++)
        {
            if (chessboard[i][2 - i] == 1)
                score[i][2 - i] += 1000;
        }
        break;
    }

    int maxRow = 0, maxCol = 0;
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
        {
            if (score[i][j] > score[maxRow][maxCol])
            {
                maxRow = i;
                maxCol = j;
            }
        }
    chessboard[maxRow][maxCol] = 5;
}
