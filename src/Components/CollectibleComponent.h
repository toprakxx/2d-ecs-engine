#pragma once

enum CollectibleID {
	Card,
	Key,
	Bomb
};

struct CollectibleComponent {
	CollectibleComponent(CollectibleID _id = Card) : collId(_id) {}

	CollectibleID collId;
};
