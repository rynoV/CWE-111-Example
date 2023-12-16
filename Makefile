exp: src/main/java/Main.c src/main/java/org/example/Main.java
	@cd src/main/java; javac -h . org/example/Main.java
	@cd src/main/java;\
	    gcc -g -fno-stack-protector -I /usr/lib/jvm/java-11-openjdk/include/ -I /usr/lib/jvm/java-11-openjdk/include/linux/\
	    Main.c -shared -o libmain.so -fPIC > /dev/null 2>&1

run: exp
	@cd src/main/java; rm accounting-compensation.ssv; java -Djava.library.path=. org.example.Main hr-compensation.csv; cat accounting-compensation.ssv

run-exploit: exp
	@cd src/main/java; rm accounting-compensation.ssv; java -Djava.library.path=. org.example.Main john-hr-compensation.csv; cat accounting-compensation.ssv
