// - Player Class

#ifndef	ENEMY_H
#define	ENEMY_H

class Enemy {
public:
	// constructor prototype
	Enemy(int x = 0, int y = 0, int direction = NONE, bool alive = true, int bDirection = LEFT,
	      int eWidth = 13, int eHeight = 13);

	int m_X;				// x coordinate of the player
	int m_Y;				// y coordinate of the player
	int m_Direction;		// direction the player is facing
	bool m_Alive;			// enemy's state
	int m_bDirection = LEFT;// bullets directions for the enemy
	int m_eWidth;           // enemy's width
	int m_eHeight;          // enemy's height

	void Draw(const uint8_t map[MAP_WIDTH][MAP_HEIGHT]); // move the enemy
	void Destroy();                                      // destroy the enemy
	void Initialise(int start_x, int start_y);           // initialise the enemy at the start of a game


	int GetTileAt(int x, int y, const uint8_t map[MAP_WIDTH][MAP_HEIGHT]);    // function used by Draw() for collision detection
	bool CornersFree(int x, int y, const uint8_t map[MAP_WIDTH][MAP_HEIGHT]); // function used by Draw() for collision detection
};

#endif
