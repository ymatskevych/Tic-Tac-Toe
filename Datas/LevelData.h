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
		result += "***********";
		result += GAME_NAME;
		result += "**************";
		result += "\n";
		result += "************************************";
		result += "\n";
		result += "**********Press ENTER to************";
		result += "\n";
		result += "**********start the game************";
		result += "\n";
		result += "************************************";
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
		const std::string DimentionAmount = std::to_string(GetChoosenDimentionAmount());

		std::string result;
		result += "Please, choose amount of dimentions: ";
		result += "\n";
		result += "************************************";
		result += "\n";
		result += "**************";
		result += " " + DimentionAmount + " x " + DimentionAmount + " ";
		result += "***************";
		result += "\n";
		result += "************************************";
		result += "\n";
		result += "**********";
		result += "press UP or DOWN";
		result += "**********";
		result += "\n";
		result += "*******";
		result += "press ENTER to continue";
		result += "******";
		result += "\n";
		result += "************************************";
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
			GameSingleton::Get().InitializeField();
			break;
			}
		default: return;
		}
	}

private:

	void DecreaseDimentions()
	{
		GameSingleton::Get().GetField().SetDimentionAmount(std::max(MIN_DIMENTION, GetChoosenDimentionAmount() - 1));
	}

	void IncreaseDimentions()
	{
		GameSingleton::Get().GetField().SetDimentionAmount(std::min(GetChoosenDimentionAmount() + 1, MAX_DIMENTION));
	}

	int32_t GetChoosenDimentionAmount() const
	{
		return GameSingleton::Get().GetField().GetDimentionAmount();
	}
};

/*
 * 
 *		   YOU PLAY
 *
 *		CROSS(x)/ZERO(o)
 *
 *	 press ENTER to continue
 *
 */
class PlayerSideLevel : public ILevel
{
public:

	std::string GetLevelAsString() const override
	{
		std::string result;
		result += "************************************";
		result += "\n";
		result += "***********YOU*PLAY*****************";
		result += "\n";
		result += "************************************";
		result += "\n";
		result += GameSingleton::Get().GetPlayerType() == ETokenType::ZERO ? m_ZeroPlay : m_CrossPlay;
		result += "\n";
		result += "************************************";
		result += "\n";
		result += "*****press ENTER to continue********";
		result += "\n";
		result += "************************************";
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
		default: break;
		}
	}

private:

	std::string m_CrossPlay = "************CROSS(x)****************";
	std::string m_ZeroPlay =  "************ZERO(o)*****************";
};
/*
 *  x | o |
 * -----------
 *    | x | o
 * -----------
 *    | o | x 
 */
class FieldLevel : public ILevel
{
	std::string GetLevelAsString() const override
	{
		std::string result;
		result += "***************************************";
		result += "\n";
		result += "**Press**ENTER**to**make**your**move**";
		result += "\n";
		result += "***************************************";
		result += "\n";
		result += "\n";
		result += GameSingleton::Get().GetField().GetFieldAsString();
		return result;
	}

	void ProcessInput() override {}
};

class FinishLevel : public ILevel
{
	std::string GetLevelAsString() const override
	{
		EGameResult GameResult = GameSingleton::Get().GetGameResult();

		std::string result;
		result += "**************************";
		result += "\n";
		if (GameResult == EGameResult::WIN)
			result += "***********WIN************";
		else if (GameResult == EGameResult::LOSE)
			result += "***********LOSE***********";
		else if (GameResult == EGameResult::DRAW)
			result += "**********DRAW**********";
		result += "\n";
		result += "**************************";
		result += "\n";

		return result;
	}

	void ProcessInput() override
	{
		const Key LastInput = GameSingleton::Get().GetInputController().GetLastInput();
		if (LastInput == Key::ENTER)
		{
			exit(0);
		}
	}
};

static EntryLevel s_EntryLevel;
static ChooseDimentionLevel s_ChooseDimentionLevel;
static FieldLevel s_FieldLevel;
static FinishLevel s_FinishLevel;
static PlayerSideLevel s_PlayerSideLevel;