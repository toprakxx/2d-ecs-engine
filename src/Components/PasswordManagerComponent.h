#pragma once
#include <random>

struct PasswordManagerComponent {
	PasswordManagerComponent() : numKnownDigits(0) {
        static std::random_device rd;
        static std::mt19937 gen(rd());
        std::uniform_int_distribution<int> dist(0, 9);

        d1 = dist(gen);
        d2 = dist(gen);
        d3 = dist(gen);
	};

	int numKnownDigits;
	int d1, d2, d3;
};
