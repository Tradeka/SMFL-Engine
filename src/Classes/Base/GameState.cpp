#include "Classes/Base/GameState.h"

void GameState::DrawObjects(RenderWindow& window)
{
	const auto& objects = GetGameObjects();
	for (size_t i = 0; i < objects.size(); ++i)
	{
		if (objects[i])
			window.draw(*objects[i]);
	}
}