#pragma once

#include <iostream>

#include "Interfaces/ILevel.h"
#include "GameData.h"
#include "GameSingleton.h"

/*
 *
 *	        TIC-TAC-TOE
 *
 *  Press ENTER to start the game
 *
 */
class EntryLevel : public ILevel
{
public:

	std::string GetLevelAsString() const override
	{
		std::string result;
		result += GAME_NAME;
		result += "\n";
		result += "Press ENTER to ";
		result += "\n";
		result += " start the game";
		result += "\n";

		return result;
	}

	void ProcessInput() override
	{
		const Key LastInput = GameSingleton::Get().GetInputController().GetLastInput();

		switch (LastInput)
		{
		case Key::ENTER:
		{
			GameSingleton::Get().GetLevelController().GoToNextLevel();
			break;
		}
		default: return;
		}
	}
};

/* 
 *
 *  Please, choose amount of dimentions:
 *	              5 x 5
 *	        press UP or DOWN
 * 	      press ENTER to continue
 *
 */
class ChooseDimentionLevel: public ILevel
{
public:

	std::string GetLevelAsString() const override
	{
		const std::string DimentionAmount = std::to_string(m_CurrentDimentionAmount);

		std::string result;
		result += "Please, choose amount of dimentions: ";
		result += "\n";
		if (m_CurrentDimentionAmount % 10 == 0)
		{
			result += " " + DimentionAmount + " x " + DimentionAmount;
		}
		else
		{
			result += "  " + DimentionAmount + " x " + DimentionAmount;
		}
		
		result += "\n";
		result += " \t press UP or DOWN";
		result += "\n";
		result += " \t press ENTER to continue";
		result += "\n";
		return result;
	}

	void ProcessInput() override
	{
		const Key LastInput = GameSingleton::Get().GetInputController().GetLastInput();

		switch (LastInput)
		{
		case Key::UP:
			{
				IncreaseDimentions();
				break;
			}
		case Key::DOWN:
			{
				DecreaseDimentions();
				break;
			}
		case Key::ENTER:
			{
			GameSingleton::Get().GetLevelController().GoToNextLevel();
			break;
			}
		default: return;
		}
	}

private:

	void DecreaseDimentions()
	{
		m_CurrentDimentionAmount = std::max(MIN_DIMENTION, m_CurrentDimentionAmount - 1);
	}

	void IncreaseDimentions()
	{
		m_CurrentDimentionAmount = std::min(m_CurrentDimentionAmount + 1, MAX_DIMENTION);
	}

	int32_t GetChoosenDimentionAmount() const
	{
		return std::min(std::max(MIN_DIMENTION, m_CurrentDimentionAmount), MAX_DIMENTION);
	}

	int32_t m_CurrentDimentionAmount = DEFAULT_DIMENTION;
};

class FieldLevel : public ILevel
{
	std::string GetLevelAsString() const override
	{
		return GameSingleton::Get().GetField().GetFieldAsString();
	}

	void ProcessInput() override
	{
		
	}
};

static EntryLevel s_EntryLevel;
static ChooseDimentionLevel s_ChooseDimentionLevel;
static FieldLevel s_FieldLevel;