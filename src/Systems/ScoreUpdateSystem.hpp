#pragma once
#include <SDL.h>
#include <string>
#include "../ECS/ECS.h"
#include "../EventSystem/EventBus.hpp"
#include "../EventSystem/Events/CollisionEnterEvent.h"
#include "../Components/ScoreText.h"
#include "../Components/TextComponent.h"
#include "../Components/PlayerControlComponent.h"

class ScoreUpdateSystem : public System {
public:
	ScoreUpdateSystem() {
		RequireComponent<ScoreText>();
	}

	void Update() {
		for (auto e : GetSystemEntities()) {
			e.GetComponent<TextComponent>().text = "Score: " + std::to_string(
				e.GetComponent<ScoreText>().score);
		}
	}

	void SubscribeToEvents(EventBus& eventBus) {
		eventBus.SubscribeToEvent<ScoreUpdateSystem, CollisionEnterEvent>(this, &ScoreUpdateSystem::OnPlayerScoreCollission);
	}

private:
	void OnPlayerScoreCollission(CollisionEnterEvent& e) {
		if(e.a.HasTag(Player) and e.b.HasTag(Score)
		or e.a.HasTag(Score) and e.b.HasTag(Player)){
			auto& player = e.a.HasTag(Player) ? e.a : e.b;
			auto& scoreBox = e.a.HasTag(Score) ? e.a : e.b;
		
		if(player.GetComponent<PlayerControlComponent>().isAlive) {
				for (auto e : GetSystemEntities()) {
					e.GetComponent<ScoreText>().score++;
				}
				scoreBox.Kill();
			}
		}
	}
};
