bullet.o: bullet.cpp gba.h defines.h bullet.h map.h assets.h
enemy.o: enemy.cpp gba.h defines.h enemy.h
font.o: font.cpp font.h
gba.o: gba.cpp gba.h
main.o: main.cpp gba.h font.h defines.h assets.h background.h map.h \
 player.h enemy.h bullet.h
player.o: player.cpp gba.h defines.h player.h
