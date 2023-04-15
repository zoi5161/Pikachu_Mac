#include "Header.h"

void setupGame(int height, int width, int &x, int &y, int &prevX, int &prevY, int &score, int &choosePause, bool &confirm, bool &modeHard, int round, int Map, int &last, int &dir, int &hour,int &minute, int &second, int &millisec, int &totalTime,int obj[27], int randomObj, char idxObj[][widthB+2], int idxNum[][widthB+2], int line[][widthB+2], int lineOut[][widthB+3], int lineEnd[][widthB+2], int greenBlock[][widthB+2], int redBlock[][widthB+2])
{
	x = 1;
	y = 1;
    prevX = 200;
    prevY = 200;

    last = ((height+1)/5)*((width+1)/10)/2;
    dir = 0;
    hour = 0;
    millisec = 0;
    greenBlock = 0;
    redBlock = 0;
    confirm = false;
    choosePause = 1;

    if((!modeHard && round == 1) || modeHard)
    {
        score = 0;
        totalTime = 0;
        second = 0;
    }

    if(!modeHard)
    {
        if(round == 1)
            minute = 5;
        else if(round == 2)
        {
            totalTime += (4-minute)*60 + 60 - second;
            minute = 10;
            second = 0;
        }
        else if(round == 3)
        {
            totalTime += (9-minute)*60 + 60 - second;
            minute = 15;
            second = 0;
        }
    }
    else
    {
        if(Map == 1)
            minute = 5;
        else if(Map == 2)
            minute = 10;
        else if(Map == 3)
            minute = 15;
    }


    for(int i=65; i<=90; i++)
        obj[i] = 0;

    for(int i=0; i<((height+1)/5)*((width+1)/10)/2; i++)
        obj[(rand()%26)+65] += 2;
    
    for(int i=3; i<height+2; i += 5)
        for(int j=5; j<width+2; j += 10)
        {
            randomObj = (rand()%26)+65;
            while(obj[randomObj] == 0)
                randomObj = (rand()%26)+65;
            idxObj[i][j] = char(randomObj);
            idxNum[i-2][j-4] = randomObj;
            obj[randomObj]--;
        }

    for(int i=0; i<height+2; i++)
        for(int j=0; j<width+2; j++)
        {
            if(i%5 == 0 && j%10 == 0)
                idxNum[i][j] = 300;
            else if(i == 0 || i == height+1 || j == 0 || j == width+1)
                idxNum[i][j] = 301;
            else if(i%5 == 0 || j%10 == 0)
                idxNum[i][j] = 302;
            else if(i%5 == 3 && j%5 == 0 && j%10 != 0)
                idxNum[i][j] = 500;
            
            line[i][j] = 0;
            lineEnd[i][j] = 0;
            lineOut[i][j] = 0;
        }
}

void runTime(int &hour, int &minute, int &second, int &millisec, bool &endGame)
{
    millisec+=10;
    if(millisec == 100)
    {
        if(hour == 0 && minute == 0 && second == 0)
            endGame = true;
        else if(second == 0 && minute == 0)
        {
            hour--;
            minute = 59;
            second = 59;
        }
        else if(second == 0)
        {
            minute--;
            second = 59;
        }
        else
            second--;
        millisec = 0;
    }
}
