#pragma once

#include <game.hpp>

class Minesweeper : public mountain::Game
{
public:
    Minesweeper();

	// Inherited via Game
	virtual void Update() override;
	virtual void Render() override;
};
