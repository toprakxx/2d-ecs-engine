#pragma once

struct PlayerInventoryComponent {
	PlayerInventoryComponent(
		bool key = false,
		bool card = false,
		bool bomb = false
	) :
		hasKey(key), hasCard(card), hasBomb(bomb)
	{}

	bool hasKey;
	bool hasCard;
	bool hasBomb;
};
