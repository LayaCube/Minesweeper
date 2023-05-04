#include "minesweeper.hpp"

int main(int, char*[])
{
    Minesweeper m;
    m.Initialize();
    m.MainLoop();
    m.Shutdown();
}
