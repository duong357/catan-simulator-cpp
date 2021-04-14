run:
	#g++ -v -ggdb -fno-omit-frame-pointer -fsanitize=bounds -fsanitize=address -fsanitize=undefined -std=c++11 main.cpp -o a.out && ./a.out
	g++ -ggdb -std=c++11 main.cpp -o a.out && ./a.out
val:
	g++ -ggdb -std=c++11 main.cpp -o a.out && valgrind --leak-check=full ./a.out
