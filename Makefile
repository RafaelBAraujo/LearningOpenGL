output: main.o display.o mesh.o shader.o stb_image.o texture.o meshloader.o
	g++ main.o display.o mesh.o shader.o stb_image.o texture.o meshloader.o -std=c++11 -lGLEW -lGL -lassimp -lSDL2 -lm -o output

main.o: src/main.cpp
	g++ -c src/main.cpp -Iinclude -std=c++11

display.o: src/display.cpp include/display.h
	g++ -c src/display.cpp -Iinclude -std=c++11

mesh.o: src/mesh.cpp include/mesh.h
	g++ -c src/mesh.cpp -Iinclude -std=c++11

shader.o: src/shader.cpp include/shader.h include/camera.h include/transform.h
	g++ -c src/shader.cpp -Iinclude -std=c++11

stb_image.o: include/stb/stb_image.cpp include/stb/stb_image.h
	g++ -c include/stb/stb_image.cpp -Iinclude/stb -std=c++11

texture.o: src/texture.cpp include/texture.h include/stb/stb_image.h
	g++ -c src/texture.cpp -Iinclude -Iinclude/stb -std=c++11

meshloader.o: src/meshloader.cpp include/meshloader.h
	g++ -c src/meshloader.cpp -Iinclude -std=c++11

clean:
	rm *.o output