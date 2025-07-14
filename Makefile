.PHONY: source build run
.ONESHELL:

restart: clean source build run
play: source build run

source:
	#Generating the compile_commands file for clangd lsp
	cd .\make
	cmake -G "Unix Makefiles" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
	move .\compile_commands.json ..
	#Actual cmake step
	cd ..\build
	cmake ..

build:
	cd .\build
	cmake --build .

run:
	".\build\Debug\main.exe"

clean:
	del "compile_commands.json"
	rmdir /S /Q build
	mkdir build
	rmdir /S /Q make
	mkdir make
