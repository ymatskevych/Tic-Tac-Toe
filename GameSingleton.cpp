#include "GameSingleton.h"
#include "Datas/LevelData.h"

GameSingleton GameSingleton::s_Instance;

void GameSingleton::Initialize()
{
	srand(static_cast<unsigned int>(std::time(nullptr)));

	const bool IsZero = rand() % 100 % 2 == 0;
	SetPlayerType(IsZero ? ETokenType::ZERO : ETokenType::CROSS);

	m_Field.Initialize();

	m_LevelController.AddLevel(&s_EntryLevel);
	m_LevelController.AddLevel(&s_ChooseDimentionLevel);
	m_LevelController.AddLevel(&s_PlayerSideLevel);

	m_LevelController.AddLevel(&s_FieldLevel);
	m_LevelController.AddLevel(&s_FinishLevel);
}

void GameSingleton::SetPlayerType(ETokenType InTokenType)
{
	m_PlayerType = InTokenType;
	m_AIPlayerType = InTokenType == ETokenType::CROSS ? ETokenType::ZERO : ETokenType::CROSS;
}
