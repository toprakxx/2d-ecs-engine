#pragma once
#include "../ECS/ECS.h"
#include "../Components/TimerComponent.h"
#include "../Components/TextComponent.h"
#include "../SceneLoader/SceneLoader.h"
#include <string>
#include <sstream>
#include <iomanip>

class TimerSystem : public System {
public:
	TimerSystem() {
		RequireComponent<TimerComponent>();
		RequireComponent<TextComponent>();
	}

	void Update(double deltaTime, SceneLoader *_sceneLoader) {
		for (auto& e : GetSystemEntities()) {
			// if (!fetch) {
				textC = &e.GetComponent<TextComponent>();
				timeC = &e.GetComponent<TimerComponent>();
				sceneLoader = _sceneLoader;
			// 	fetch = true;
			// }

			timeC->currentSeconds -= deltaTime;

			std::ostringstream ss;
			ss << std::fixed << std::setprecision(1) << timeC->currentSeconds;
			textC->text = ss.str();

			if(timeC->currentSeconds <= 0){
				sceneLoader->UnloadCurrentScene();
				sceneLoader->LoadScene(DeathScreen);
			}
		}
	}

	bool fetch = false;
	TextComponent* textC = nullptr;
	TimerComponent* timeC = nullptr;
	SceneLoader *sceneLoader = nullptr;
};
