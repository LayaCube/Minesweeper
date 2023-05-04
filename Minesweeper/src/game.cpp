#include "minesweeper.hpp"

#include <constants.hpp>
#include <string>
#include <input.hpp>

void Minesweeper::GameDiscover()
{
	//No need to check if MousePosition is inbound as the Mouse Position won't update if it is not

	if (!mountain::Input::MouseDown[mountain::inputs::MouseButton_Left]) return;

	int x = tileSnap().x;
	int y = tileSnap().y;
	if (!isPositionValid(x, y)) return;

	if (board.tiles[x][y].isMine)	/*GameOver();*/return;
	if (board.tiles[x][y].isFlagged)	return;
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

void Minesweeper::GameFlag()
{
	if (!mountain::Input::MouseDown[mountain::inputs::MouseButton_Right]) {previousMouseFlag = false ; return;} 
	if( timerBetweenFlagging < 0.1f) return;
	if (previousMouseFlag) return;
	previousMouseFlag = true;
	
	timerBetweenFlagging = 0.f;
	int x = tileSnap().x;
	int y = tileSnap().y;
	if (!isPositionValid(x, y)) return;
	if (board.tiles[x][y].isDiscovered) return;

	board.tiles[x][y].isFlagged = !board.tiles[x][y].isFlagged;
	flagCount += board.tiles[x][y].isFlagged ? 1 : -1;
}

Vector2 Minesweeper::tileSnap()
{
	Vector2 index;
	index.x = (int) (mountain::Input::MousePosition.x / Const::defaultCaseSize.x);
	index.y = (int) (mountain::Input::MousePosition.y / Const::defaultCaseSize.y);
	return index;
}