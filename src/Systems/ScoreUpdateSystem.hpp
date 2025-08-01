#pragma once
#include <SDL.h>
#include <string>
#include "../ECS/ECS.h"
#include "../EventSystem/EventBus.hpp"
#include "../EventSystem/Events/CollisionEnterEvent.h"
#include "../Components/ScoreText.h"
#include "../Components/TextComponent.h"

class ScoreUpdateSystem : public System {
public:
	ScoreUpdateSystem() {
		RequireComponent<ScoreText>();
	}

	void Update() {
		for (auto e : GetSystemEntities()) {
			e.GetComponent<TextComponent>().text = "Score: " + std::to_string(score);
		}
	}

	void SubscribeToEvents(EventBus& eventBus) {
		eventBus.SubscribeToEvent<ScoreUpdateSystem, CollisionEnterEvent>(this, &ScoreUpdateSystem::OnPlayerScoreCollission);
	}

private:
	void OnPlayerScoreCollission(CollisionEnterEvent& event) {
		if(event.a.HasTag(Player) and event.b.HasTag(Score)
		or event.a.HasTag(Score) and event.b.HasTag(Player)){
			// Logger::Log("Player scored.");
			score++;
		}
	}

	int score = 0;
};
