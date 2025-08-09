# 2D ECS Engine
A small 2D ECS engine I built to better understand low-level game programming and engine design.  
**Libraries:** SDL2, SDL2_mixer, SDL2_image, ImGui, GLM


## Demo
Below is a little demo showing the current capabilities of the engine.  
<video src="./showcase/bird-video.mp4" controls playsinline></video>
<!-- ![video](./showcase/bird-video.mp4) -->
<!-- ![flappy-bird-demo](./showcase/bird-demo.gif) -->

## Features
- AABB collision with sweep-and-prune broadphase
- Synchronous event system
- Animated sprites
- Data-oriented ECS architecture
- Keyboard and mouse input

## How to run

- **Prebuilt**  
  Download the latest Windows build from the **Releases** page and run `main.exe`.

- **Build with Make**  
  Clone the repo and run:
  ``` make play ```

- **Build with CMake**  
  Clone the repo, go in to the ```/build``` directory and run ``` cmake .. ```

#### Notes
The engine is in a MVP state with small game(s) to showcase what it is currently capable of, I will most likely keep updating it.  
Many thanks to Gustavo Pezzi from [pikuma.com](https://pikuma.com) for much of the inspration and information behind the making of this engine.