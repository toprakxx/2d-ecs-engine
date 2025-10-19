#pragma once
#include "../ECS/ECS.h"
#include "../Components/PasswordManagerComponent.h"
#include "../Components/TextComponent.h"
#include <string>

class PassworManagerSystem : public System {
public:
	PassworManagerSystem() {
		RequireComponent<TextComponent>();
		RequireComponent<PasswordManagerComponent>();
	};

	void Update() {
		for (auto &e : GetSystemEntities()) {
			auto &pass = e.GetComponent<PasswordManagerComponent>();
			if (pass.numKnownDigits == numLastKnowDigit) return;
			numLastKnowDigit = pass.numKnownDigits;
			auto &text = e.GetComponent<TextComponent>();

			switch (numLastKnowDigit) {
			case 1:
				text.text = "Password: " + std::to_string(pass.d1) + " _ _";
				break;
			case 2:
				text.text = "Password: " + std::to_string(pass.d1) +  " " + std::to_string(pass.d2) + " _";
				break;
			case 3:
				text.text = "Password: " + std::to_string(pass.d1) +  " " + std::to_string(pass.d2) +  " " + std::to_string(pass.d3);
				break;
			}
		}
	}

	int numLastKnowDigit = 0;
};
