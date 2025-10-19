#pragma once
#include "../ECS/ECS.h"
#include "../Components/TimerComponent.h"
#include "../Components/TextComponent.h"
#include "../SceneLoader/SceneLoader.h"
#include "../EventSystem/EventBus.hpp"
#include "../EventSystem/Events/TimerBridgeEvent.h"
#include "../EventSystem/Events/SoundEffectEvent.h"
#include <string>
#include <sstream>
#include <iomanip>

class TimerSystem : public System {
public:
	TimerSystem() {
		RequireComponent<TimerComponent>();
		RequireComponent<TextComponent>();
	}

	void Update(double deltaTime, SceneLoader *_sceneLoader, EventBus *eb) {
		for (auto& e : GetSystemEntities()) {
			textC = &e.GetComponent<TextComponent>();
			timeC = &e.GetComponent<TimerComponent>();
			sceneLoader = _sceneLoader;
			eventBus = eb;

			timeC->currentSeconds -= deltaTime;

			std::ostringstream ss;
			ss << std::fixed << std::setprecision(1) << timeC->currentSeconds;
			textC->text = ss.str();

			if((timeC->currentSeconds <= 2 * timeC->maxSeconds / 3.0) and !timeC->bridgeCollapsed) {
				eventBus->EmitEvent<TimerBridgeEvent>();
				eventBus->EmitEvent<SoundEffectEvent>("bridge-crash");
				timeC->bridgeCollapsed = true;
			}

			if(timeC->currentSeconds <= 0){
				sceneLoader->UnloadCurrentScene();
				sceneLoader->LoadScene(DeathScreen);
			}
		}
	}

	TextComponent* textC = nullptr;
	TimerComponent* timeC = nullptr;
	SceneLoader *sceneLoader = nullptr;
	EventBus *eventBus = nullptr;
};
