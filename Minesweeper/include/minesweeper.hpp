#pragma once

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>
#include <game.hpp>
#include <vector.hpp>
#include <constants.hpp>

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

	//Structs
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

	//Variables
	float generalPurposeTimer = 0.0f;
	int flagCount;
	int mineNumber;
	bool previousMouseFlag = false;
	bool hasStarted = false;
	int scene = 0;


	//Functions
	void Draw();
	void InitBoard();
	int checkAround(int x, int y, Vector2 size);
	bool isPositionValid(int x, int y);
	bool isPositionValid(Vector2 pos);
	Vector2 tileSnap();
	void GameDiscover(bool force = false);
	void AutoDiscovery(int x, int y);
	void GameFlag();
	void GameOver();
	void GameOverScreen();

	//Constants to overwrite
	Vector2 defaultCaseSize = Const::defaultCaseSize;
	void varUpdate();
};
