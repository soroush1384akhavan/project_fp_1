#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#if defined _WIN32
#include <conio.h>
#elif defined(__LINUX__) || defined(__gnu_linux__) || defined(__linux__)
#include <unistd.h>
#include <termios.h>
#endif

using namespace std;

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

class Level
{
public:
    int levelNumber;
    Level(int number = 0) : levelNumber(number)
    {
    }
};

class Vaccine
{
public:
    int VaccineNumber;
    Vaccine(int number = 0) : VaccineNumber(number)
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

class Round
{
public:
    int RoundNumber;
    Round(int number = 0) : RoundNumber(number)
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

class Ammo
{
public:
    int AmmoNumber;
    int AmmoMagazine;
    Ammo(int numberAmmo = 3, int numberMagazine = 0) : AmmoNumber(numberAmmo), AmmoMagazine(numberMagazine)
    {
    }
};

class Kill
{
public:
    int KillNumber;
    Kill(int number = 0) : KillNumber(number)
    {
    }
};

class Game_board
{
public:
    Level level;
    Vaccine vaccine;
    Credit credit;
    Round round;
    Health health;
    Ammo ammo;
    Kill kill;
    Player player;
    void Details()
    {
        cout << "Level: " << level.levelNumber << " ";
        cout << "Vaccine: " << vaccine.VaccineNumber << " ";
        cout << " Credit: " << credit.CreditNumber << " ";
        cout << "Round: " << round.RoundNumber << endl;
        cout << "Health: ";
        health.HealthDrawer();
        cout << " ";
        cout << "Ammo: " << ammo.AmmoNumber << "/" << ammo.AmmoMagazine << " ";
        cout << "Kill: " << kill.KillNumber;
    }
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
        // Use the member variable player instead of creating a local Player object
        player.display();
    }

    // char getUserInput()
    // {
    //     char userInput;
    //     // Get the user input without waiting for Enter
    //     userInput = getch();
    //     return userInput;
    // }
};

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
    void Options()
    {
        Game_board gameboard;
        cout << "𝟙-𝕟𝕖𝕨 𝕘𝕒𝕞𝕖" << endl;
        cout << "𝟚-𝕊𝕖𝕥𝕥𝕚𝕟𝕘𝕤" << endl;
        cout << "𝟛-ℂ𝕣𝕖𝕕𝕚𝕥𝕤" << endl;
        cout << "𝟜-ℍ𝕖𝕝𝕡" << endl;
        cout << "𝟝-𝔼𝕩𝕚𝕥" << endl;
        int userInput = getUserInput();
        if (userInput == 1)
        {
            gameboard.print_Game_board();
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

bool loose()
{
    return false;
}

bool win()
{
    return false;
}

// void move_player(Player &player)
// {
//     Game_board game_board; // ایجاد یک شیء از Game_board
//     char userInput = player.getUserInput();
//     if (userInput == 's')
//     {
//         player.move(player.x, player.y - 1);
//         game_board.print_Game_board();
//     }
// }

char getUserInput_move()
{
    char input = _getch();
    return input;
}
int main()
{
    MainMenu menu;
    Game_board game_board;
    Clear_scr();
    menu.printHeader();
    menu.Options();
    menu.getUserInput();
    while (!(loose() || win()))
    {
        const char userinput = getUserInput_move();
        game_board.player.move(userinput);
        game_board.print_Game_board();
    }
}
