#pragma once 

enum Scenes{
	StartMenu,
	Gameplay,
	DeathScreen,
	WinScene
};

class SceneLoader {
public:
	void LoadScene(Scenes level);
	void UnloadCurrentScene();
private:
};

