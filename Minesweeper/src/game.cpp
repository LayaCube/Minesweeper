#include "minesweeper.hpp"

#include <string>
#include <input.hpp>

void Minesweeper::GameDiscover(bool force)
{
	//No need to check if MousePosition is inbound as the Mouse Position won't update if it is not

	if (!mountain::Input::MouseDown[mountain::inputs::MouseButton_Left] && !force) return;

	int x = tileSnap().x;
	int y = tileSnap().y;
	if (!isPositionValid(x, y)) return;

	if (board.tiles[x][y].isFlagged)	return;
	if (board.tiles[x][y].isMine)
		{GameOver(); return;}
	if (!board.tiles[x][y].isDiscovered)
		AutoDiscovery(x, y);
}

void Minesweeper::AutoDiscovery(int x, int y)
{
	board.tiles[x][y].isDiscovered = true;
	hasStarted = true;
	if (board.tiles[x][y].value != 0) return;
    for (int dx = x-1; dx < x+2; dx++)
        for (int dy = y-1; dy < y+2; dy++)
            if (isPositionValid(dx, dy) && !board.tiles[dx][dy].isDiscovered && !board.tiles[dx][dy].isMine)
                AutoDiscovery(dx, dy);
    
}

void Minesweeper::GameOver()
{
	if (!hasStarted)
	{
		//reload all the board
		InitBoard();
		GameDiscover(true);
		hasStarted = true;
		return;
	}

	scene = 2;
	generalPurposeTimer = 0;
}

void Minesweeper::GameFlag()
{
	if (!mountain::Input::MouseDown[mountain::inputs::MouseButton_Right]) {previousMouseFlag = false ; return;} 
	if (previousMouseFlag) return;
	
	previousMouseFlag = true;
	
	int x = tileSnap().x;
	int y = tileSnap().y;
	if (!isPositionValid(x, y)) return;
	if (board.tiles[x][y].isDiscovered) return;

	if (flagCount >= mineNumber && !board.tiles[x][y].isFlagged)
		return;
	board.tiles[x][y].isFlagged = !board.tiles[x][y].isFlagged;
	flagCount += board.tiles[x][y].isFlagged ? 1 : -1;
	int sum = 0;
	for (int dx = 0; dx < board.size.x; dx++)
        for (int dy = 0; dy < board.size.y; dy++)
			if (board.tiles[dx][dy].isMine && board.tiles[dx][dy].isFlagged)
				sum ++;
	
	if (sum == mineNumber)
	{
		scene = 1;
		generalPurposeTimer = 0;
	}
}

Vector2 Minesweeper::tileSnap()
{
	Vector2 index;
	index.x = (int) (mountain::Input::MousePosition.x / Const::defaultCaseSize.x);
	index.y = (int) (mountain::Input::MousePosition.y / Const::defaultCaseSize.y);
	return index;
}

