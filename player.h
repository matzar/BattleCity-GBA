// - Player Class

#ifndef	PLAYER_H
#define	PLAYER_H

class Player {
public:
	//constructor prototype
	Player(int x = 0, int y = 0, int direction = NONE, uint16_t prevKeys = 0, int bDirection = UP, int rand_counter = 0,
           bool alive = true, int pWidth = 13, int pHeight = 13);

	int m_X;          //x coordinate of a player
	int m_Y;          //y coordinate of a player
	int m_bDirection; //direction a player is facing used for bullets direction
	bool m_Alive;     //player's status
	int m_pWidth;     //player's width
	int m_pHeight;    //player's height
	
	void Initialise(int start_x, int start_y);           //initialise a player
	void Move(const uint8_t map[MAP_WIDTH][MAP_HEIGHT]); //move a player		
	void Destroy();                                      //destroy a player
	
private:
	int m_Direction;      //direction player is facing
	uint16_t m_PrevKeys;  //variable used for a movement
	int m_RandCounter;    //variable used to seed the counter
	
	int GetTileAt(int x, int y, const uint8_t map[MAP_WIDTH][MAP_HEIGHT]);    //function used by Move() for collision detection
	bool CornersFree(int x, int y, const uint8_t map[MAP_WIDTH][MAP_HEIGHT]); //function used by Move() for collision detection
};


#endif