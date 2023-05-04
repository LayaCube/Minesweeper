#include "minesweeper.hpp"

#include <renderer.hpp>
#include <color.hpp>
#include <draw.hpp>
#include <constants.hpp>
#include <string>

void ResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	printf("%d ; %d\n", width, height);
}


void Minesweeper::Draw()
{
	glfwSetFramebufferSizeCallback(mountain::Renderer::GetWindow(), ResizeCallback);
	for (Vector2 loop = {0,0}; loop.x < board.size.x; loop.x++)
	{
		for (loop.y = 0; loop.y < board.size.y; loop.y++)
		{
			Vector2 pos = Const::defaultCaseSize * loop;
			mountain::Draw::RectFilled(pos, Const::defaultCaseSize, Const::COL_MAIN);
			mountain::Draw::Rect(pos, Const::defaultCaseSize, Const::COL_SECO);
			if (board.tiles[loop.x][loop.y].isDiscovered)
			{
				int minesAround = board.tiles[loop.x][loop.y].value;
				if (board.tiles[loop.x][loop.y].isMine)
					dl->AddText(ImGui::GetFont(), 64, pos+10, ImColor(255,255,0,255), "M");
				else
					dl->AddText(ImGui::GetFont(), 64, pos, ImColor(31 * minesAround,0,0,255), std::to_string(minesAround).c_str());
			}
		}
	}
}

