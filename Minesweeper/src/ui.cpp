#include "minesweeper.hpp"

#include <renderer.hpp>
#include <color.hpp>
#include <draw.hpp>
#include <constants.hpp>
#include <string>
#include <input.hpp>
#include <iostream>

void Minesweeper::GameOverScreen()
{
	dl->AddText(ImGui::GetFont(), 64, {0,  mountain::Renderer::WindowSize.y - 64.f}, ImColor(255,0,0,255), "Game Over");
	if (generalPurposeTimer > 1.0f && mountain::Input::MouseDown[mountain::inputs::MouseButton_Left])
	{
		scene = 0;
		InitBoard();
	}
}