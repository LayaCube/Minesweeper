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
		bool	isFlagged		= false;
	};

	struct Board {
		std::vector< std::vector <Tile> > tiles;
		Vector2 size;
	};
	ImDrawList* dl;
	Board board;
	int flagCount;
	bool previousMouseFlag = false;


	void Draw();
	void InitBoard();
	int checkAround(int x, int y, Vector2 size);
	bool isPositionValid(int x, int y);
	bool isPositionValid(Vector2 pos);
	Vector2 tileSnap();
	void GameDiscover();
	void AutoDiscovery(int x, int y);
	void GameFlag();
};
