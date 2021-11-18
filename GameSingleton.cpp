#include "GameSingleton.h"
#include "Datas/LevelData.h"

GameSingleton GameSingleton::s_Instance;

void GameSingleton::Initialize()
{
	srand(static_cast<unsigned int>(std::time(nullptr)));

	const bool IsZero = rand() % 100 % 2 == 0;
	SetPlayerType(IsZero ? EPlayerType::ZERO : EPlayerType::CROSS);

	m_LevelController.AddLevel(&s_EntryLevel);
	m_LevelController.AddLevel(&s_ChooseDimentionLevel);
	m_LevelController.AddLevel(&s_PlayerSideLevel);

	m_Field.GenerateCells();
	m_Field.Initialize();

	m_LevelController.AddLevel(&s_FieldLevel);
	m_LevelController.AddLevel(&s_FinishLevel);
}

void GameSingleton::SetPlayerType(EPlayerType InPlayerType)
{
	m_PlayerType = InPlayerType;
	m_AIPlayerType = InPlayerType == EPlayerType::CROSS ? EPlayerType::ZERO : EPlayerType::CROSS;
}
