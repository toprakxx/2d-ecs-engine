#pragma once
#include "../ECS/ECS.h"
#include "../EventSystem/EventBus.hpp"
#include "../InputManager/InputManager.h"
#include "../Components/DoorComponent.h"
#include "../Components/PlayerInventoryComponent.h"
#include "../EventSystem/Events/CollisionEvent.h"
#include "../SceneLoader/SceneLoader.h"

class BatterySystem : public System {
public:
	void SubscribeToEvents(EventBus &eb, SceneLoader *_sceneLoader) {
		eb.SubscribeToEvent(this, &BatterySystem::OnPlayerCollision);
		sceneLoader = _sceneLoader;
	}

	void OnPlayerCollision(CollisionEvent &e){
		if(e.a.HasTag(Player) and e.b.HasTag(Battery)
		or e.a.HasTag(Battery) and e.b.HasTag(Player)) {

			// Entity player = e.a.HasTag(Player) ? e.a : e.b;
			// Entity battery = e.a.HasTag(Battery) ? e.a : e.b;

			sceneLoader->UnloadCurrentScene();
			sceneLoader->LoadScene(WinScene);
		}
	}

	SceneLoader *sceneLoader = nullptr;
};
