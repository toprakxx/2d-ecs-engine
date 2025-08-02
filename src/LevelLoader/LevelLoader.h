#pragma once 

enum Levels{
	StartMenu,
	Gameplay,
	DeathScreen
};

class LevelLoader {
public:
	void LoadLevel(Levels level);
	void UnloadCurrentLevel();
private:
};

