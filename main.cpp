#include <iostream>
#include <termios.h>
#include <unistd.h>

struct termios initState{};

void disabelRawMode()
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &initState);
}

void enableRawMode()
{
    struct termios raw{};

    tcgetattr(STDIN_FILENO, &initState);
    atexit(disabelRawMode);

    tcgetattr(STDIN_FILENO, &raw);

    raw.c_iflag &= ~(IXON | ICRNL);
    raw.c_lflag &= ~(ECHO | ICANON | ISIG | IEXTEN);
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

int main()
{
    struct termios prev;

    enableRawMode();

    char c{};

    while (c != 'q')
    {
        c = getchar();
        if(iscntrl(int(c))){
            std::cout << int(c) << "\n";
        }
        else{
            std::cout << int(c) << " : " << c << "\n";
        }
    }

    return 0;
}