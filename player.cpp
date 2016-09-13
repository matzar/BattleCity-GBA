#include "gba.h"
#include "defines.h"
#include "stdlib.h"
#include "player.h"

// constructor definition
Player::Player(int x, int y, int direction, uint16_t prevKeys, int bDirection, int rand_counter,
               bool alive, int pWidth, int pHeight ) {
m_X = x;				
m_Y = y;
m_Direction = direction;
m_PrevKeys = prevKeys;
m_bDirection = bDirection;
m_RandCounter = rand_counter;
m_Alive = alive;
m_pWidth = pWidth;
m_pHeight = pHeight;
}

void Player::Destroy() {
	ObjBuffer[PLAYER].attr0 = ATTR0_HIDE;                                                  // hide player
	ObjBuffer[ENEMY_BULLET].attr0 = ATTR0_HIDE;	                                           // hide enemy's bullet
	ObjBuffer[SMALL_BOOM].attr0 = ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(m_Y);  // display explosion on player's position
	ObjBuffer[SMALL_BOOM].attr1 = ATTR1_SIZE(1) | ATTR1_X(m_X);
}

void Player::Initialise(int start_x, int start_y) {
	// initialise and set variables
	m_X = start_x;
	m_Y = start_y;
	// Set up player
	SetObject(PLAYER,
	          ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(m_Y),
			  ATTR1_SIZE(1) | ATTR1_X(m_X),
			  ATTR2_ID8(OBJ_PLAYER_UP));
	// Set up small explosion
	SetObject(SMALL_BOOM,
	          ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_HIDE | ATTR0_Y(0),
			  ATTR1_SIZE(1) | ATTR1_X(0),
			  ATTR2_ID8(OBJ_SMALL_BOOM));
	// Set up big explosion
	SetObject(BIG_BOOM,
	          ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_HIDE | ATTR0_Y(0),
			  ATTR1_SIZE(1) | ATTR1_X(0),
			  ATTR2_ID8(OBJ_BIG_BOOM));
}

void Player::Move(const uint8_t map[MAP_WIDTH][MAP_HEIGHT]) {
	uint16_t currentKeys = REG_KEYINPUT;
	m_Direction = NONE;                     // preventing player from permanent movement
	m_RandCounter++;                        // add one to seeded number
	
	if ((currentKeys & KEY_RIGHT) == 0) {	// moving right and seeding random number
		m_Direction = RIGHT;                // set direction
		srand(m_RandCounter);               // seed random number
	}
	if ((currentKeys & KEY_LEFT) == 0) {    // moving left and seeding random number
		m_Direction = LEFT;
		srand(m_RandCounter);
	}
	if ((currentKeys & KEY_UP) == 0) {	    // moving up and seeding random number
		m_Direction = UP;
		srand(m_RandCounter);
	}
	if ((currentKeys & KEY_DOWN) == 0) {	// moving down and seeding random number
		m_Direction = DOWN;
		srand(m_RandCounter);
	}
	if (m_Direction != NONE) {              // direction for bullet when player is not moving
		m_bDirection = m_Direction;
	}
	
	switch (m_Direction) {
	// move right
	case RIGHT:
		if (CornersFree(m_X + 1, m_Y, map)) {                      // check if there is space to move into
			m_X++;                                                 // move right by 1
			ObjBuffer[PLAYER].attr2 = ATTR2_ID8(OBJ_PLAYER_RIGHT); // set sprite to match direction player is facing
			SetObjectX(PLAYER, m_X);                               // set new position
		}
		break;	
	// move up
	case UP:
		if (CornersFree(m_X, m_Y - 1, map)) {                       
			m_Y--;                                                 
			ObjBuffer[PLAYER].attr2 = ATTR2_ID8(OBJ_PLAYER_UP);     
			SetObjectY(PLAYER, m_Y);                                
		}
		break;	
	// move left
	case LEFT:
		if (CornersFree(m_X - 1, m_Y, map)) {                       
			m_X--;                                                 
			ObjBuffer[PLAYER].attr2 = ATTR2_ID8(OBJ_PLAYER_LEFT);   
			SetObjectX(PLAYER, m_X);                                
		}
		break;
	// move down
	case DOWN:
		if (CornersFree(m_X, m_Y + 1,map)) {
			m_Y++;
			ObjBuffer[PLAYER].attr2 = ATTR2_ID8(OBJ_PLAYER_DOWN);
			SetObjectY(PLAYER, m_Y);
		}
		break;
	}
	m_PrevKeys = currentKeys;
}
// Ascertain player's position on map
int Player::GetTileAt(int x, int y, const uint8_t map[MAP_WIDTH][MAP_HEIGHT]) {
	int tileX = x/SQUARESIZE;
	int tileY = y/SQUARESIZE;
	
	return map[tileX][tileY]; // return 0 or 1 depending on position of player on map
}
// Prevent from moving through walls by checking player's corners
bool Player::CornersFree(int x, int y, const uint8_t map[MAP_WIDTH][MAP_HEIGHT]) { 
	if (GetTileAt(x,                y,                 map) != EMPTY) return false;//check if left upper corner of player is free 
	if (GetTileAt(x + m_pWidth - 1, y,                 map) != EMPTY) return false;//check if right upper corner of player is free 
	if (GetTileAt(x,                y + m_pHeight - 1, map) != EMPTY) return false;//check if left bottom corner of player is free 
	if (GetTileAt(x + m_pWidth - 1, y + m_pHeight - 1, map) != EMPTY) return false;//check if right bottom corner of player is free  
	return true; //if all corners are free return true
}