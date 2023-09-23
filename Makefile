
build: 
	@g++ main.cpp -lSDL2 -std=c++20 -o main

run: build
	@./main
