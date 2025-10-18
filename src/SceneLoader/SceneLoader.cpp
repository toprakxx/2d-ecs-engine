#include "SceneLoader.h"
#include "../Utils.hpp"
#include "../ECS/ECS.h"
#include "../ECS/ECS.h"
#include "../Game/Game.h"
#include "../Components/TransformComponent.h"
#include "../Components/SpriteComponent.h"
#include "../Components/RigidBodyComponent.h"
#include "../Components/PlayerControlComponent.h"
#include "../Components/ColliderComponent.h"
#include "../Components/AnimationComponent.h"
#include "../Components/ParentComponent.h"
#include "../Components/CameraFollowComponent.h"
#include "glm/fwd.hpp"

auto &Registry = Registry::registry;
//////////////////////////////////////////////////
/// Helper Functions
//////////////////////////////////////////////////

inline int PseudoRandomTileOffset(int x, int y, int range) {
    unsigned h = x * 73856093u ^ y * 19349663u;
    return int(h % range);
}

enum GapSide { TOP=0, RIGHT=1, BOTTOM=2, LEFT=3 };

inline void CreateRoom(
    int wTiles, int hTiles,
    glm::vec2 startPos,
    const std::string& floorTile, int floorRange,
	bool haveWalls,
    const std::string& wallTile = "",  int wallRange = 0,
    std::bitset<4> gaps = std::bitset<4>(0),
    int doorWidthTiles = 3
) {
    const float S = SCALE_FACTOR_32;
    const int TW = 32, TH = 32;
    const int stepX = int(TW * S), stepY = int(TH * S);
    const int x0 = int(startPos.x), y0 = int(startPos.y);
    const int cx = wTiles / 2, cy = hTiles / 2;
    const int halfDoorX = doorWidthTiles / 2;
    const int halfDoorY = doorWidthTiles / 2;

    for (int ty = 0; ty < hTiles; ++ty) {
        for (int tx = 0; tx < wTiles; ++tx) {
            const bool onLeft   = (tx == 0);
            const bool onRight  = (tx == wTiles - 1);
            const bool onTop    = (ty == 0);
            const bool onBottom = (ty == hTiles - 1);
            bool border = onLeft || onRight || onTop || onBottom;

            if (border) {
                if (onTop    && gaps[TOP]    && std::abs(tx - cx) <= halfDoorX)    border = false;
                if (onBottom && gaps[BOTTOM] && std::abs(tx - cx) <= halfDoorX)    border = false;
                if (onLeft   && gaps[LEFT]   && std::abs(ty - cy) <= halfDoorY)    border = false;
                if (onRight  && gaps[RIGHT]  && std::abs(ty - cy) <= halfDoorY)    border = false;
            }

            const bool useWall = haveWalls ? border : false;
            const int  range   = useWall ? wallRange : floorRange;
            const auto& atlas  = useWall ? wallTile  : floorTile;

            const int x = x0 + tx * stepX;
            const int y = y0 + ty * stepY;

            Entity e = Registry->CreateEntity();
            e.AddComponent<TransformComponent>(glm::vec2(x, y), glm::vec2(S));

            int variant = (range > 0) ? PseudoRandomTileOffset(x, y, range) : 0;
            e.AddComponent<SpriteComponent>(atlas, TW, TH, useWall ? 3 : 0, false, TW * variant, 0);

            if (useWall) {
                e.AddComponent<ColliderComponent>(Box, glm::vec2(0,0), int(TW * S), int(TH * S));
                e.AddTag(Obstacle);
            }
        }
    }
}

inline glm::vec2 InTiles(float x, float y) {
	return glm::vec2(32 * SCALE_FACTOR_32 * x, 32 * SCALE_FACTOR_32 * y);
}

//////////////////////////////////////////////////
/// Member Functions
//////////////////////////////////////////////////
void SceneLoader::UnloadCurrentScene() {
	Registry->ClearEntities();
}

void SceneLoader::LoadScene(Scenes level) {
	switch (level) {
	case StartMenu: {
			//---//EntityName//---//
			//Entity entity = Registry->CreateEntity();
			//entity.AddComponent<ComponentType>(args);

			//---//PlayerCast//---//
			Entity playerInteractionCast = Registry->CreateEntity();
			playerInteractionCast.AddComponent<TransformComponent>(
				glm::vec2(0),
				glm::vec2(1)
			);
			playerInteractionCast.AddComponent<ColliderComponent>(
				Box,
				glm::vec2(0),
				PLAYER_INTERACTION_WIDTH,
				PLAYER_INTERACTION_HEIGHT
			);
			playerInteractionCast.AddTag(PlayerInteractionCast);

			//---//Player//---//
			Entity player = Registry->CreateEntity();
			player.AddComponent<TransformComponent>(
				// glm::vec2(Game::windowWidth/2 - 32, Game::windowHeight/2 - 32),
				glm::vec2(0, 0),
				glm::vec2(SCALE_FACTOR_32)
			);
			player.AddComponent<SpriteComponent>("time-bot", 32, 32, 5);
			player.AddComponent<AnimationComponent>(AnimationComponent{
				{"IdleSouth", 0, 4, true, 6},
				{"WalkSouth", 1, 4, true, 6},
				{"IdleEast" , 2, 4, true, 6},
				{"WalkEast" , 3, 4, true, 6},
				{"IdleNorth", 4, 4, true, 6},
				{"WalkNorth", 5, 4, true, 6},
				{"IdleWest" , 6, 4, true, 6},
				{"WalkWest" , 7, 4, true, 6},
			});
			player.AddComponent<RigidBodyComponent>(
				glm::vec2(0,0)
			);
			player.AddComponent<PlayerControlComponent>(500.0);
			player.AddComponent<ColliderComponent>(
				Box,
				glm::vec2(0,0),
				32 * SCALE_FACTOR_32,
				32 * SCALE_FACTOR_32
			);
			player.AddComponent<ParentComponent>(ParentComponent{
				{playerInteractionCast, glm::vec2(0)},
			});
			player.AddComponent<CameraFollowComponent>();
			player.AddTag(Player);

			//---//Wall//---//
			// Entity wall = Registry->CreateEntity();
			// wall.AddComponent<TransformComponent>(
			// 	glm::vec2(Game::windowWidth/2 + 100, Game::windowHeight/2 + 100),
			// 	glm::vec2(SCALE_FACTOR_32)
			// );
			// wall.AddComponent<SpriteComponent>("metal-ground", 32, 32, 5, false, 32*5, 0);
			// wall.AddComponent<ColliderComponent>(
			// 	Box,
			// 	glm::vec2(0,0),
			// 	32 * SCALE_FACTOR_32,
			// 	32 * SCALE_FACTOR_32
			// );
			// wall.AddTag(Obstacle);

			//---//Ground//---//
			int xg = (int) Game::windowWidth / 2;
			int yg = (int) Game::windowHeight / 2;
			CreateRoom(11, 11, InTiles(-5, -5), "metal-ground", 5, true, "metal-wall", 1, std::bitset<4>("1111"));
			CreateRoom(5, 10, InTiles(-2, -15), "metal-ground", 5, true, "metal-wall", 0, std::bitset<4>("0101"), 3);
			CreateRoom(5, 10, InTiles(-2, 6), "metal-ground", 5, true, "metal-wall", 0, std::bitset<4>("0101"), 3);

			break;
		}
	case Gameplay:{

			break;
		}
	case DeathScreen: {

			break;
		}
	}
}
