#include <iostream>
#include <string>
#include <cstdlib>
#include <chrono>
#include <thread>
#include <fstream>
#include <cmath>
#include <ctime>
#include <unistd.h>
#include <windows.h>
#include <mmsystem.h>
#if defined _WIN32
#include <conio.h>
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
#include <unistd.h>
#include <termios.h>
#endif

using namespace std;

int count_m = 0;
class Game_board;
void Header(Game_board &);
// char getUserInput();
// class Gun;

// void load(Game_board);
// int colectAmmo();
void Clear_scr()
{
    cout << "\033[1;1H"; // Move cursor to the top left corner

#if defined _WIN32
    system("cls");
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
    system("clear");
#elif defined(__APPLE__)
    system("clear");
#endif
}

class Round
{
public:
    int RoundNumber;
    Round(int number = 0) : RoundNumber(number)
    {
    }
};

// game sounds

// void startSound()
// {
//     PlaySound(TEXT("exit.wav"), NULL, SND_SYNC);
// }
// void menuSound()
// {
//     PlaySound(TEXT("link.wav"), NULL, SND_SYNC);
// }
// void fireSound()
// {
//     PlaySound(TEXT("bomb_explosion.wav"), NULL, SND_SYNC);
// }
// void winSound()
// {
//     PlaySound(TEXT("round_end.wav"), NULL, SND_SYNC);
// }
// void loseSound()
// {
//     PlaySound(TEXT("death.wav"), NULL, SND_SYNC);
// }

class Kill
{
public:
    int KillNumber;
    Kill(int number = 0) : KillNumber(number)
    {
    }

    void count(Round &round)
    {

        cout << "\033[" << 10 << ";" << 25 << "H";

        if (KillNumber % 14 == 1)
        {
            cout << "First blood";
        }
        if (KillNumber % 14 == 2)
        {
            cout << "Double kill";
        }
        if (KillNumber % 14 == 3)
        {
            if (round.RoundNumber % 2 == 0)
            {
                cout << "Triple kill";
            }
            else if (round.RoundNumber % 2 != 0)
            {
                cout << "Hattrick";
            }
        }
        if (KillNumber % 14 == 4)
        {
            cout << "Team Killer";
        }
        if (KillNumber % 14 == 5)
        {
            cout << "Headshot";
        }
        if (KillNumber % 14 == 6)
        {
            cout << "Rampage";
        }
        if (KillNumber % 14 == 7)
        {
            cout << "killing Spree";
        }
        if (KillNumber % 14 == 8)
        {
            cout << "Unstoppable";
        }
        if (KillNumber % 14 == 9)
        {
            cout << "Monster Kill";
        }
        if (KillNumber % 14 == 10)
        {
            cout << "Multi Kill";
        }
        if (KillNumber % 14 == 11)
        {
            cout << "Ludicrouskill";
        }
        if (KillNumber % 14 == 12)
        {
            cout << "Ultra Kill";
        }
        if (KillNumber % 14 == 13)
        {
            cout << "Dominating";
        }
        if (KillNumber % 14 == 14)
        {
            cout << "Godlike";
        }
        sleep(1);
        cout << "\033[" << 10 << ";" << 17 << "H";
        cout << "                          ";
        cout << "\033[" << 20 << ";" << 1 << "H";
    }
};

class Vaccine_Details
{
public:
    int VaccineNumber = 0;
    int x;
    int y;
    bool is_recive;
};

class Vaccine : public Vaccine_Details
{
public:
    Vaccine()
    {
        setRandomCoordinates();
        is_recive = false;
    }
    void setRandomCoordinates()
    {
        // تنظیم seed یک بار در ابتدای برنامه
        static bool seedSet = false;
        if (!seedSet)
        {
            srand(static_cast<unsigned>(time(0)));
            seedSet = true;
        }

        // تولید مختصات تصادفی
        x = rand() % (15) + 2;
        y = rand() % (13) + 4;
    }

    void display()
    {
        if (!is_recive)
        {
            cout << "\033[" << y << ";" << x << "H"; // Set cursor position
            cout << "\e[0;33m";                      // ANSI escape code for red color
            cout << "V";
            cout << "\033[0m"; // Reset color to default
            cout << "\033[" << 20 << ";" << 1 << "H";
        }
    }
};

class ammoBox_Details
{
public:
    int AmmoBoxNumber = 0;
    int x;
    int y;
    bool isRecive;
};

class Ammo_Box : public ammoBox_Details
{
public:
    Ammo_Box()
    {
        setRandomCoordinates();
        isRecive = false;
    }
    void setRandomCoordinates()
    {
        // تنظیم seed یک بار در ابتدای برنامه
        static bool seedSet = false;
        if (!seedSet)
        {
            srand(static_cast<unsigned>(time(0) + 1));
            seedSet = true;
        }

        // تولید مختصات تصادفی
        x = rand() % (15) + 2;
        y = rand() % (13) + 4;
    }

    void display()
    {
        if (!isRecive)
        {
            cout << "\033[" << y << ";" << x << "H"; // Set cursor position
            cout << "\033[36m";                      // ANSI escape code for red color
            cout << "A";
            cout << "\033[0m"; // Reset color to default
            cout << "\033[" << 20 << ";" << 1 << "H";
        }
    }
};
class Player
{
public:
    int x;
    int y;

    Player(int initialX = 2, int initialY = 4) : x(initialX), y(initialY)
    {
    }

    void move(char direction)
    {
        int newX = x;
        int newY = y;

        if (direction == 's')
        {
            newY = y + 1;
        }
        else if (direction == 'w')
        {
            newY = y - 1;
        }
        else if (direction == 'a')
        {
            newX = x - 1;
        }
        else if (direction == 'd')
        {
            newX = x + 1;
        }

        // بررسی اینکه بازیکن در محدوده معتبر قرار دارد
        if (newX > 1 && newX < 17 && newY > 3 && newY < 19)
        {
            x = newX;
            y = newY;
            // Beep(523, 5);
        }
    }

    void vaccineCheck(Vaccine *vaccines, int level, Vaccine_Details &vaccine_Details, int &credit)
    {
        for (int i = 0; i < level; i++)
        {
            if (x == vaccines[i].x && y == vaccines[i].y && !vaccines[i].is_recive)
            {
                vaccine_Details.VaccineNumber++;
                vaccines[i].is_recive = true;
                cout << "\033[" << 10 << ";" << 25 << "H";
                cout << "Vaccine collected!";
                cout << "\033[" << 11 << ";" << 25 << "H";
                cout << level + 1 << " credit gained!";
                sleep(1);
                // پاک کردن پیام پس از تأخیر
                cout << "\033[" << 10 << ";" << 17 << "H";
                cout << "                          ";
                cout << "\033[" << 20 << ";" << 1 << "H";

                credit += level + 1;
                break;
            }
        }
    }

    void ammoBoxCheck(Ammo_Box *ammo_Boxes, int level, ammoBox_Details &ammoBox_Details, int &AmmoNumber)
    {
        for (int i = 0; i < level; i++)
        {
            if (x == ammo_Boxes[i].x && y == ammo_Boxes[i].y && !ammo_Boxes[i].isRecive)
            {
                ammo_Boxes[i].isRecive = true;
                AmmoNumber++;
                cout << "\033[" << 10 << ";" << 25 << "H";
                cout << "Ammo collected!";
                sleep(1);
                // پاک کردن پیام پس از تأخیر
                cout << "\033[" << 10 << ";" << 17 << "H";
                cout << "                          ";
                cout << "\033[" << 20 << ";" << 1 << "H";
                // gun.AmmoMagazine++;
                break;
            }
        }
    }

    void display()
    {
        // Set cursor position, change text color to green, and display 'P'
        cout << "\033[" << y << ";" << x << "H"; // Set cursor position
        cout << "\033[32m";                      // ANSI escape code for green color
        cout << "P";
        cout << "\033[0m"; // Reset color to default
        cout << "\033[" << 20 << ";" << 1 << "H";
    }
};

class Zombie
{
public:
    int x;
    int y;
    bool isActive;

    // سازنده با مقادیر اولیه
    Zombie()
    {
        setRandomCoordinates();
        isActive = true;
    }

    void setRandomCoordinates()
    {
        // تنظیم seed یک بار در ابتدای برنامه
        static bool seedSet = false;
        if (!seedSet)
        {
            srand(static_cast<unsigned>(time(0) + 3));
            seedSet = true;
        }

        // تولید مختصات تصادفی
        x = rand() % (15) + 2;
        y = rand() % (13) + 4;
    }

    void display()
    {
        if (isActive)
        {
            // استفاده از ANSI Escape برای تنظیم رنگ

            cout << "\033[" << y << ";" << x << "H"; // Set cursor position
            cout << "\033[31m";                      // ANSI escape code for red color
            cout << "Z";
            cout << "\033[0m"; // Reset color to default
            cout << "\033[" << 20 << ";" << 1 << "H";
        }
    }

    void move(Player &player, Zombie *otherZombies, int zombieCount, int index)
    {
        int original_x = x;
        int original_y = y;

        if (player.x > x)
        {
            x++;
        }
        else if (player.x < x)
        {
            x--;
        }

        if (player.y > y)
        {
            y++;
        }
        else if (player.y < y)
        {
            y--;
        }

        // بررسی تداخل با سایر زامبی‌ها
        for (int i = 0; i < zombieCount; i++)
        {
            if (i != index) // جلوگیری از بررسی زامبی خود
            {
                if (x == otherZombies[i].x && y == otherZombies[i].y)
                {
                    // در صورت تداخل، عدم تکون زامبی
                    x = original_x;
                    y = original_y;
                    break; // خروج از حلقه، زیرا تداخل با یک زامبی کافی است
                }
            }
        }

        // محدودیت‌های حرکت زامبی
        if (x < 2)
        {
            x = 2;
        }
        else if (x > 16)
        {
            x = 16;
        }

        if (y < 2)
        {
            y = 2;
        }
        else if (y > 18)
        {
            y = 18;
        }
    }

    void ZombiesCheck(Player &player, int level, int &health)
    {
        if (abs(x - player.x) <= 1 && abs(y - player.y) <= 1 && isActive)
        {
            health--;
            cout << "\033[" << 10 << ";" << 25 << "H";
            cout << "The Zombie is eating you!";
            cout << "\033[" << 11 << ";" << 25 << "H";
            cout << "You lost one of your healths!";
            sleep(1);
            // پاک کردن پیام پس از تأخیر
            cout << "\033[" << 10 << ";" << 17 << "H";
            cout << "                          ";
            cout << "\033[" << 20 << ";" << 1 << "H";
        }
    }
};
// meow
class Gun
{
public:
    int AmmoNumber;
    int AmmoMagazine;
    int MagazineSize;
    int range;
    Gun()
    {
        AmmoNumber = 3;
        AmmoMagazine = 0;
        MagazineSize = 3;
        range = 3;
    }
    void shoot(char direction, Zombie *zombies, Player &player, Kill &kill_, int Level, Round &round)
    {
        if (direction == 't' || direction == 'T')
        {
            if (AmmoNumber > 0)
            {
                AmmoNumber--;
                // fireSound();
                for (int i = 0; i <= Level; i++)
                {
                    if (zombies[i].isActive && zombies[i].x == player.x && 0 <= (player.y - zombies[i].y) && (player.y - zombies[i].y) <= range)
                    {
                        zombies[i].isActive = false;
                        kill_.KillNumber++;
                        kill_.count(round);
                        break;
                    }
                    else if (zombies[i].isActive && zombies[i].x == player.x)
                    {
                        cout << "\033[" << 10 << ";" << 25 << "H";
                        cout << "Zombie is not in range! come closer.";
                        sleep(1);
                        // پاک کردن پیام پس از تأخیر
                        cout << "\033[" << 10 << ";" << 17 << "H";
                        cout << "                          ";
                        cout << "\033[" << 20 << ";" << 1 << "H";
                        break;
                    }
                }
            }
            else
            {
                cout << "\033[" << 10 << ";" << 25 << "H";
                cout << "No charged ammo!";
                sleep(1);
                // پاک کردن پیام پس از تأخیر
                cout << "\033[" << 10 << ";" << 17 << "H";
                cout << "                          ";
                cout << "\033[" << 20 << ";" << 1 << "H";
            }
        }

        else if (direction == 'g' || direction == 'G')
        {
            if (AmmoNumber > 0)
            {
                AmmoNumber--;
                // fireSound();
                for (int i = 0; i <= Level; i++)
                {
                    if (zombies[i].isActive && zombies[i].x == player.x && 0 <= zombies[i].y - player.y && zombies[i].y - player.y <= range)
                    {
                        zombies[i].isActive = false;
                        kill_.KillNumber++;
                        kill_.count(round);
                        // cout << "Zombie hit! Zombie at (" << zombies[i].x << ", " << zombies[i].y << ") eliminated." << endl;
                        break;
                    }
                    else if (zombies[i].isActive && zombies[i].x == player.x)
                    {
                        cout << "\033[" << 10 << ";" << 25 << "H";
                        cout << "Zombie is not in range! come closer.";
                        sleep(1);
                        // پاک کردن پیام پس از تأخیر
                        cout << "\033[" << 10 << ";" << 17 << "H";
                        cout << "                          ";
                        cout << "\033[" << 20 << ";" << 1 << "H";
                        break;
                    }
                }
            }
            else
            {
                cout << "\033[" << 10 << ";" << 25 << "H";
                cout << "No charged ammo!";
                sleep(1);
                // پاک کردن پیام پس از تأخیر
                cout << "\033[" << 10 << ";" << 17 << "H";
                cout << "                          ";
                cout << "\033[" << 20 << ";" << 1 << "H";
            }
        }

        else if (direction == 'h' || direction == 'H')
        {
            if (AmmoNumber > 0)
            {
                AmmoNumber--;
                // fireSound();
                for (int i = 0; i <= Level; i++)
                {
                    if (zombies[i].isActive && zombies[i].y == player.y && 0 <= zombies[i].x - player.x && zombies[i].x - player.x <= range)
                    {
                        zombies[i].isActive = false;
                        kill_.KillNumber++;
                        kill_.count(round);
                        // cout << "Zombie hit! Zombie at (" << zombies[i].x << ", " << zombies[i].y << ") eliminated." << endl;
                        break;
                    }
                    else if (zombies[i].isActive && zombies[i].y == player.y)
                    {
                        cout << "\033[" << 10 << ";" << 25 << "H";
                        cout << "Zombie is not in range! come closer.";
                        sleep(1);
                        // پاک کردن پیام پس از تأخیر
                        cout << "\033[" << 10 << ";" << 17 << "H";
                        cout << "                          ";
                        cout << "\033[" << 20 << ";" << 1 << "H";
                        break;
                    }
                }
            }
            else
            {

                cout << "\033[" << 10 << ";" << 25 << "H";
                cout << "No charged ammo!";
                sleep(1);
                // پاک کردن پیام پس از تأخیر
                cout << "\033[" << 10 << ";" << 17 << "H";
                cout << "                          ";
                cout << "\033[" << 20 << ";" << 1 << "H";
            }
        }

        else if (direction == 'f' || direction == 'F')
        {
            if (AmmoNumber > 0)
            {
                AmmoNumber--;
                // fireSound();
                for (int i = 0; i <= Level; i++)
                {
                    if (zombies[i].isActive && zombies[i].y == player.y && 0 <= player.x - zombies[i].x && player.x - zombies[i].x <= range)
                    {
                        zombies[i].isActive = false;
                        kill_.KillNumber++;
                        kill_.count(round);
                        // cout << "Zombie hit! Zombie at (" << zombies[i].x << ", " << zombies[i].y << ") eliminated." << endl;
                        break;
                    }
                    else if (zombies[i].isActive && zombies[i].y == player.y)
                    {
                        cout << "\033[" << 10 << ";" << 25 << "H";
                        cout << "Zombie is not in range! come closer.";
                        sleep(1);
                        // پاک کردن پیام پس از تأخیر
                        cout << "\033[" << 10 << ";" << 17 << "H";
                        cout << "                          ";
                        cout << "\033[" << 20 << ";" << 1 << "H";
                        break;
                    }
                }
            }
            else
            {
                cout << "\033[" << 10 << ";" << 25 << "H";
                cout << "No charged ammo!";
                sleep(1);
                // پاک کردن پیام پس از تأخیر
                cout << "\033[" << 10 << ";" << 17 << "H";
                cout << "                          ";
                cout << "\033[" << 20 << ";" << 1 << "H";
            }
        }
    }
    void reload(char direction)
    {
        int freeMag = MagazineSize - AmmoNumber;

        if (direction == 'r' || direction == 'R')
        {
            if (AmmoMagazine == 0)
            {
                cout << "\033[" << 10 << ";" << 25 << "H";
                cout << "No Ammo!";
                sleep(1);
                // پاک کردن پیام پس از تأخیر
                cout << "\033[" << 10 << ";" << 17 << "H";
                cout << "                          ";
                cout << "\033[" << 20 << ";" << 1 << "H";
            }

            else if (AmmoNumber < MagazineSize)
            {
                for (; AmmoNumber != MagazineSize && AmmoMagazine > 0;)
                {
                    AmmoMagazine--;
                    AmmoNumber++;
                }
                cout << "\033[" << 10 << ";" << 25 << "H";
                cout << "Reloading!";
                sleep(1);

                cout << "\033[" << 10 << ";" << 17 << "H";
                cout << "                          ";
                cout << "\033[" << 20 << ";" << 1 << "H";
            }
            else if (AmmoNumber == MagazineSize)
            {

                cout << "\033[" << 10 << ";" << 25 << "H";
                cout << "The gun is already Charged";
                sleep(1);

                cout << "\033[" << 10 << ";" << 17 << "H";
                cout << "                          ";
                cout << "\033[" << 20 << ";" << 1 << "H";
            }
        }
    }
};

class Door
{
public:
    int x;
    int y;
    Door(int initialX = 16, int initialY = 18) : x(initialX), y(initialY)
    {
    }

    void display()
    {
        cout << "\033[" << y << ";" << x << "H"; // Set cursor position
        cout << "\033[36m";                      // ANSI escape code for red color
        cout << "D";
        cout << "\033[0m"; // Reset color to default
        cout << "\033[" << 20 << ";" << 1 << "H";
    }
};

class Level
{
public:
    int levelNumber;
    Level(int number = 1) : levelNumber(number)
    {
    }
};

class Credit
{
public:
    int CreditNumber;
    Credit(int number = 0) : CreditNumber(number)
    {
    }
};

class Health
{
public:
    int HealthNumber;
    Health(int number = 3) : HealthNumber(number)
    {
    }
    void HealthDrawer()
    {
        cout << "{";
        for (int i = 0; i < HealthNumber; i++)
        {
            cout << " |";
        }
        cout << " }";
    }
};

class Upgrade
{
public:
    void Upgrade_magazin(int &MagazineSize, int level, int &credit)
    {
        if (credit >= (level)*MagazineSize && MagazineSize != 7)
        {
            credit -= (level)*MagazineSize;
            MagazineSize++;
            Clear_scr();
            cout << "\033[" << 10 << ";" << 45 << "H";
            cout << "Upgrade done successfully.Your magazine capacity is now  ." << MagazineSize;
        }
        else if (MagazineSize == 7)
        {
            cout << "\033[" << 10 << ";" << 45 << "H";
            cout << "The selected item is maximum";
        }
        else
        {
            Clear_scr();
            cout << "\033[" << 10 << ";" << 45 << "H";
            cout << "Unfortunately, your credit is not enough to get this item. Please gain " << (level)*MagazineSize - credit << " more credit by playing ";
        }
    }

    void Upgrade_range(int &range, int level, int &credit)
    {
        if (credit >= (level) + range && range != 10)
        {
            credit -= (level) + range;
            range++;
            Clear_scr();
            cout << "\033[" << 10 << ";" << 45 << "H";
            cout << "Upgrade done successfully.Your shotgun range is now " << range;
        }
        else if (range == 10)
        {
            cout << "\033[" << 10 << ";" << 45 << "H";
            cout << "The selected item is maximum";
        }
        else
        {
            Clear_scr();
            cout << "\033[" << 10 << ";" << 45 << "H";
            cout << "Unfortunately, your credit is not enough to get this item. Please gain " << (level) + range - credit << " more credit by playing ";
        }
    }
    void Upgrade_health(int &health, int level, int &credit)
    {
        if (credit >= (health) * (level + 1) && health != 5)
        {
            credit -= (health) * (level + 1);
            health++;
            Clear_scr();
            cout << "\033[" << 10 << ";" << 45 << "H";
            cout << "Additional health received successfully. Your health is now " << health;
        }
        else if (health == 5)
        {
            cout << "\033[" << 10 << ";" << 45 << "H";
            cout << "The selected item is maximum";
        }
        else
        {
            Clear_scr();
            cout << "\033[" << 10 << ";" << 45 << "H";
            cout << "Unfortunately, your credit is not enough to get this item. Please gain " << (health) * (level + 1) - credit << " more credit by playing ";
        }
    }

    void display(int MagazineSize, int ammonumber, int level, int range, int health, int credit)
    {
        Clear_scr();
        cout << "\033[" << 6 << ";" << 70 << "H";
        cout << "Your credit: " << credit;
        cout << "\033[" << 8 << ";" << 45 << "H";
        cout << "0 – Return to game.";
        cout << "\033[" << 10 << ";" << 45 << "H";
        cout << "1 – Upgrade capacity of magazine :";
        cout << " 1 bullet ";
        cout << " (maximum is " << 7 << " bullets, now is " << MagazineSize << ") ";
        cout << "Credit required: " << (level)*MagazineSize;
        cout << "\033[" << 12 << ";" << 45 << "H";
        cout << "2 – Upgrade range of shotgun : 1 times the size of the person himself ";
        cout << "(maximum is 10 times, now is " << range << ") ";
        cout << "Credit required: " << (level) + range;
        cout << "\033[" << 14 << ";" << 45 << "H";
        cout << "3 – get an additional health (maximum is 5 healths, now is " << health;
        cout << " Credit required: " << (health) * (level + 1);
    }
};

class Timer
{
private:
    std::chrono::high_resolution_clock::time_point start_time;

public:
    Timer() : start_time(std::chrono::high_resolution_clock::now()) {}

    double elapsed() const
    {
        return std::chrono::duration<double>(std::chrono::high_resolution_clock::now() - start_time).count();
    }

    void setSeconds(double seconds)
    {
        start_time = std::chrono::time_point_cast<std::chrono::high_resolution_clock::duration>(
            std::chrono::high_resolution_clock::now() - std::chrono::duration<double>(seconds));
    }
};

class Game_board
{
public:
    Level level;
    Vaccine_Details vaccine_Details;
    Vaccine Vaccines[20];
    Credit credit;
    Round round;
    Health health;
    Ammo_Box ammo_Details;
    Ammo_Box ammo_Boxes[20];
    Kill kill_;
    Player player;
    Zombie zombies[20];
    Door door;
    Gun gun;
    Upgrade upgrade;
    // ShowMenu showmenu;
    void Details()
    {
        cout << "Level: " << level.levelNumber << " ";
        cout << "Vaccine: " << vaccine_Details.VaccineNumber << " ";
        cout << " Credit: " << credit.CreditNumber << " ";
        cout << "Round: " << round.RoundNumber << endl;
        cout << "Health: ";
        health.HealthDrawer();
        cout << " ";
        cout << "Ammo: " << gun.AmmoNumber << "/" << gun.AmmoMagazine << " ";
        cout << "Kill: " << kill_.KillNumber;
    }
    void Reset_position()
    {
        player.x = 2;
        player.y = 4;
        for (int i = 0; i < level.levelNumber; i++)
        {
            zombies[i].setRandomCoordinates();
            Vaccines[i].setRandomCoordinates();
            ammo_Boxes[i].setRandomCoordinates();
            for (int j = 0; j < i; j++)
            {
                while (is_same_position(zombies[i], zombies[j], i, j))
                {
                    zombies[i].setRandomCoordinates();
                }
            }
        }
    }

    Timer timer; // تعریف یک نمونه از کلاس Timer برای استفاده در سرتاسر برنامه

    void print_Game_board()
    {
        Clear_scr();
        Details();
        cout << endl;
        int width = 17;
        int height = 17;
        for (int i = 0; i < width; i++)
        {
            cout << "-";
        }
        cout << endl;
        for (int i = 0; i < height - 2; i++)
        {
            cout << "|";
            for (int i = 0; i < height - 2; i++)
            {
                cout << " ";
            }
            cout << "|";
            cout << endl;
        }
        for (int i = 0; i < width; i++)
        {
            cout << "-";
        }

        player.display();
        door.display();

        for (int i = 0; i < level.levelNumber; i++)
        {
            // zombies[i].setRandomCoordinates();
            for (int j = 0; j < level.levelNumber; j++)
            {
                if (!is_same_position(zombies[i], zombies[j], i, j) && (zombies[i].x != 2 || zombies[i].y != 4) && (zombies[i].x != 16 || zombies[i].y != 18))
                {
                    zombies[i].display();
                }
                else
                {
                    zombies[j].setRandomCoordinates();
                }
            }
        }

        for (int i = 0; i < level.levelNumber; i++)
        {
            for (int j = 0; j < level.levelNumber; j++)
            {
                if (!is_same_position_z_v(zombies[i], Vaccines[j]) && !is_same_position_V(Vaccines[i], Vaccines[j], i, j) && (Vaccines[i].x != 2 || Vaccines[i].y != 4) && (Vaccines[i].x != 16 || Vaccines[i].y != 18))
                {
                    Vaccines[i].display();
                }
                else
                {
                    Vaccines[j].setRandomCoordinates();
                }
            }
        }
        for (int i = 0; i < level.levelNumber; i++)
        {
            for (int j = 0; j < level.levelNumber; j++)
            {
                if (!is_same_position_z_a(zombies[i], ammo_Boxes[j]) && !is_same_position_v_a(Vaccines[i], ammo_Boxes[j]) && !is_same_position_A(ammo_Boxes[i], ammo_Boxes[j], i, j) && (ammo_Boxes[i].x != 2 || ammo_Boxes[i].y != 4) && (ammo_Boxes[i].x != 16 || ammo_Boxes[i].y != 18))
                {
                    ammo_Boxes[i].display();
                }
                else
                {
                    ammo_Boxes[j].setRandomCoordinates();
                }
            }
        }

        if (static_cast<int>(timer.elapsed()) < 60)
        {
            cout << "\033[" << 8 << ";" << 55 << "H";
            cout << "Time you have been playing : " << static_cast<int>(timer.elapsed()) << " second" << endl;
            cout << "\033[" << 20 << ";" << 1 << "H";
        }
        else
        {
            int elapsed_seconds = static_cast<int>(timer.elapsed());
            int min = elapsed_seconds / 60;
            int sec = elapsed_seconds % 60;
            cout << "\033[" << 8 << ";" << 55 << "H";
            cout << "Time you have been playing : " << min << " minute and " << sec << " second" << endl;
            cout << "\033[" << 20 << ";" << 1 << "H";
        }
    }

    bool is_same_position(Zombie &zombie_1, Zombie &zombie_2, int index_1, int index_2)
    {
        if (zombie_1.x == zombie_2.x && zombie_1.y == zombie_2.y && index_1 != index_2)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool is_same_position_z_v(Zombie &zombie, Vaccine &vaccine)
    {
        if (zombie.x == vaccine.x && zombie.y == vaccine.y)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool is_same_position_z_a(Zombie &zombie, Ammo_Box &ammo_Boxes)
    {
        if (zombie.x == ammo_Boxes.x && zombie.y == ammo_Boxes.y)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool is_same_position_v_a(Vaccine &vaccine, Ammo_Box &ammo_Boxes)
    {
        if (ammo_Boxes.x == vaccine.x && ammo_Boxes.y == vaccine.y)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool is_same_position_V(Vaccine &vaccine_1, Vaccine &vaccine_2, int index_1, int index_2)
    {
        if (vaccine_1.x == vaccine_2.x && vaccine_1.y == vaccine_2.y && index_1 != index_2)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    bool is_same_position_A(Ammo_Box &ammo_box_1, Ammo_Box &ammo_box_2, int index_1, int index_2)
    {
        if (ammo_box_1.x == ammo_box_2.x && ammo_box_1.y == ammo_box_2.y && index_1 != index_2)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

class Game_Setting
{
public:
    bool is_mute = true;
    int index = 0;

    void Setting(Game_board &game_board)
    {
        Clear_scr();
        cout << "final level is: 20" << endl;
        if (is_mute)
        {
            cout << "Sound is not mute!" << endl;
            cout << "Do you want to mute the sound?" << endl;
        }
        else if (!is_mute)
        {
            cout << "Sound is mute!" << endl;
            cout << "Do you want to unmute the sound?" << endl;
        }

        char step = getUserInput_setting();

        if (step == 'y')
        {
            if (is_mute == true)
            {
                is_mute = false;
            }
            else if (is_mute == false)
            {
                is_mute = true;
            }

            Setting(game_board);
        }
        else if (step == 'n')
        {
            if (index == 0)
            {
                Header(game_board);
            }
            else
            {
                game_board.print_Game_board();
            }
        }
    }

    char getUserInput_setting()
    {
        char sound;
        sound = _getch();

        return sound;
    }
};

void Game_credit(Game_board &game_board)
{
    Clear_scr();
    cout << "created by :" << endl;
    cout << "Soroush Akhavan , Amirmohammad Amrayi";
    sleep(5);
    Clear_scr();
    Header(game_board);
}

void load(Game_board &game_board)
{
    ifstream saved("save_file.txt", ios::in);

    if (saved.is_open())
    {
        // خواندن اطلاعات بازی از فایل
        saved >> game_board.level.levelNumber;
        saved >> game_board.vaccine_Details.VaccineNumber;
        saved >> game_board.credit.CreditNumber;
        saved >> game_board.round.RoundNumber;
        saved >> game_board.health.HealthNumber;
        saved >> game_board.gun.AmmoNumber;
        saved.ignore(); // تخطی از کاراکتر جدا کننده رشته
        saved >> game_board.gun.AmmoMagazine;
        saved >> game_board.kill_.KillNumber;
        saved >> game_board.gun.range;

        // خواندن موقعیت بازیکن
        saved >> game_board.player.x >> game_board.player.y;

        // خواندن موقعیت زامبی‌ها
        for (int i = 0; i < game_board.level.levelNumber; ++i)
        {
            saved >> game_board.zombies[i].isActive; // خواندن وضعیت فعال بودن
            if (game_board.zombies[i].isActive)
            {
                saved >> game_board.zombies[i].x >> game_board.zombies[i].y;
            }
            else
            {
                saved.ignore();
            }
        }

        for (int i = 0; i < game_board.level.levelNumber; ++i)
        {
            saved >> game_board.ammo_Boxes[i].isRecive; // خواندن وضعیت فعال بودن
            if (!game_board.ammo_Boxes[i].isRecive)
            {
                saved >> game_board.ammo_Boxes[i].x >> game_board.ammo_Boxes[i].y;
            }
            else
            {
                saved.ignore();
            }
        }

        for (int i = 0; i < game_board.level.levelNumber; ++i)
        {
            saved >> game_board.Vaccines[i].is_recive; // خواندن وضعیت فعال بودن
            if (!game_board.Vaccines[i].is_recive)
            {
                saved >> game_board.Vaccines[i].x >> game_board.Vaccines[i].y;
            }
            else
            {
                saved.ignore();
            }
        }

        // خواندن زمان از فایل
        // int elapsed_seconds;
        // saved >> elapsed_seconds;
        // game_board.timer.reset();                                          // تنظیم مجدد تایمر
        // game_board.timer.setSeconds(static_cast<double>(elapsed_seconds)); // تنظیم زمان خوانده شده به تایمر

        saved.close();
        if (count_m == 0)
        {
            cout << "\033[" << 10 << ";" << 25 << "H";
            cout << "Game loading...";
            sleep(3);
            // پاک کردن پیام پس از تأخیر
        }
    }
}

class MainMenu
{
public:
    void printHeader()
    {
        string Reset = "\033[0m";
        string Blood_color = "\033[38;2;136;8;8m";
        string Red = "\033[31m";
        cout << Red << "                          .__      .___     ________   _______    ________   _______   \n";
        cout << "  ____     ____   ___  __ |__|   __| _/     \\_____  \\  \\   _  \\   \\_____  \\  \\   _  \\  \n";
        cout << "_/ ___\\   /  _ \\  \\  \\/ / |  |  / __ |       /  ____/  /  /_\\  \\    _(__  <  /  /_\\  \\ \n";
        cout << "\\  \\___  (  <_> )  \\   /  |  | / /_/ |      /       \\  \\  \\_/   \\  /       \\ \\  \\_/   \\\n";
        cout << " \\___  >  \\____/    \\_/   |__| \\____ |      \\_______ \\  \\_____  / /______  /  \\_____  / \n";
        cout << "     \\/                             \\/              \\/        \\/         \\/         \\/  \n"
             << Blood_color;
        cout << endl;
        cout << "█     █░▓█████  ██▓    ▄████▄  ▒█████   ███▄ ▄███▓▓█████    ▄▄▄█████▓ ▒█████     ▄▄▄█████▓ ██░ ██ ▓█████      ▄████  ▄▄▄      ███▄ ▄███▓▓█████     ▐██▌\n";
        cout << "▓█░ █ ░█░▓█   ▀ ▓██▒   ▒██▀ ▀█ ▒██▒  ██▒▓██▒▀█▀ ██▒▓█   ▀    ▓  ██▒ ▓▒▒██▒  ██▒   ▓  ██▒ ▓▒▓██░ ██▒▓█   ▀     ██▒ ▀█▒▒████▄   ▓██▒▀█▀ ██▒▓█   ▀     ▐██▌\n";
        cout << "▒█░ █ ░█ ▒███   ▒██░   ▒▓█    ▄▒██░  ██▒▓██    ▓██░▒███      ▒ ▓██░ ▒░▒██░  ██▒   ▒ ▓██░ ▒░▒██▀▀██░▒███      ▒██░▄▄▄░▒██  ▀█▄ ▓██    ▓██░▒███       ▐██▌\n";
        cout << "░█░ █ ░█ ▒▓█  ▄ ▒██░   ▒▓▓▄ ▄██▒██   ██░▒██    ▒██ ▒▓█  ▄    ░ ▓██▓ ░ ▒██   ██░   ░ ▓██▓ ░ ░▓█ ░██ ▒▓█  ▄    ░▓█  ██▓░██▄▄▄▄██▒██    ▒██ ▒▓█  ▄     ▓██▒\n";
        cout << "░░██▒██▓ ░▒████▒░██████▒ ▓███▀ ░ ████▓▒░▒██▒   ░██▒░▒████▒     ▒██▒ ░ ░ ████▓▒░     ▒██▒ ░ ░▓█▒░██▓░▒████▒   ░▒▓███▀▒ ▓█   ▓██▒██▒   ░██▒░▒████▒    ▒▄▄ \n";
        cout << "░ ▓░▒ ▒  ░░ ▒░ ░░ ▒░▓  ░ ░▒ ▒  ░ ▒░▒░▒░ ░ ▒░   ░  ░░░ ▒░ ░     ▒ ░░   ░ ▒░▒░▒░      ▒ ░░    ▒ ░░▒░▒░░ ▒░ ░    ░▒   ▒  ▒▒   ▓▒█░ ▒░   ░  ░░░ ▒░ ░    ░▀▀▒\n";
        cout << "  ▒ ░ ░   ░ ░  ░░ ░ ▒  ░ ░  ▒    ░ ▒ ▒░ ░  ░      ░ ░ ░  ░       ░      ░ ▒ ▒░        ░     ▒ ░▒░ ░ ░ ░  ░     ░   ░   ▒   ▒▒ ░  ░      ░ ░ ░  ░    ░  ░\n";
        cout << "  ░   ░     ░     ░ ░  ░       ░ ░ ░ ▒  ░      ░      ░        ░      ░ ░ ░ ▒       ░       ░  ░░ ░   ░      ░ ░   ░   ░   ▒  ░      ░      ░          ░\n";
        cout << "    ░       ░  ░    ░  ░ ░         ░ ░         ░      ░  ░                ░ ░               ░  ░  ░   ░  ░         ░       ░  ░      ░      ░  ░    ░   \n";

        cout << "                       ░                                                                                                                                                                  \n"
             << Reset;
        ;
    }
    void Options(Game_board &game_board)
    {
        // Game_board gameboard;
        Game_Setting game_Setting;

        cout << "𝟙-𝕟𝕖𝕨 𝕘𝕒𝕞𝕖" << endl;
        cout << "𝟚-𝕣𝕖𝕤𝕦𝕞𝕖" << endl;
        cout << "𝟛-𝕊𝕖𝕥𝕥𝕚𝕟𝕘𝕤" << endl;
        cout << "𝟜-ℂ𝕣𝕖𝕕𝕚𝕥𝕤" << endl;
        cout << "𝟝-ℍ𝕖𝕝𝕡" << endl;
        cout << "𝟞-𝔼𝕩𝕚𝕥" << endl;
        int userInput = getUserInput();
        if (userInput != 1 && userInput != 2 && userInput != 3 && userInput != 4 && userInput != 5 && userInput != 6)
        {
            while (userInput != 1 && userInput != 2 && userInput != 3 && userInput != 4 && userInput != 5 && userInput != 6)
            {
                cout << "\033[" << 26 << ";" << 45 << "H";
                cout << "Please just enter the numbers in the menu: ";
                sleep(1);
                cout << "\033[" << 26 << ";" << 45 << "H";
                cout << "                                            ";
                cout << "\033[" << 25 << ";" << 1 << "H";
                userInput = getUserInput();
            }
        }
        if (userInput == 1)
        {
            if (count_m == 0)
            {
                game_board.print_Game_board();
                game_Setting.index = 1;
                // startSound();
            }
            else
            {
                load(game_board);
                game_board.print_Game_board();
            }
        }
        else if (userInput == 2)
        {
            // startSound();
            load(game_board);
            game_board.print_Game_board();
            game_Setting.index = 1;
        }
        else if (userInput == 3)
        {
            // menuSound();
            game_Setting.Setting(game_board);
        }
        else if (userInput == 4)
        {
            // menuSound();
            Game_credit(game_board);
        }
        else if (userInput == 6)
        {
            cout << "Are you sure you want to exit the game? (y/n) ";
            char userInput_u;
            userInput_u = getch();
            if (userInput_u != 'n' && userInput_u != 'y' && userInput_u != 'Y' && userInput_u != 'N')
            {
                while (userInput_u != 'n' && userInput_u != 'y' && userInput_u != 'Y' && userInput_u != 'N')
                {
                    cout << "\033[" << 26 << ";" << 45 << "H";
                    cout << "Please just enter y or n: ";
                    sleep(1);
                    cout << "\033[" << 26 << ";" << 45 << "H";
                    cout << "                                            ";
                    cout << "\033[" << 25 << ";" << 1 << "H";
                    userInput_u = getch();
                }
            }
            if (userInput_u == 'y' || userInput_u == 'Y')
            {
                exit(0);
            }
            else
            {
                Clear_scr();
                printHeader();
                Options(game_board);
                cout << "\033[" << 20 << ";" << 1 << "H";
            }
        }
    }

    int getUserInput()
    {
        int userInput = 0;
        // Get the user input without waiting for Enter
        userInput = getch() - '0';
        return userInput;
    }
};

bool lose(Game_board &game_board)
{
    if (game_board.health.HealthNumber == 0)
    {

        return true;
    }

    return false;
}

bool win(Game_board game_board)
{
    int count_v = 0;
    if (game_board.player.x == game_board.door.x && game_board.player.y == game_board.door.y)
    {
        for (int i = 0; i < (game_board.level.levelNumber); i++)
        {
            if (game_board.Vaccines[i].is_recive)
            {
                count_v++;
                if (count_v == game_board.level.levelNumber)
                {
                    return true;
                }
            }
        }

        cout << "\033[" << 10 << ";" << 25 << "H";
        cout << "First get all the vaccine.";
        sleep(1);
        // پاک کردن پیام پس از تأخیر
        cout << "\033[" << 10 << ";" << 17 << "H";
        cout << "                          ";
        cout << "\033[" << 20 << ";" << 1 << "H";
    }
    return false;
}

char getUserInput()
{
    char input = _getch();
    return input;
}

void Header(Game_board &game_board) // نمایش منوی اصلی بازی
{
    MainMenu main;
    Clear_scr();
    main.printHeader();
    main.Options(game_board);
}

void printMenu()
{
    Clear_scr();
    cout << "0-𝕣𝕖𝕥𝕦𝕣𝕟 𝕥𝕖 𝕘𝕒𝕞𝕖" << endl;
    cout << "𝟙-𝕟𝕖𝕨 𝕘𝕒𝕞𝕖" << endl;
    cout << "𝟚-𝕊𝕖𝕥𝕥𝕚𝕟𝕘𝕤" << endl;
    cout << "𝟛-𝔼𝕩𝕚𝕥" << endl;
}

void resume_(Game_board &game_board)
{
    game_board.print_Game_board();
}
void newGame()
{
}
void inGameSetting(Game_Setting &game_setting, Game_board &game_board)
{
    game_setting.Setting(game_board);
}
void exit(Game_board &game_board)
{
    Header(game_board);
}

void save(Game_board &game_board)
{
    ofstream save("save_file.txt", ios::out);

    // ذخیره اطلاعات بازی در فایل
    save << game_board.level.levelNumber << endl;                                    // level :
    save << game_board.vaccine_Details.VaccineNumber << endl;                        // VaccineNumber :
    save << game_board.credit.CreditNumber << endl;                                  // CreditNumber :
    save << game_board.round.RoundNumber << endl;                                    // RoundNumber :
    save << game_board.health.HealthNumber << endl;                                  // HealthNumber :
    save << game_board.gun.AmmoNumber << "/" << game_board.gun.AmmoMagazine << endl; // AmmoNumber & AmmoMagazine :
    save << game_board.kill_.KillNumber << endl;                                     // KillNumber :
    save << game_board.gun.range << endl;                                            // range :
    // ذخیره موقعیت بازیکن
    save << game_board.player.x << " " << game_board.player.y << endl;

    // ذخیره موقعیت زامبی‌ها
    for (int i = 0; i < game_board.level.levelNumber; ++i)
    {
        save << game_board.zombies[i].isActive << endl;
        if (game_board.zombies[i].isActive)
        {
            save << game_board.zombies[i].x << " " << game_board.zombies[i].y << endl;
        }
    }

    for (int i = 0; i < game_board.level.levelNumber; ++i)
    {
        save << game_board.ammo_Boxes[i].isRecive << endl;
        if (!game_board.ammo_Boxes[i].isRecive)
        {
            save << game_board.ammo_Boxes[i].x << " " << game_board.ammo_Boxes[i].y << endl;
        }
    }

    for (int i = 0; i < game_board.level.levelNumber; ++i)
    {
        save << game_board.Vaccines[i].is_recive << endl;
        if (!game_board.Vaccines[i].is_recive)
        {
            save << game_board.Vaccines[i].x << " " << game_board.Vaccines[i].y << endl;
        }
    }

    // save << static_cast<int>(game_board.timer.elapsed()) << endl;

    // بستن فایل
    save.close();
    cout << "\033[" << 10 << ";" << 25 << "H";
    if (count_m == 0)
    {
        cout << "Game saving...";
        sleep(3);
        // پاک کردن پیام پس از تأخیر
        cout << "\033[" << 10 << ";" << 17 << "H";
        cout << "                          ";
        cout << "\033[" << 20 << ";" << 1 << "H";
    }
}

int main()
{
    int count = 0;

    Game_board game_board;
    Game_Setting game_setting;
    Header(game_board);
    char userInput;
    while (!(lose(game_board)))
    {
        userInput = getUserInput(); // دریافت جهت حرکت
        // save game;
        if (userInput == '/')
        {
            save(game_board);
        }
        if (userInput == 'w' || userInput == 'a' || userInput == 's' || userInput == 'd')
        {
            game_board.player.move(userInput); // حرکت بازیکن بر اساس جهت حرکت
            game_board.player.vaccineCheck(game_board.Vaccines, game_board.level.levelNumber, game_board.vaccine_Details, game_board.credit.CreditNumber);
            game_board.player.ammoBoxCheck(game_board.ammo_Boxes, game_board.level.levelNumber, game_board.ammo_Details, game_board.gun.AmmoMagazine);
            for (int i = 0; i < game_board.level.levelNumber; i++)
            {
                game_board.zombies[i].ZombiesCheck(game_board.player, game_board.level.levelNumber, game_board.health.HealthNumber);
            }
        }
        // userInput_shoot = getUserInput_move_shoot(); // دریافت جهت تیر
        // game_board.gun.shoot(userInput_shoot, game_board.zombies, game_board.player);
        // if (userInput == 'T' || userInput == 't')
        // {
        //     game_board.gun.shoot(userInput, game_board.zombies, game_board.player, game_board.kill.KillNumber);
        // }
        if (userInput == 't' || userInput == 'g' || userInput == 'f' || userInput == 'h' || userInput == 'G' || userInput == 'F' || userInput == 'T' || userInput == 'H')
        {
            game_board.gun.shoot(userInput, game_board.zombies, game_board.player, game_board.kill_, game_board.level.levelNumber, game_board.round);
        }
        if (userInput == 'r' || userInput == 'R')
        {
            game_board.gun.reload(userInput);
        }
        if (userInput == 'e' || userInput == 'E')
        {
            cout << "Are you sure you want to exit the game? (y/n) ";
            char userInput_u;
            userInput_u = getUserInput();
            if (userInput_u == 'y')
            {
                return 0;
            }
            else
            {
            }
        }

        if (count % 2 == 0)
        {
            for (int i = 0; i < 20; i++)
            {
                game_board.zombies[i].move(game_board.player, game_board.zombies, game_board.level.levelNumber, i); // حرکت زامبی‌ها به سمت بازیکن
            }
        }
        game_board.print_Game_board();
        count++;

        if (userInput == 'u' || userInput == 'U')
        {
            game_board.upgrade.display(game_board.gun.MagazineSize, game_board.gun.AmmoNumber, game_board.level.levelNumber, game_board.gun.range, game_board.health.HealthNumber, game_board.credit.CreditNumber);
            char userInput_u = getUserInput();
            if (userInput_u != '0' && userInput_u != '1' && userInput_u != '2' && userInput_u != '3')
            {
                while (userInput_u != '0' && userInput_u != '1' && userInput_u != '2' && userInput_u != '3')
                {
                    cout << "\033[" << 16 << ";" << 45 << "H";
                    cout << "Please just enter the numbers in the menu: ";
                    userInput_u = getUserInput();
                }
            }
            if (userInput_u == '0')
            {
                Clear_scr();
                game_board.print_Game_board();
            }

            if (userInput_u == '1')
            {
                game_board.upgrade.Upgrade_magazin(game_board.gun.MagazineSize, game_board.level.levelNumber, game_board.credit.CreditNumber);
            }

            else if (userInput_u == '2')
            {
                game_board.upgrade.Upgrade_range(game_board.gun.range, game_board.level.levelNumber, game_board.credit.CreditNumber);
            }

            else if (userInput_u == '3')
            {
                game_board.upgrade.Upgrade_health(game_board.health.HealthNumber, game_board.level.levelNumber, game_board.credit.CreditNumber);
            }
        }
        if (userInput == 'm' || userInput == 'M')
        {
            count_m++;
            printMenu();
            char userInput_m = getUserInput();

            if(userInput_m == '0')
            {
                resume_(game_board);
            }
            else if(userInput_m == '1')
            {
                newGame();
            }
            else if (userInput_m == '2')
            {
                inGameSetting(game_setting, game_board);
            }
            else if(userInput_m == '3')
            {
                exit(game_board);
            }

        }

        if (win(game_board))
        {
            for (int i = 0; i < game_board.level.levelNumber; i++)
            {
                game_board.zombies[i].isActive = true;
                game_board.Vaccines[i].is_recive = false;
                game_board.ammo_Boxes[i].isRecive = false;
            }
            if (game_board.level.levelNumber == 20)
            {
                Clear_scr();
                cout << "Congratulations! You have successfully collected all the vaccines!" << endl;
                cout << "Now it is time to return to the Earth" << endl;
                cout << "Good Bye!" << endl;
                sleep(5);
                Header(game_board);
            }
            else
            {
                cout << "\033[" << 10 << ";" << 25 << "H";
                cout << "You Won! You have reached level " << game_board.level.levelNumber + 1;
                sleep(1);
                // پاک کردن پیام پس از تأخیر
                cout << "\033[" << 10 << ";" << 17 << "H";
                cout << "                          ";
                cout << "\033[" << 20 << ";" << 1 << "H";
            }

            game_board.level.levelNumber++;
            Clear_scr();
            game_board.Reset_position();
            game_board.print_Game_board();
            // winSound();
        }
    }
    if (lose(game_board))
    {
        cout << " You Died!" << endl;
        cout << " You Lose! Would you like to try again?(y/n)";
        game_setting.index = 0;
        sleep(2);
        char command = getUserInput();
        if (command != 'y' && command != 'Y' && command != 'n' && command != 'N')
        {
            while (command != 'y' && command != 'Y' && command != 'n' && command != 'N')
            {
                cout << "\033[" << 21 << ";" << 46 << "H";
                cout << "pleas just enter y or n .";
                sleep(1);
                // پاک کردن پیام پس از تأخیر
                cout << "\033[" << 21 << ";" << 46 << "H";
                cout << "                                   ";
                cout << "\033[" << 22 << ";" << 1 << "H";
                command = getch();
            }
        }
        if (command == 'y' || command == 'Y')
        {
            for (int i = 5; i > 0; i--)
            {
                Clear_scr();
                cout << "\033[" << 21 << ";" << 46 << "H";
                cout << "The game will restart in " << i << " seconds";
                sleep(1);
            }
            count_m = 0;
            main();
        }

        else
        {
            Clear_scr();
            return 0;
        }
    }
    // loseSound();
    return 0;
}
