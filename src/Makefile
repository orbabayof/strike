install:
	ninja -C ../build
	cp ../build/compile_commands.json .
	cp ../build/src/strike .

clean:
	rm compile_commands.json strike

run:
	sleep 10 && pkill strike &
	./strike
