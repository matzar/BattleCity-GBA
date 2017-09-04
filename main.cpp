#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "gba.h"
#include "font.h"
#include "defines.h"
#include "assets.h"
#include "background.h"
#include "map.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
//c:\gba700\RunMake "$(CURRENT_DIRECTORY)" run
// function prototypes
void InitialiseDisplay();
void DrawText(int x, int y, const char string[]);
void DrawMap(const uint8_t map[MAP_WIDTH][MAP_HEIGHT]);

int main() {
	InitialiseDisplay();
	
	// draw the map
	DrawMap(map);
	// initialising the player
	Player player;
	player.Initialise(18, 18);
	// initialising player's bullet
	Bullet pBullet;
	pBullet.Initialise();
	// initialising enemy's bullet
	Bullet eBullet;
	eBullet.InitialiseEnemyBullet();
	// initialising the enemy
	Enemy enemy;
	enemy.Initialise(100, 120);
	
	while (true) {	
		// 13x13pixels
		if (player.m_Alive == true) {                                  
			pBullet.Fire(player.m_X, player.m_Y, player.m_bDirection); // fire bullet from tank's location
			pBullet.Update(map);                                       // move bullet on map
			player.Move(map);                                          // move player
		}
		
		if (enemy.m_Alive == true) {                                   
			enemy.Draw(map);                                                         // moving enemy on map
			if (rand()%60 == 0 && eBullet.m_Active == false){                        // enemy is shooting randomly
				eBullet.FireEnemyBullet(enemy.m_X, enemy.m_Y, enemy.m_bDirection);   // firing enemy's bullet
			}
			eBullet.UpdateEnemyBullet(map);                                          // moving enemy's bullet
		}
	
		if ( pBullet.m_X < enemy.m_X + enemy.m_eWidth &&    // collision detection
			pBullet.m_X + pBullet.m_bWidth > enemy.m_X &&   // between player's bullet
			pBullet.m_Y < enemy.m_Y + enemy.m_eHeight &&    // and enemy
			pBullet.m_bHeight + pBullet.m_Y > enemy.m_Y) {
			enemy.Destroy();                                // destroying enemy
			eBullet.Hide();                                 // hiding bullet after enemy dies
			enemy.m_Alive = false;
			DrawText(80, 0, "YOU WIN!");
		}
		
		
		if ( eBullet.m_X < player.m_X + player.m_pWidth &&  // collision detection
			eBullet.m_X + eBullet.m_bWidth > player.m_X &&  // between enemy's bullet
			eBullet.m_Y < player.m_Y + player.m_pHeight &&  // and player
			eBullet.m_bHeight + eBullet.m_Y > player.m_Y) {
			player.Destroy();                               // destroying player	
			player.m_Alive = false;
			DrawText(80, 0, "YOU LOSE!");	
		}
		
		WaitVSync();
		
		UpdateObjects();
	}
	
	return 0;
}	

void InitialiseDisplay() {
	// Set display options
	// DCNT_MODE0 sets mode 0, which provides four tiled backgrounds
	// DCNT_BG0 enables background 0 screen block 30 - Map 
	// DCNT_BG1 enables background 1 screen block 29 - Text
	// DCNT_BG2 enables background 2 screen block 28 - Not in use
	// DCNT_BG3 enables background 3 screen block 27 - Not in use
	// DCNT_OBJ enables objects
	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_BG2 | DCNT_BG3 | DCNT_OBJ;
	
	// Set background 0 options
	// BG_8BPP uses 8bpp tiles
	REG_BG0CNT = BG_CBB(0) | BG_SBB(30) | BG_8BPP | BG_REG_32x32;
	// Set horizontal and vertical offset for background 0 to (0, 0)
	REG_BG0HOFS = 0;
	REG_BG0VOFS = 0;
	// Set background 1 options
	REG_BG1CNT = BG_CBB(1) | BG_SBB(29) | BG_8BPP | BG_REG_32x32;
	// Set horizontal and vertical offset for background 1 to (0, 0)
	REG_BG1HOFS = 0;
	REG_BG1VOFS = 0;
	// Set background 2 options
	REG_BG2CNT = BG_CBB(1) | BG_SBB(28) | BG_8BPP | BG_REG_32x32;
	// Set horizontal and vertical offset for background 2 to (0, 0)
	REG_BG2HOFS = 0;
	REG_BG2VOFS = 0;
	// Set background 3 options
	REG_BG3CNT = BG_CBB(1) | BG_SBB(27) | BG_8BPP | BG_REG_32x32;
	// Set horizontal and vertical offset for background 3 to (0, 0)
	REG_BG3HOFS = 0;
	REG_BG3VOFS = 0;
	// Load background sprites
	LoadPaletteBGData(0, backgroundPal, sizeof (backgroundPal));
	SetPaletteBG(0, RGB(0, 0, 0)); //Set colour 0 in the palette to black
	LoadTileData(1, 1, backgroundTiles, sizeof (backgroundTiles));
	// Load objects sprites
	LoadPaletteObjData(0, assetsPal, sizeof (assetsPal));
	LoadTileData(4, 0, assetsTiles, sizeof (assetsTiles));
	// Load fonts
	for (int i = 0; i < 128; i++) {
		LoadTile8(0, i, font_medium[i]);
	}
	
	ClearObjects();
}
// function definitions
// function for displaying text on screen
void DrawText(int x, int y, const char string[]) {
	int lenght = strlen(string);
	for (int i = 0 ; i  <  lenght; ++i)
		SetTile(30, x + i, y, string[i]);
}
// function for displaying map on screen
void DrawMap(const uint8_t map[MAP_WIDTH][MAP_HEIGHT]) {
	for (int column = 0; column < 30; ++column) {
			for (int row = 0; row < 20; ++row) {
				SetTile(29, column, row, map[column][row]);
			}
		}
}