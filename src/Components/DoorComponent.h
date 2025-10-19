#pragma once

enum DoorID {
	CardDoor,
	KeyDoor,
	BombDoor
};

struct DoorComponent {
	DoorComponent(DoorID _id = CardDoor) : doorId(_id) {}

	DoorID doorId;
};
