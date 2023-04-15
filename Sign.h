#include "Header.h"

bool checkPass(char user[], char pass[])
{
    char userClone[20], passClone[20];
    ifstream fin("account.bin", ios::binary);
    fin.seekg(0, ios::beg);
    while(!fin.eof())
    {
        fin.read(userClone, 20);
        fin.read(passClone, 20);
        if(strcmp(userClone, user) == 0 && strcmp(passClone, pass) == 0)
            return true;
    }
    fin.close();
    return false;
}

bool availableAccount(char user[])
{
    char userClone[20];
    ifstream fin("account.bin", ios::binary);
    fin.seekg(0, ios::beg);
    while(!fin.eof())
    {
        fin.read(userClone, 20);
        if(strcmp(userClone, user) == 0)
            return true;
    }
    fin.close();
    return false;
}

void createAccount(char user[], char pass[])
{
    ofstream fout("account.bin", ios::binary | ios::app);
    fout.write(user, 20);
    fout.write(pass, 20);
    fout.close();
}

void inputSign(char user[], char pass[], bool &endUser, bool &endPass, bool &endSign, bool &endSeen, bool &endGM, bool &warnAcc, bool &signUp, int &chooseMenu)
{
    halfdelay(1);
    
    int ch;
    char c;

    ch = getch();
    c = char(ch);

    if(ch == '=')
    {
        for(int i = 0; i < strlen(user); i++)
            user[i] = '\0';
        for(int i = 0; i < strlen(pass); i++)
            pass[i] = '\0';   
        endUser = false;
        endPass = true;
        endSign = true;
        endSeen = true;
        warnAcc = false;   
    }

    if(ch == '\t')
    {
        if(endSeen)
            endSeen = false;
        else 
            endSeen = true;
    }

    if(endUser && endPass)
    {
        if((!signUp && checkPass(user, pass)) || signUp)
            endSign = true;
        else
            endPass = false;
    }

    if(!endPass)
    {
        if(availableAccount(user) && signUp)
            warnAcc = true;
        else if(signUp)
            warnAcc = false;
        else if(availableAccount(user) && !signUp)
            warnAcc = false;
        else if(!signUp)
            warnAcc = true;
        
        if(!signUp && ch == '\n' && warnAcc)
        {
            signUp = true;
            endPass = true;
            endUser = false;
            chooseMenu = 1;
        }

        if(ch == KEY_UP)
        {
            endPass = true;
            endUser = false;
        }
        else
        {
            if(((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')) && strlen(pass) < 18)
            {
                pass[strlen(pass)] = c;
                pass[strlen(pass)] = '\0';
            }
            else if(strlen(pass) > 0 && ch == '-')
                pass[strlen(pass)-1] = '\0';
            else if(ch == '\n' && strlen(pass) > 0 && !warnAcc)
            {
                endPass = true;
                endGM = false;
                if(signUp)
                    createAccount(user, pass);
                return;
            }
        }
    }
    
    if(!endUser)
    {   
        warnAcc = false;
        if((ch == KEY_DOWN || ch == '\n') && strlen(user) > 0)
        {
            endUser = true;
            endPass = false;
        }
        else
        {
            if(((c >= 'a' && c <= 'z') || (c >= '0' && c <= '9') || (c >= 'A' && c <= 'Z')) && strlen(user) < 18)
            {
                user[strlen(user)] = c;
                user[strlen(user)] = '\0';
            }
            else if(strlen(user) > 0 && ch == '-')
                user[strlen(user)-1] = '\0';
        }
    }
}

void inputBackgroundSign(string backgroundSign[], string s)
{
    ifstream fin;
    fin.open(s);
    int i = 0;
    while(i <= 36)
    {
        getline(fin, backgroundSign[i], '\n');
        i++;
    }
    fin.close();
}

void drawSign(string backgroundSign[], char user[], char pass[], bool endSeen, bool &warnAcc, bool &signUp)
{
    clear();

    for(int i = 0; i <= 36; i++)
        for(int j = 0; j <= 184; j++)
        {
            if(warnAcc && i == 29 && j >= 59 && j <= 84 && signUp)
            {
                attron(COLOR_PAIR(1));
                mvprintw(i + 5, j + 20, "%c", backgroundSign[i][j]);
                attron(COLOR_PAIR(1));
            }
            else if(!warnAcc && (i == 28 || i == 29) && j >= 48 && j <= 99 && signUp)
            {
                attron(COLOR_PAIR(9));
                mvprintw(i + 5, j + 20, " ");
                attron(COLOR_PAIR(9));
            }
            else if(warnAcc && (i == 28 || i == 29) && j >= 48 && j <= 99 && !signUp)
            {
                attron(COLOR_PAIR(1));
                mvprintw(i + 5, j + 20, "%c", backgroundSign[i][j]);
                attron(COLOR_PAIR(1));
            }
            else if(!warnAcc && (i == 28 || i == 29) && j >= 48 && j <= 99 && !signUp)
            {
                attron(COLOR_PAIR(9));
                mvprintw(i + 5, j + 20, " ");
                attron(COLOR_PAIR(9));
            }
            else if(i == 22 && j >= 67 && j < (int)(67 + strlen(user)))
            {
                attron(COLOR_PAIR(1));
                mvprintw(i + 5, j + 20, "%c", user[j-67]);
                attron(COLOR_PAIR(1));
            }
            else if(i == 24 && j >= 67 && j < (int)(67 + strlen(pass)))
            {
                if(endSeen)
                {
                    attron(COLOR_PAIR(1));
                    mvprintw(i + 5, j + 20, "*");
                    attron(COLOR_PAIR(1));
                }
                else
                {
                    attron(COLOR_PAIR(1));
                    mvprintw(i + 5, j + 20, "%c", pass[j-67]);
                    attron(COLOR_PAIR(1));
                }
            }
            else if(i >= 23 && i <= 25 && j >= 91 && j <= 98)
            {
                if(endSeen)
                {
                    attron(COLOR_PAIR(3));
                    mvprintw(i + 5, j + 20, "%c", backgroundSign[i][j]);
                    attron(COLOR_PAIR(3));
                }
                else
                {
                    attron(COLOR_PAIR(1));
                    mvprintw(i + 5, j + 20, "%c", backgroundSign[i][j]);
                    attron(COLOR_PAIR(1));
                }
            }
            else if(i >= 21 && i <= 25 && j >= 55 && j <= 89)
            {
                attron(COLOR_PAIR(3));
                mvprintw(i + 5, j + 20, "%c", backgroundSign[i][j]);
                attron(COLOR_PAIR(3));
            }
            else if(i >= 10 && i <= 15 && j >= 37 && j <= 108)
            {
                attron(COLOR_PAIR(6));
                mvprintw(i + 5, j + 20, "%c", backgroundSign[i][j]);
                attron(COLOR_PAIR(6));
            }
            else if(i >= 35)
            {
                attron(COLOR_PAIR(1));
                mvprintw(i + 5, j + 20, "%c", backgroundSign[i][j]);
                attron(COLOR_PAIR(1));
            }
            else
            {
                attron(COLOR_PAIR(2));
                mvprintw(i + 5, j + 20, "%c", backgroundSign[i][j]);
                attron(COLOR_PAIR(2));
            }
        }
    refresh();
}