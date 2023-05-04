#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <game.hpp>
#include <vector.hpp>

class Minesweeper : public mountain::Game
{
public:
	Minesweeper();

	// Inherited via Game
	void Update() override;
	void Render() override;

	void Initialize() override;
	void PreRender() override;
	void PostRender() override;
	void Shutdown() override;

	struct Tile {
		bool	isDiscovered	= false;
		int		value			= 0;
		bool	isMine			= false;
	};

	struct Board {
		std::vector< std::vector <Tile> > tiles;
		Vector2 size;
	};
	ImDrawList* dl;
	Board board;

	void Draw();
	void InitBoard();
	int checkAround(int x, int y, Vector2 size);
	bool isPositionValid(int x, int y);
	bool isPositionValid(Vector2 pos);
	void GameClick();
};
