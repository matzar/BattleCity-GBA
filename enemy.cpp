#include "gba.h"
#include "defines.h"
#include "enemy.h"

// constructor definition
Enemy::Enemy(int x, int y, int direction, bool alive, int bDirection, int eWidth, int eHeight) {
m_X = x;			
m_Y = y;
m_Direction = direction;
m_Alive = alive;
m_bDirection = bDirection;
m_eWidth = eWidth;
m_eHeight = eHeight;
}
// Destroying the enemy
void Enemy::Destroy() {
	ObjBuffer[ENEMY].attr0 = ATTR0_HIDE;                                                   // hide the enemy
	ObjBuffer[ENEMY_BULLET].attr0 = ATTR0_HIDE;	                                           // hide enemy's bullet
	ObjBuffer[BULLET].attr0 = ATTR0_HIDE;	                                               // hide player's bullet
	ObjBuffer[SMALL_BOOM].attr0 = ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(m_Y);  // display explosion 
	ObjBuffer[SMALL_BOOM].attr1 = ATTR1_SIZE(1) | ATTR1_X(m_X);
}
// Initialising the enemy
void Enemy::Initialise(int start_x, int start_y) {
	m_X = start_x;
	m_Y = start_y;
	m_Direction = RIGHT;
	
	SetObject(ENEMY,
	          ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_REG | ATTR0_Y(m_Y),
			  ATTR1_SIZE(1) | ATTR1_X(m_X),
			  ATTR2_ID8(OBJ_ENEMY_RIGHT));
			  
	SetObjectX(ENEMY, m_X);
	SetObjectY(ENEMY, m_Y);
}
// Moving the enemy on the map
void Enemy::Draw(const uint8_t map[MAP_WIDTH][MAP_HEIGHT]) {
	switch (m_Direction)
	{
	// move right
	case RIGHT:
		// check if there is space to move into
		if (CornersFree(m_X + 1, m_Y, map)) {
			m_Direction = RIGHT;
			m_X++;
			ObjBuffer[ENEMY].attr2 = ATTR2_ID8(OBJ_ENEMY_RIGHT); // set sprite to match the direction the ENEMY is facing
			SetObjectX(ENEMY, m_X);                              // move the enemy
		}
		else
		{
			m_Direction = UP;
		}
		break;	
	// move up
	case UP:
		// check if there is space to move into
		if (CornersFree(m_X, m_Y - 1, map)) {
			m_Direction = UP;
			m_Y--;
			ObjBuffer[ENEMY].attr2 = ATTR2_ID8(OBJ_ENEMY_UP);// set sprite to match the direction the ENEMY is facing
			SetObjectY(ENEMY, m_Y);
		}
		else {
			m_Direction = LEFT;
		}
		break;	
	// move left
	case LEFT:
		// check if there is space to move into
		if (CornersFree(m_X - 1, m_Y, map)) {
			m_Direction = LEFT;
			m_X--;
			ObjBuffer[ENEMY].attr2 = ATTR2_ID8(OBJ_ENEMY_LEFT); // set sprite to match the direction the ENEMY is facing
			SetObjectX(ENEMY, m_X);
		}
		else {
		m_Direction = DOWN;
		}
		break;
	// move down
	case DOWN:
		// check if there is space to move into
		if (CornersFree(m_X, m_Y + 1,map)) {
			m_Direction = DOWN;
			m_Y++;
			ObjBuffer[ENEMY].attr2 = ATTR2_ID8(OBJ_ENEMY_DOWN);// set sprite to match the direction the ENEMY is facing
			SetObjectY(ENEMY, m_Y);
		}
		else {
		m_Direction = RIGHT;
		}
		break;
	}
	if (m_Direction != NONE) {
		m_bDirection = m_Direction;
	}
}
// Ascertain enemy's position on map
int Enemy::GetTileAt(int x, int y, const uint8_t map[MAP_WIDTH][MAP_HEIGHT]) {
	int tileX = x/SQUARESIZE;
	int tileY = y/SQUARESIZE;
	
	return map[tileX][tileY]; // return 0 or 1 depending on position of enemy on map
}
// Prevent from moving through walls by checking enemy's corners
bool Enemy::CornersFree(int x, int y, const uint8_t map[MAP_WIDTH][MAP_HEIGHT]) { 
	if (GetTileAt(x,                y,                 map) != EMPTY) return false;//check if left upper corner of enemy is free 
	if (GetTileAt(x + m_eWidth - 1, y,                 map) != EMPTY) return false;//check if right upper corner of enemy is free 
	if (GetTileAt(x,                y + m_eHeight - 1, map) != EMPTY) return false;//check if left bottom corner of enemy is free 
	if (GetTileAt(x + m_eWidth - 1, y + m_eHeight - 1, map) != EMPTY) return false;//check if right bottom corner of enemy is free  
	return true; //if all corners are free return true
}