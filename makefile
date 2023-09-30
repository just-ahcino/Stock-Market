all:
	g++ -Iinclude -Isrc/headers -Llib -o Main src/*.cpp -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_mixer -mwindows
	rcedit "Main.exe" --set-file-version "1.0"
	rcedit "Main.exe" --set-product-version "1.0"
	rcedit "Main.exe" --set-icon "res/icon.ico"
