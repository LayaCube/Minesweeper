#include "minesweeper.hpp"

#include <renderer.hpp>
#include <color.hpp>
#include <draw.hpp>
#include <string>

void ResizeCallback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
	printf("%d ; %d\n", width, height);
}


void Minesweeper::Draw()
{
	glfwSetFramebufferSizeCallback(mountain::Renderer::GetWindow(), ResizeCallback);

	//Draw Tiles
	for (Vector2 loop = {0,0}; loop.x < board.size.x; loop.x++)
	{
		for (loop.y = 0; loop.y < board.size.y; loop.y++)
		{
			Vector2 pos = defaultCaseSize * loop;
			mountain::Draw::RectFilled(pos, defaultCaseSize, Const::COL_MAIN);
			mountain::Draw::Rect(pos, defaultCaseSize, Const::COL_SECO);
			if (board.tiles[loop.x][loop.y].isDiscovered)
			{
				int minesAround = board.tiles[loop.x][loop.y].value;
				if (board.tiles[loop.x][loop.y].isMine)
					dl->AddText(ImGui::GetFont(), defaultCaseSize.x, pos+10, ImColor(255,255,0,255), "M");
				else
					dl->AddText(ImGui::GetFont(), defaultCaseSize.x, pos, ImColor(31 * minesAround,0,0,255), std::to_string(minesAround).c_str());
			}
			else if (board.tiles[loop.x][loop.y].isFlagged)
				dl->AddText(ImGui::GetFont(), defaultCaseSize.x, pos, ImColor(0,0,255,255), "FF");
		}
	}

	//Draw Flag Counter
	std::string flag = std::to_string(flagCount) + "/" + std::to_string(mineNumber);
	dl->AddText(ImGui::GetFont(), defaultCaseSize.x, {mountain::Renderer::WindowSize.x-128.f, mountain::Renderer::WindowSize.y-96.f},
		ImColor(0,0,255,255), flag.c_str());
}

