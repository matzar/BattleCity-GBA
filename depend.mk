bullet.o: bullet.cpp gba.h defines.h bullet.h map.h assets.h
character.o: character.cpp gba.h defines.h character.h
enemy.o: enemy.cpp gba.h defines.h enemy.h
font.o: font.cpp font.h
gba.o: gba.cpp gba.h
main.o: main.cpp gba.h font.h defines.h assets.h background.h map.h \
 player.h enemy.h bullet.h
main2.o: main2.cpp gba.h font.h defines.h assets.h background.h map.h \
 player.h bullet.h character.h
player.o: player.cpp gba.h defines.h player.h
