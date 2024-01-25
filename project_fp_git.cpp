#include <iostream>
#include <string>
#include <cstdlib>
#include <fstream>
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

void Header();

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
class Kill
{
public:
    int KillNumber;
    Kill(int number = 0) : KillNumber(number)
    {
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
            Beep(523, 5);
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
            srand(static_cast<unsigned>(time(0)));
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
};
// meow
class Gun
{
public:
    int AmmoNumber;
    int AmmoMagazine;
    int range;
    Gun()
    {
        AmmoNumber = 10;
        AmmoMagazine = 0;
        range = 3;
    }
    void shoot(char direction, Zombie *zombies, Player &player, Kill &kill_, int Level)
    {
        if (direction == 't' || direction == 'T')
        {
            if (AmmoNumber > 0)
            {
                AmmoNumber--;
                for (int i = 0; i < Level; i++)
                {
                    if (zombies[i].isActive && zombies[i].x == player.x && 0 <= (player.y - zombies[i].y) && (player.y - zombies[i].y) <= range)
                    {
                        zombies[i].isActive = false;
                        kill_.KillNumber++;
                        break;
                    }
                    else if (zombies[i].isActive && zombies[i].x == player.x)
                    {
                        cout << "\033[" << 10 << ";" << 25 << "H";
                        cout << "Out of range";
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
                cout << "Out of ammo!";
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
                for (int i = 0; i < Level; i++)
                {
                    if (zombies[i].isActive && zombies[i].x == player.x && 0 <= zombies[i].y - player.y && zombies[i].y - player.y <= range)
                    {
                        zombies[i].isActive = false;
                        kill_.KillNumber++;
                        // cout << "Zombie hit! Zombie at (" << zombies[i].x << ", " << zombies[i].y << ") eliminated." << endl;
                        break;
                    }
                    else if (zombies[i].isActive && zombies[i].x == player.x)
                    {
                        cout << "\033[" << 10 << ";" << 25 << "H";
                        cout << "Out of range";
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
                cout << "Out of ammo!";
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
                for (int i = 0; i < Level; i++)
                {
                    if (zombies[i].isActive && zombies[i].y == player.y && 0 <= zombies[i].x - player.x && zombies[i].x - player.x <= range)
                    {
                        zombies[i].isActive = false;
                        kill_.KillNumber++;
                        // cout << "Zombie hit! Zombie at (" << zombies[i].x << ", " << zombies[i].y << ") eliminated." << endl;
                        break;
                    }
                    else if (zombies[i].isActive && zombies[i].y == player.y)
                    {
                        cout << "\033[" << 10 << ";" << 25 << "H";
                        cout << "Out of range";
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
                cout << "Out of ammo!";
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
                for (int i = 0; i < Level; i++)
                {
                    if (zombies[i].isActive && zombies[i].y == player.y && 0 <= player.x - zombies[i].x && player.x - zombies[i].x <= range)
                    {
                        zombies[i].isActive = false;
                        kill_.KillNumber++;
                        // cout << "Zombie hit! Zombie at (" << zombies[i].x << ", " << zombies[i].y << ") eliminated." << endl;
                        break;
                    }
                    else if (zombies[i].isActive && zombies[i].y == player.y)
                    {
                        cout << "\033[" << 10 << ";" << 25 << "H";
                        cout << "Out of range";
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
                cout << "Out of ammo!";
                sleep(1);
                // پاک کردن پیام پس از تأخیر
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
    Level(int number = 2) : levelNumber(number)
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

class Game_Setting
{
public:
    bool is_mute = true;

    void Setting()
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

            Setting();
        }
        else if (step == 'n')
        {
            Header();
        }
    }

    char getUserInput_setting()
    {
        char sound;
        sound = _getch();

        return sound;
    }
};

class sound
{
    bool start = PlaySound(TEXT("/exit.wiv"), NULL, SND_ASYNC);
};
class Game_board
{
public:
    Level level;
    Vaccine vaccine;
    Credit credit;
    Round round;
    Health health;
    // Ammo ammo;
    Kill kill_;
    Player player;
    Zombie zombies[20];
    Door door;
    Gun gun;
    void Details()
    {
        cout << "Level: " << level.levelNumber << " ";
        cout << "Vaccine: " << vaccine.VaccineNumber << " ";
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
            for (int j = 0; j < i; j++)
            {
                while (is_same_position(zombies[i], zombies[j], i, j))
                {
                    zombies[i].setRandomCoordinates();
                }
            }
        }
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
        door.display();

        for (int i = 0; i < level.levelNumber; i++)
        {
            // zombies[i].setRandomCoordinates();
            for (int j = 0; j < level.levelNumber; j++)
            {
                if (!is_same_position(zombies[i], zombies[j], i, j))
                {
                    zombies[i].display();
                }
                else
                {
                    break;
                }
            }
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
        Game_Setting game_Setting;

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
        else if (userInput == 2)
        {
            game_Setting.Setting();
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

bool lose()
{
    return false;
}

bool win(Game_board game_board)
{
    if (game_board.player.x == game_board.door.x && game_board.player.y == game_board.door.y)
    {
        return true;
    }
    return false;
}

char getUserInput()
{
    char input = _getch();
    return input;
}

void Header() // نمایش منوی اصلی بازی
{
    MainMenu main;
    Clear_scr();
    main.printHeader();
    main.Options();
}

void save(Game_board &game_board)
{
    ofstream save("save_file.txt", ios::out);

    // ذخیره اطلاعات بازی در فایل
    save << "Level: " << game_board.level.levelNumber << endl;
    save << "Vaccine: " << game_board.vaccine.VaccineNumber << endl;
    save << "Credit: " << game_board.credit.CreditNumber << endl;
    save << "Round: " << game_board.round.RoundNumber << endl;
    save << "Health: " << game_board.health.HealthNumber << endl;
    save << "Ammo: " << game_board.gun.AmmoNumber << "/" << game_board.gun.AmmoMagazine << endl;
    save << "Kill: " << game_board.kill_.KillNumber << endl;
    save << "range: " << game_board.gun.range << endl;
    // ذخیره موقعیت بازیکن
    save << "Player Position: " << game_board.player.x << " " << game_board.player.y << std::endl;

    // ذخیره موقعیت زامبی‌ها
    for (int i = 0; i < game_board.level.levelNumber; ++i)
    {
        save << "Zombie Position: " << game_board.zombies[i].x << " " << game_board.zombies[i].y << std::endl;
    }
    // بستن فایل
    save.close();
    cout << "\033[" << 10 << ";" << 25 << "H";
    cout << "Game saved successfully.";
    sleep(3);
    // پاک کردن پیام پس از تأخیر
    cout << "\033[" << 10 << ";" << 17 << "H";
    cout << "                          ";
    cout << "\033[" << 20 << ";" << 1 << "H";
}

int main()
{
    int count = 0;

    Game_board game_board;
    Header();
    char userInput;

    while (!(lose()))
    {
        userInput = getUserInput(); // دریافت جهت حرکت
        // save game;
        if (userInput == '/')
        {
            save(game_board);
        }
        if (userInput == 'w' || userInput == 'a' || userInput == 's' || userInput == 'd')
            game_board.player.move(userInput); // حرکت بازیکن بر اساس جهت حرکت
        // userInput_shoot = getUserInput_move_shoot(); // دریافت جهت تیر
        // game_board.gun.shoot(userInput_shoot, game_board.zombies, game_board.player);
        // if (userInput == 'T' || userInput == 't')
        // {
        //     game_board.gun.shoot(userInput, game_board.zombies, game_board.player, game_board.kill.KillNumber);
        // }
        if (userInput == 't' || userInput == 'g' || userInput == 'f' || userInput == 'h')
        {
            game_board.gun.shoot(userInput, game_board.zombies, game_board.player, game_board.kill_, game_board.level.levelNumber);
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
        if (win(game_board))
        {
            for (int i = 0; i < game_board.level.levelNumber; i++)
            {
                game_board.zombies[i].isActive = true;
            }
            game_board.level.levelNumber++;
            Clear_scr();
            game_board.Reset_position();
            game_board.print_Game_board();
        }
    }
    return 0;
}
