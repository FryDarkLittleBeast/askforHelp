run:compile
	./map input.txt

compile:
	g++ *.cpp -g -o map

clean:
	rm ./map

