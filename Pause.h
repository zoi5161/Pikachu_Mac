#include "Header.h"

void inputBackgroundPause(string backgroundPause[])
{
    ifstream fin;
    fin.open("BackgroundPause.txt");
    int i = 0;
    while(i <= 3)
    {
        getline(fin, backgroundPause[i], '\n');
        i++;
    }
    fin.close();
}

void inputPause(int &dirPause)
{
    halfdelay(1);

    int c = getch();
    switch(c)
    {
        case KEY_UP:
            dirPause = 1;
            break;
        case KEY_DOWN:
            dirPause = 2;
            break;
        case ' ':
            dirPause = 3;
            break;
        case '\n':
            dirPause = 3;
            break;
        default:
            break;
    }
}

void drawPause(int choosePause, string backgroundPause[], char boxExit[], char boxResume[])
{
    clear();

    attron(COLOR_PAIR(3));
    for(int i = passingHeightMenu; i <= passingHeightMenu + 3; i++)
        for(int j = 0; j <= 26; j++)
            mvprintw(i, j + 80, "%c", backgroundPause[i-12][j]);
    attroff(COLOR_PAIR(3));
    
    if(choosePause == 1)
    {
        attron(COLOR_PAIR(1));
        for(int i = passingHeightMenu + 8; i <=passingHeightMenu + 10; i++)
        {
            for(int j=5; j <= 22; j++)
            {
                if(i == passingHeightMenu + 9 && (j == 5 || j == 22))
                    mvprintw(i,  j + 80, "|");
                else if(j != 5 && j != 22 && i != passingHeightMenu + 9)
                    mvprintw(i,  j + 80, "-");
                else if(j == 11 && i == passingHeightMenu + 9)
                    mvprintw(i,  j + 80, "%s", boxResume);
            }
        }
        attroff(COLOR_PAIR(1));
    }
    else
    {
        attron(COLOR_PAIR(3));
        for(int i = passingHeightMenu + 8; i <=passingHeightMenu + 10; i++)
        {
            for(int j=5; j <= 22; j++)
            {
                if(i == passingHeightMenu + 9 && (j == 5 || j == 22))
                    mvprintw(i,  j + 80, "|");
                else if(j != 5 && j != 22 && i != passingHeightMenu + 9)
                    mvprintw(i,  j + 80, "-");
                else if(j == 11 && i == passingHeightMenu + 9)
                    mvprintw(i,  j + 80, "%s", boxResume);
            }
        }
        attroff(COLOR_PAIR(3));
    }

    if(choosePause == 2)
    {
        attron(COLOR_PAIR(1));
        for(int i = passingHeightMenu + 13; i <=passingHeightMenu + 15; i++)
        {
            for(int j=5; j <= 22; j++)
            {
                if(i == passingHeightMenu + 14 && (j == 5 || j == 22))
                    mvprintw(i,  j + 80, "|");
                else if(j != 5 && j != 22 && i != passingHeightMenu + 14)
                    mvprintw(i,  j + 80, "-");
                else if(j == 12 && i == passingHeightMenu + 14)
                    mvprintw(i,  j + 80, "%s", boxExit);
            }
        }
        attroff(COLOR_PAIR(1));
    }
    else
    {
        attron(COLOR_PAIR(3));
        for(int i = passingHeightMenu + 13; i <=passingHeightMenu + 15; i++)
        {
            for(int j=5; j <= 22; j++)
            {
                if(i == passingHeightMenu + 14 && (j == 5 || j == 22))
                    mvprintw(i,  j + 80, "|");
                else if(j != 5 && j != 22 && i != passingHeightMenu + 14)
                    mvprintw(i,  j + 80, "-");
                else if(j == 12 && i == passingHeightMenu + 14)
                    mvprintw(i,  j + 80, "%s", boxExit);
            }
        }
        attroff(COLOR_PAIR(3));
    }


    refresh();
}

void logicPause(int &dirPause, int &choosePause, bool &endPause, bool &endGame)
{
    switch(dirPause)
    {
        case 1:
            if(choosePause == 1)
                choosePause = 2;
            else
                choosePause--;
            break;
        case 2:
            if(choosePause == 2)
                choosePause = 1;
            else
                choosePause++;
            break;
        case 3:
            if(choosePause == 2)
            {
                endPause = true;
                endGame = true;
            }
            else
                endPause = true;
            break;
        default:
            break;
    }
    dirPause = 0;
}