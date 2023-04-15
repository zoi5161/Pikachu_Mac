#include "Header.h"

void inputFinish(bool &endFinish)
{
    halfdelay(1);

    int c = getch();
    
    if(c == '\n')
        endFinish = true;
}

void inputBackgroundWinner(string backgroundWinner[])
{
    ifstream fin;
    fin.open("BackgroundWinner.txt");
    int i = 0;
    while(i <= 34)
    {
        getline(fin, backgroundWinner[i], '\n');
        i++;
    }
    fin.close();
}

void inputBackgroundLoser(string backgroundLoser[])
{
    ifstream fin;
    fin.open("BackgroundLoser.txt");
    int i = 0;
    while(i <= 34)
    {
        getline(fin, backgroundLoser[i], '\n');
        i++;
    }
    fin.close();
}

void drawFinish(string backgroundWinner[], string backgroundLoser[], int totalTime, int score, bool win)
{
    clear();

    for(int i = 0; i <= 34; i++)
    {
        for(int j = 0; j <= 71; j++)
        {   
            if(win)
            {
                if(i == 11 && ((j >= 6 && j <= 34) || (j >= 42 && j <= 66)))
                {
                    attron(COLOR_PAIR(1));
                    if(j == 27)
                        mvprintw(i + 11, j + 50, "%02d:%02d", ((14 - totalTime)*60 + totalTime)/60, ((14 - totalTime)*60 + totalTime)%60);
                    else if(j == 59)
                        mvprintw(i + 11, j + 50, "%d", score);
                    else if(j < 27 || (j > 31 && j < 59) || j > 63)
                        mvprintw(i + 11, j + 50, "%c", backgroundWinner[i][j]);
                    attroff(COLOR_PAIR(1));
                }
                else
                {
                    attron(COLOR_PAIR(3));
                    mvprintw(i + 11, j + 50, "%c", backgroundWinner[i][j]);
                    attroff(COLOR_PAIR(3));
                }
            }
            else
            {
                if(i == 14 && j >= 40 && j <= 58)
                {
                    attron(COLOR_PAIR(1));
                    if(j == 53)
                        mvprintw(i + 11, j + 50, "%d", score);
                    else if(j < 53 || j >= 56)
                        mvprintw(i + 11, j + 50, "%c", backgroundLoser[i][j]);
                    attroff(COLOR_PAIR(1));
                }
                else
                {
                    attron(COLOR_PAIR(3));
                    mvprintw(i + 11, j + 50, "%c", backgroundLoser[i][j]);
                    attroff(COLOR_PAIR(3));
                }
            }
        }
    }

    refresh();
}