#include "minesweeper.hpp"

#include <constants.hpp>
#include <string>
#include <input.hpp>

void Minesweeper::GameClick()
{
	//No need to check if MousePosition is inbound as the Mouse Position won't update if it is not

	if (!mountain::Input::MouseDown[mountain::inputs::MouseButton_Left]) return;

	int x = (int) (mountain::Input::MousePosition.x / Const::defaultCaseSize.x);
	int y = (int) (mountain::Input::MousePosition.y / Const::defaultCaseSize.y);
	if (!isPositionValid(x, y)) return;

	if (board.tiles[x][y].isMine)	/*GameOver();*/return;
	if (!board.tiles[x][y].isDiscovered)
	AutoDiscovery(x, y);
}

void Minesweeper::AutoDiscovery(int x, int y)
{
	board.tiles[x][y].isDiscovered = true;
	if (board.tiles[x][y].value != 0) return;
    for (int dx = x-1; dx < x+2; dx++)
        for (int dy = y-1; dy < y+2; dy++)
            if (isPositionValid(dx, dy) && !board.tiles[dx][dy].isDiscovered && !board.tiles[dx][dy].isMine)
                AutoDiscovery(dx, dy);
    
}