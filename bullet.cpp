#include "gba.h"
#include "defines.h"
#include "bullet.h"
#include "map.h"
#include "assets.h"

// constructor definition
Bullet::Bullet(int x, int y, int direction, bool active, int bWidth, int bHeight, int prevKeys) {
m_X = x;		
m_Y = y;
m_Direction = direction;
m_Active = active;
m_bWidth = bWidth;
m_bHeight = bHeight;
m_PrevKeys = prevKeys;
}
// Set up and hide player's bullet
void Bullet::Initialise() {
	SetObject(BULLET,
	          ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_HIDE | ATTR0_Y(0),
			  ATTR1_SIZE(0) | ATTR1_X(0),
			  
			  ATTR2_ID8(OBJ_BULLET));
}
// Set up and hide enemy's bullet
void Bullet::InitialiseEnemyBullet() {
	SetObject(ENEMY_BULLET,
	          ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_HIDE | ATTR0_Y(0),
			  ATTR1_SIZE(0) | ATTR1_X(0),
			  ATTR2_ID8(OBJ_BULLET));
}

// Function for firing player's bullet
void Bullet::Fire(int start_x, int start_y, int projected_direction) {
	uint16_t currentKeys = REG_KEYINPUT;
	uint16_t changed = REG_KEYINPUT ^ m_PrevKeys;
	if((REG_KEYINPUT & KEY_A) == 0 && (changed & KEY_A) != 0) { // firing only once even when A button is held
		m_X = start_x + 5;                   // setting bullet's position in the middle of tank
		m_Y = start_y + 5; 
		m_Direction = projected_direction;	 // give bullet tank's direction
		
		
		ObjBuffer[BULLET].attr0 = ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_REG; // show bullet
		// start drawing bullet from tank's position
		SetObjectX(BULLET, m_X); 
		SetObjectY(BULLET, m_Y); 
		
		switch (m_Direction) { // match bullet's sprite with direction
		case RIGHT:
			ObjBuffer[BULLET].attr2 = ATTR2_ID8(OBJ_BULLET_RIGHT);
			m_bWidth = 8 ;
			m_bHeight = 3;
			break;
		case UP:
			ObjBuffer[BULLET].attr2 = ATTR2_ID8(OBJ_BULLET_UP);
			m_bWidth = 3 ;
			m_bHeight = 8;
			break;	
		case LEFT:
				ObjBuffer[BULLET].attr2 = ATTR2_ID8(OBJ_BULLET_LEFT); 
				m_bWidth = 8 ;
				m_bHeight = 3;
			break;
		case DOWN:
				ObjBuffer[BULLET].attr2 = ATTR2_ID8(OBJ_BULLET_DOWN);
				m_bWidth = 3 ;
				m_bHeight = 8;
			break;
		}
	}
	m_PrevKeys = currentKeys;
}
// Function for firing enemy's bullet
void Bullet::FireEnemyBullet(int start_x, int start_y, int projected_direction) { // fire bullet from enemy's location
	m_Active = true;   // setting bullet's state
	m_X = start_x + 5; // setting bullet's position in the middle of tank
	m_Y = start_y + 5; 
	m_Direction = projected_direction;	// give bullet it's m_Direction
	
	
	ObjBuffer[ENEMY_BULLET].attr0 = ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_REG; // show bullet
	SetObjectX(ENEMY_BULLET, m_X); // start drawing bullet from tank's position
	SetObjectY(ENEMY_BULLET, m_Y); // start drawing bullet from tank's position
	
	switch (m_Direction) { // switch direction of bullet's sprite
		case RIGHT:
			ObjBuffer[ENEMY_BULLET].attr2 = ATTR2_ID8(OBJ_BULLET_RIGHT);
			break;
		case UP:
			ObjBuffer[ENEMY_BULLET].attr2 = ATTR2_ID8(OBJ_BULLET_UP);	
			
			break;	
		case LEFT:
				ObjBuffer[ENEMY_BULLET].attr2 = ATTR2_ID8(OBJ_BULLET_LEFT); 
			break;
		case DOWN:
				ObjBuffer[ENEMY_BULLET].attr2 = ATTR2_ID8(OBJ_BULLET_DOWN);
			break;
	}			
}
// Function for updating player's bullet position
void Bullet::Update(const uint8_t map[MAP_WIDTH][MAP_HEIGHT]) {	
	// player's bullet position on map
	int tileX = m_X / SQUARESIZE;
	int tileY = m_Y / SQUARESIZE;
	
	
	if (map[tileX + 1][tileY] == EMPTY && m_Direction == RIGHT) {    // check if moving right is possible
		m_X += velocity;
		SetObjectX(BULLET, m_X);
	}
	else if (map[tileX][tileY - 1] == EMPTY && m_Direction == UP) {  // check if moving up is possible
		m_Y -= velocity;
		SetObjectY(BULLET, m_Y);
	}
	else if (map[tileX - 1][tileY] == EMPTY && m_Direction == LEFT) { // check if moving left is possible
		m_X -= velocity;
		SetObjectX(BULLET, m_X);
	}
	else if (map[tileX][tileY + 1] == EMPTY && m_Direction == DOWN) { // check if moving down is possible
		m_Y += velocity;
		SetObjectY(BULLET, m_Y);
	}
	else {
		// if not possible hide bullet
		ObjBuffer[BULLET].attr0 = ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_HIDE; 
		ObjBuffer[BULLET].attr1 = ATTR1_SIZE(1);
		// set hidden bullet in new place
		SetObjectX(BULLET, 0); 
		SetObjectY(BULLET, 0);
		// set bullet's tracking coordinates for 0 again.
		m_X = 0;
		m_Y = 0;
	}
}
// Function for updating enemy's bullet position
void Bullet::UpdateEnemyBullet(const uint8_t map[MAP_WIDTH][MAP_HEIGHT]) {	
    // enemy's bullet position on map
	int tileX = m_X / SQUARESIZE; 
	int tileY = m_Y / SQUARESIZE; 
	
	if (map[tileX + 1][tileY] == EMPTY && m_Direction == RIGHT) {    // check if moving right is possible
		m_X += velocity;
		SetObjectX(ENEMY_BULLET, m_X);
	}
	else if (map[tileX][tileY - 1] == EMPTY && m_Direction == UP) {  // check if moving up is possible
		m_Y -= velocity;
		SetObjectY(ENEMY_BULLET, m_Y);
	}
	else if (map[tileX - 1][tileY] == EMPTY && m_Direction == LEFT) { // check if moving up is possible
		m_X -= velocity;
		SetObjectX(ENEMY_BULLET, m_X);
	}
	else if (map[tileX][tileY + 1] == EMPTY && m_Direction == DOWN) { // check if moving down is possible
		m_Y += velocity;
		SetObjectY(ENEMY_BULLET, m_Y);
	}
	else {
		// if not possible hide bullet
		ObjBuffer[ENEMY_BULLET].attr0 = ATTR0_SHAPE(0) | ATTR0_8BPP | ATTR0_HIDE; 
		ObjBuffer[ENEMY_BULLET].attr1 = ATTR1_SIZE(1);
		m_Active = false;
		// set hidden bullet in the new place
		SetObjectX(ENEMY_BULLET, 0); 
		SetObjectY(ENEMY_BULLET, 0);
		// set bullet's tracking coordinates for 0 again.
		m_X = 0;
		m_Y = 0;
	}
}
// Hide bullet
void Bullet::Hide() {
	SetObjectX(BULLET, 0);
	SetObjectY(BULLET, 0);
	m_X = 0;
	m_Y = 0;
}