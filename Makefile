CFLAGS = -lGL -lglut -lGLU -lm -lGLEW
#CFLAGS = -lGL -lGLU -lglut -lX11 -lpthread -lXrandr -lXi -ldl -lm

build: 
	mkdir -p build

graphic: build src/main.cpp 
	clang++ src/*.c* $(CFLAGS) -o build/graphic

run: graphic
	build/graphic

clean:
	rm build/*
