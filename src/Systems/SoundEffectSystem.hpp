#pragma once
#include "../ECS/ECS.h"
#include "../AssetManager/AssetManager.h"
#include "../EventSystem/EventBus.hpp"
#include "../EventSystem/Events/SoundEffectEvent.h"
#include "SDL_mixer.h"

class SoundEffectSystem : public System {
public:
	SoundEffectSystem() = default; //Does not require a component as of now
	
	void SubscribeToEvents(EventBus& eventBus, AssetManager* assetManager) {
		eventBus.SubscribeToEvent<SoundEffectSystem, SoundEffectEvent> (this, &SoundEffectSystem::OnSoundEffectCalled);
		this->assetMan = assetManager;
	}

	void OnSoundEffectCalled(SoundEffectEvent& e) {
		Mix_Chunk* sfx = assetMan->GetSFX(e.sfxName);
		if(Mix_PlayChannel(-1, sfx, 0) == -1) {
			Logger::Err("Sound could not be played: " + e.sfxName);
		}
	}

	AssetManager* assetMan = nullptr;
};
