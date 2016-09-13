// - Player Class

#ifndef	BULLET_H
#define	BULLET_H

class Bullet {
public:
	// constructor prototype
	Bullet(int x = 0, int y = 0, int direction = NONE, bool active = true,
           int bWidth = 3, int bHeight = 8, int prevKeys = 0);

	int m_X;				// player's x 
	int m_Y;				// player's y 
	int m_Direction;		// direction player is facing
	bool m_Active;          // player's state
	int m_bWidth ;          // player's width
	int m_bHeight;          // player's height
	
	// Methods						
	void Initialise();                                                        // initialise bullet at the beginning of game
	void InitialiseEnemyBullet();                                             // initialise enemy at the beginning of game
	void Fire(int start_x, int start_y, int projected_direction);             // fires bullet
	void Update(const uint8_t map[MAP_WIDTH][MAP_HEIGHT]);	                  // updates position of bullet	
	void FireEnemyBullet(int start_x, int start_y, int projected_direction);  // fires enemy's bullet							
	void UpdateEnemyBullet(const uint8_t map[MAP_WIDTH][MAP_HEIGHT]);	      // updates enemy's bullet
	void Hide();                                                              // hides bullet

private:
	const int velocity = 4;		// speed at which bullet is moving
	int m_PrevKeys;
	
	int GetTileAt(int x, int y, const uint8_t map[MAP_WIDTH][MAP_HEIGHT]);    // function used by Move() for collision detection
	bool CornersFree(int x, int y, const uint8_t map[MAP_WIDTH][MAP_HEIGHT]); // function used by Move() for collision detection
};

#endif