#include "Header.h"

void draw(int height, int width, int passingHeight, int passingWidth, int x, int y, int prevX, int prevY, int hour, int minute, int second, int score, int last, int round, bool modeHard, char boxConfirm[], string backgroundGame[],char idxObj[][widthB+2], int idxNum[][widthB+2], int line[][widthB+2], int lineOut[][widthB+3], int lineEnd[][widthB+2], int lineHelp[][widthB+2], int resetNum[][widthB+2], int resetLine[][widthB+2], int resetLineOut[][widthB+3], int resetLineEnd[][widthB+2], int greenBlock[][widthB+2], int redBlock[][widthB+2])
{
    clear();
    
    attron(COLOR_PAIR(3));
    printw("Time: %02d:%02d:%02d           Score: %d", hour, minute, second, score);
    attroff(COLOR_PAIR(3));

    std::this_thread::sleep_for(std::chrono::milliseconds(1));

    for(int i=0; i<height+2; i++)
    {
        for(int j=0; j<width+2; j++)
        {
            // Bảng Confirm
            if(last == 0)
            {
                attron(COLOR_PAIR(1));
                for(int u = 0; u <= 2; u++)
                {
                    for(int v = 0; v <= 48; v++)
                    {
                        if((u == 0 || u == 2) && v != 0 && v != 48)
                            mvprintw(u + passingHeight + height + 6, v + 71, "-");
                        else if((v == 0 || v == 48) && u != 0 && u != 2)
                            mvprintw(u + passingHeight + height + 6, v + 71, "|");
                        else if(u == 1 && v == 6)
                            mvprintw(u + passingHeight + height + 6, v + 71, "%s", boxConfirm);
                    }
                }
                attroff(COLOR_PAIR(1));
            }

            // Vẽ đường nối nếu nằm ngoài bảng
            if(lineOut[i][j] != 0 && i == 0)
            {
                attron(COLOR_PAIR(1));
                mvprintw(i + passingHeight - 1, j + passingWidth +1, "-");
                attroff(COLOR_PAIR(1));
                lineOut[i][j]--;
            }
            else if(lineOut[i][j] != 0 && i == height+1)
            {
                attron(COLOR_PAIR(1));
                mvprintw(i + passingHeight + 1, j + passingWidth +1, "-");
                attroff(COLOR_PAIR(1));
                lineOut[i][j]--;
            }

            if(lineOut[i][j] != 0 && j == 0)
            {
                attron(COLOR_PAIR(1));
                mvprintw(i + passingHeight, j + passingWidth - 1, "|");
                attroff(COLOR_PAIR(1));
                lineOut[i][j]--;
            }
            else if(lineOut[i][j] != 0 && j == width+1)
            {
                attron(COLOR_PAIR(1));
                mvprintw(i + passingHeight, j + passingWidth + 1, "|");
                attroff(COLOR_PAIR(1));
                lineOut[i][j]--;
            }

            // Vẽ đường nối trong bảng
            if(line[i][j] != 0 && (i%5 == 3 ||  j%10 == 0) ) // Vẽ đường nối ngang
            {
                attron(COLOR_PAIR(1));
                if(lineEnd[i][j] == 3)
                    mvprintw(i + passingHeight, j + passingWidth, ">");
                else if(lineEnd[i][j] == 4)
                    mvprintw(i + passingHeight, j + passingWidth, "<");
                else
                {
                    if(line[i-1][j] == 1 || line[i+1][j] == 1)
                        mvprintw(i + passingHeight, j + passingWidth, "|");
                    else
                        mvprintw(i + passingHeight, j + passingWidth, "-");
                }
                attroff(COLOR_PAIR(1));       
                line[i][j]--;
                if(line[i][j] == 0)
                    lineEnd[i][j] = 0;   
            }
            else if(line[i][j] != 0 && (j%5 == 0 || (i%5 == 0))) // Vẽ đường nối dọc
            {
                attron(COLOR_PAIR(1));
                if(lineEnd[i][j] == 1)
                    mvprintw(i + passingHeight, j + passingWidth, "^");
                else if(lineEnd[i][j] == 2)
                    mvprintw(i + passingHeight, j + passingWidth, "v");
                else
                {
                    if(line[i][j-1] == 1 || line[i][j+1] == 1)
                        mvprintw(i + passingHeight, j + passingWidth, "-");
                    else
                        mvprintw(i + passingHeight, j + passingWidth, "|");
                }
                attroff(COLOR_PAIR(1));       
                line[i][j]--;
                if(line[i][j] == 0)
                    lineEnd[i][j] = 0;         
            }
            else if(greenBlock[i][j] != 0)
            {
                attron(COLOR_PAIR(11));
                mvprintw(i + passingHeight, j + passingWidth, " ");
                attroff(COLOR_PAIR(11));
                greenBlock[i][j]--;
            }
            else if(redBlock[i][j] != 0)
            {
                attron(COLOR_PAIR(10));
                mvprintw(i + passingHeight, j + passingWidth, " ");
                attroff(COLOR_PAIR(10));
                redBlock[i][j]--;
            }
            else if(j >= x && j - x <= 9 && i >= y && i - y <= 4 && idxNum[i][j] == 300)
            {
                attron(COLOR_PAIR(8));
                mvprintw(i + passingHeight, j + passingWidth, " ");
                attroff(COLOR_PAIR(8));
            }
            else if((idxNum[i][j] == 300 || (i%5 == 0 && j%10 == 0)))
            {
                if(i%5 == 0 && j%10 == 0 && ((j == 0 && idxNum[i][j+1] != 300) || (j == width + 1 && idxNum[i][j-1] != 300) || idxNum[i][j+1] != 300))
                {
                    if((j >= x && j - x <= 9 && i >= y && i - y <= 4) || (j >= prevX && j - prevX <= 9 && i >= prevY && i - prevY <= 4))
                    {
                        attron(COLOR_PAIR(8));
                        mvprintw(i + passingHeight, j + passingWidth, " ");
                        attroff(COLOR_PAIR(8));
                    }
                    else
                    {
                        attron(COLOR_PAIR(9));
                        mvprintw(i + passingHeight, j + passingWidth, " ");
                        attroff(COLOR_PAIR(9));
                    }
                }
                else
                {
                    attron(COLOR_PAIR(3));
                    mvprintw(i + passingHeight, j + passingWidth, "%c", backgroundGame[i][j]);
                    attroff(COLOR_PAIR(3));
                }
            }
            else if(j%5 == 0 && j%10 != 0 &&  i%5 == 3 && idxNum[i][j] != 300 && modeHard)
            {
                if((j >= x && j - x <= 9 && i >= y && i - y <= 4) || (j >= prevX && j - prevX <= 9 && i >= prevY && i - prevY <= 4))
                {
                    attron(COLOR_PAIR((int)idxObj[i][j] % 8));
                    mvprintw(i + passingHeight, j + passingWidth, "%c", idxObj[i][j]);
                    attroff(COLOR_PAIR((int)idxObj[i][j] % 8));
                }
                else
                {
                    attron(COLOR_PAIR(9));
                    mvprintw(i + passingHeight, j + passingWidth, " ");
                    attroff(COLOR_PAIR(9));
                }
            }
            else if(j%5 == 0 && j%10 != 0 &&  i%5 == 3 && idxNum[i][j] != 300)
            {
                attron(COLOR_PAIR((int)idxObj[i][j] % 8));
                mvprintw(i + passingHeight, j + passingWidth, "%c", idxObj[i][j]);
                attroff(COLOR_PAIR((int)idxObj[i][j] % 8));
            }
            else if(j >= x && j - x <= 9 && i >= y && i - y <= 4)
            {
                attron(COLOR_PAIR(8));
                mvprintw(i + passingHeight, j + passingWidth, " ");
                attroff(COLOR_PAIR(8));
            }
            else if(j >= prevX && j - prevX <= 9 && i >= prevY && i - prevY <= 4)
            {
                attron(COLOR_PAIR(8));
                mvprintw(i + passingHeight, j + passingWidth, " ");
                attroff(COLOR_PAIR(8));
            }
            else if(i%5 == 0 && j%10 != 0)
            {
                if(lineHelp[i][j] != 0)
                {
                    attron(COLOR_PAIR(1));
                    mvprintw(i + passingHeight, j + passingWidth, "_");
                    attroff(COLOR_PAIR(1));
                    lineHelp[i][j]--;
                }
                else
                {
                    attron(COLOR_PAIR(4));
                    mvprintw(i + passingHeight, j + passingWidth, "_");
                    attroff(COLOR_PAIR(4));
                }
            }
            else if(j == 0 || j == width + 1 || j%10 == 0)
            {
                if(lineHelp[i][j] != 0)
                {
                    attron(COLOR_PAIR(1));
                    mvprintw(i + passingHeight, j + passingWidth, "|");
                    attroff(COLOR_PAIR(1));
                    lineHelp[i][j]--;
                }
                else
                {
                    attron(COLOR_PAIR(4));
                    mvprintw(i + passingHeight, j + passingWidth, "|");
                    attroff(COLOR_PAIR(4));
                }
            }
        }
    }
    refresh();
}
