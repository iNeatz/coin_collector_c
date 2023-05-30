#include <stdio.h>
#include <conio.h>
#include <graphics.h>
#include <time.h>
#include <stdlib.h>

int isGameOver = 0, x = 280, y = 280, coinExists = 0, coinX, coinY, score = 0, highScore;
char directionOfMovement='d', controlKey;

FILE *fp;

void gameOver(int score)
{
    isGameOver = 1;
    char scoreOut[50], highScoreOut[50];

    sprintf(scoreOut, "Your Score is: %d", score);

    //Reading HighScore
    fp = fopen("highscore.txt", "r");
    fscanf(fp, "%d", &highScore);
    fclose(fp);

    outtextxy(300,225,"Game Over!!");
    outtextxy(290,250,scoreOut);


    if(score > highScore)
    {
        fp = fopen("highscore.txt", "w");
        fprintf(fp, "%d", score);
        fclose(fp);
    }

    if(score <= highScore)
    {
        sprintf(highScoreOut, "HighScore: %d", highScore);
        outtextxy(300,275,highScoreOut);
    }

}

void boundaryInit()
{
    //Boundary Initialization
    rectangle(10,10,600,450);
    rectangle(12,12,598,448);
}

void charInit(int x, int y)
{
    //Character Initialization
    bar(x,y,x+70,y+70);
}

void coinInit()
{
    //Random coordinates
    if(coinExists == 0)
    {
        srand(time(0));
        coinX = 30 + rand() % 530;
        coinY = 30 + rand() % 380;
        coinExists = 1;
    }

    //Coin Initialization
    fillellipse(coinX,coinY,10,10);
}

void charControl()
{
    //Getting movement key from user
    if(kbhit())
    {
        controlKey = getch();
        if(controlKey == 'd' || controlKey == 'w' || controlKey == 's' || controlKey=='a')
            directionOfMovement = controlKey;
    }

    //Moving character to the right direction
    if(x <= 528 && directionOfMovement=='d')
    {
        x+=2;
        charInit(x,y);
    }

    //Moving character to the downward direction
    if((y+70) <= 448 && directionOfMovement=='s')
    {
        y+=2;
        charInit(x,y);
    }

    //Moving character to the upward direction
    if(y >= 12 && directionOfMovement=='w')
    {
        y-=2;
        charInit(x,y);
    }

    //Moving character to the upward direction
    if(x >= 12 && directionOfMovement=='a')
    {
        x-=2;
        charInit(x,y);
    }

    if(x >= 528 || (y+70) >= 448 || y <= 12 || x <= 12)
        gameOver(score);
}

void coinCollect()
{
    //Collision Effect
    if(coinX >= x && coinX <= (x+70) && coinY >= y && coinY <= (y+70))
    {
        coinExists = 0;
        score+=10;
    }
}

void scoreDisplay(int score)
{
    char scoreText[50];
    sprintf(scoreText, "%d", score);
    outtextxy(570,25,scoreText);
}

int main()
{
    int gd = DETECT, gm;
    initgraph(&gd, &gm, "C:\\TURBOC3\\BGI");

    charInit(x,y);

    while(!isGameOver)
    {
        coinInit();
        boundaryInit();
        scoreDisplay(score);
        charControl();
        coinCollect();

        delay(1);
        cleardevice();
    }

    if(isGameOver)
        gameOver(score);

    getch();
    closegraph();
    return 0;
}
