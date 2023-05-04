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

	board.tiles[x][y].isDiscovered = true;
	if (board.tiles[x][y].isMine)	/*GameOver();*/return;
	
}