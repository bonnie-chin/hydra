CXX = g++
CXXFLAGS = -std=c++14 -g -Wall -MMD -Werror=vla
OBJECTS = subject.o card.o player.o joker.o head.o rules.o rule1.o rule2.o rule3.o rule4.o rule5.o cut.o controller.o cmdline_view.o test_view.o game.o main.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = hydra

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	rm ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies
