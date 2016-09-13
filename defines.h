// - Defines

// Define objects numbers
#define PLAYER			0	// object number player
#define ENEMY			1	// object number enemy
#define BULLET			2	// object number bullet
#define ENEMY_BULLET    3	// object number enemy bullet
#define SMALL_BOOM		4	// object number small boom
#define BIG_BOOM		5	// object number big boom

// Define tiles
#define WALL 1
#define EMPTY 0

// Define more tile numbers
#define OBJ_PLAYER_UP 0	    // player's position in sprite sheet
#define OBJ_PLAYER_RIGHT 2
#define OBJ_PLAYER_DOWN 4
#define OBJ_PLAYER_LEFT 6
#define OBJ_ENEMY_UP 32	    // enemy's position in sprite sheet
#define OBJ_ENEMY_RIGHT 34
#define OBJ_ENEMY_DOWN 36
#define OBJ_ENEMY_LEFT 38
#define OBJ_BULLET 8        // bullet's position in sprite sheet
#define OBJ_BULLET_UP 8	
#define OBJ_BULLET_RIGHT 10
#define OBJ_BULLET_DOWN 12 
#define OBJ_BULLET_LEFT 14
#define OBJ_EAGLE 108       // eagle's position in sprite sheet
#define OBJ_SMALL_BOOM 40   // explosion's position in sprite sheet
#define OBJ_BIG_BOOM 42

// Define directions
#define NONE		0
#define RIGHT		1
#define UP			2
#define LEFT		3
#define DOWN		4

// Define grid properties
#define MAP_WIDTH	30		// size of array used for storing the map
#define MAP_HEIGHT	20		// size of array used for storing the map
#define SQUARESIZE	8		// tile's size