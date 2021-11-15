#include "GameSingleton.h"
#include "Datas/LevelData.h"

GameSingleton GameSingleton::s_Instance;

void GameSingleton::Initialize()
{
	m_LevelController.AddLevel(&s_EntryLevel);
	m_LevelController.AddLevel(&s_ChooseDimentionLevel);

	m_Field.GenerateCells();

	m_LevelController.AddLevel(&s_FieldLevel);
	m_LevelController.AddLevel(&s_FinishLevel);
}
