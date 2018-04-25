int Pin_Data = 2;
int Pin_Latch = 4;
int Pin_Clock = 5;

int joyYPin = A5;
int joyXPin = A4;
int joyBPin = 8;

#define DEBUG 0

class Glyph
{
  public:
    const byte *pixels;
};

#define TOTAL_GLYPHS 37

// Font Definitions
const byte F00[] = {0x3c, 0x66, 0x6e, 0x7e, 0x76, 0x66, 0x3c, 0x00};
const byte F01[] = {0x18, 0x38, 0x78, 0x18, 0x18, 0x18, 0x18, 0x00};
const byte F02[] = {0x3c, 0x66, 0x06, 0x0c, 0x18, 0x30, 0x7e, 0x00};
const byte F03[] = {0x3c, 0x66, 0x06, 0x1c, 0x06, 0x66, 0x3c, 0x00};
const byte F04[] = {0x1c, 0x3c, 0x6c, 0xcc, 0xfe, 0x0c, 0x0c, 0x00};
const byte F05[] = {0x7e, 0x60, 0x7c, 0x06, 0x06, 0x66, 0x3c, 0x00};
const byte F06[] = {0x1c, 0x30, 0x60, 0x7c, 0x66, 0x66, 0x3c, 0x00};
const byte F07[] = {0x7e, 0x06, 0x06, 0x0c, 0x18, 0x18, 0x18, 0x00};
const byte F08[] = {0x3c, 0x66, 0x66, 0x3c, 0x66, 0x66, 0x3c, 0x00};
const byte F09[] = {0x3c, 0x66, 0x66, 0x3e, 0x06, 0x0c, 0x38, 0x00};

const byte F_A[] = {0x3c, 0x66, 0x66, 0x7e, 0x66, 0x66, 0x66, 0x00};
const byte F_B[] = {0x7c, 0x66, 0x66, 0x7c, 0x66, 0x66, 0x7c, 0x00};
const byte F_C[] = {0x1e, 0x30, 0x60, 0x60, 0x60, 0x30, 0x1e, 0x00};
const byte F_D[] = {0x78, 0x6c, 0x66, 0x66, 0x66, 0x6c, 0x78, 0x00};
const byte F_E[] = {0x7e, 0x60, 0x60, 0x78, 0x60, 0x60, 0x7e, 0x00};
const byte F_F[] = {0x7e, 0x60, 0x60, 0x7c, 0x60, 0x60, 0x60, 0x00};
const byte F_G[] = {0x3c, 0x66, 0x60, 0x6e, 0x66, 0x66, 0x3e, 0x00};
const byte F_H[] = {0x66, 0x66, 0x66, 0x7e, 0x66, 0x66, 0x66, 0x00};
const byte F_I[] = {0x3c, 0x18, 0x18, 0x18, 0x18, 0x18, 0x3c, 0x00};
const byte F_J[] = {0x06, 0x06, 0x06, 0x06, 0x06, 0x66, 0x3c, 0x00};
const byte F_K[] = {0xc6, 0xcc, 0xd8, 0xf0, 0xd8, 0xcc, 0xc6, 0x00};
const byte F_L[] = {0x60, 0x60, 0x60, 0x60, 0x60, 0x60, 0x7e, 0x00};
const byte F_M[] = {0xc6, 0xee, 0xfe, 0xd6, 0xc6, 0xc6, 0xc6, 0x00};
const byte F_N[] = {0xc6, 0xe6, 0xf6, 0xde, 0xce, 0xc6, 0xc6, 0x00};
const byte F_O[] = {0x3c, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3c, 0x00};
const byte F_P[] = {0x7c, 0x66, 0x66, 0x7c, 0x60, 0x60, 0x60, 0x00};
const byte F_Q[] = {0x78, 0xcc, 0xcc, 0xcc, 0xcc, 0xdc, 0x7e, 0x00};
const byte F_R[] = {0x7c, 0x66, 0x66, 0x7c, 0x6c, 0x66, 0x66, 0x00};
const byte F_S[] = {0x3c, 0x66, 0x70, 0x3c, 0x0e, 0x66, 0x3c, 0x00};
const byte F_T[] = {0x7e, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x00};
const byte F_U[] = {0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0x3c, 0x00};
const byte F_V[] = {0x66, 0x66, 0x66, 0x66, 0x3c, 0x3c, 0x18, 0x00};
const byte F_W[] = {0xc6, 0xc6, 0xc6, 0xd6, 0xfe, 0xee, 0xc6, 0x00};
const byte F_X[] = {0xc3, 0x66, 0x3c, 0x18, 0x3c, 0x66, 0xc3, 0x00};
const byte F_Y[] = {0xc3, 0x66, 0x3c, 0x18, 0x18, 0x18, 0x18, 0x00};
const byte F_Z[] = {0xfe, 0x0c, 0x18, 0x30, 0x60, 0xc0, 0xfe, 0x00};
const byte F__[] = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

Glyph font[TOTAL_GLYPHS];

class MazeCell
{
  public:
    byte flags;                         // Visited, OnStack, TopWall, LeftWall, RightWall, BottomWall
    byte nTop, nLeft, nRight, nBottom;  // Neighbors
    byte details;                       // RoomType (3), Variant (3), Rotation (2)
};

class Room
{
  public:
    const byte *walls;
};

#define PLAYER_HP 4
#define PLAYER_DEF 1
#define PLAYER_ATK 1

#define MAX_INVENTORY 8

class InventoryItem
{
  public:
    byte item;
    byte level;
};

class Player
{
  public:
    byte x;
    byte y;
    byte health;
    InventoryItem inventory[MAX_INVENTORY];
    byte HP;
    byte ATK;
    byte DEF;
};

#define MAX_MOBS 8

class Mob
{
  public:
    byte room;
    byte x;
    byte y;
    byte health;
};

#define MAX_CHESTS 8

class Chest
{
  public:
    byte room;
    byte x;
    byte y;
    byte item;
};

class Item
{
  public:
    const byte *image;
    byte type;
};

// Do Not Exceed 254 Cells
#define ROWS 4
#define COLS 4
#define EMPTY 255
#define CELL_COUNT ROWS * COLS

#define LOCKED   B10000000
#define HAS_EXIT B01000000
#define VISITED  B00100000
#define ONSTACK  B00010000
#define WTOP     B00001000
#define WLEFT    B00000100
#define WRIGHT   B00000010
#define WBOTTOM  B00000001

const byte R00[] = {0xe7, 0x81, 0x81, 0x81, 0x81, 0x81, 0x81, 0xff};
const byte R01[] = {0xe7, 0x81, 0xa5, 0x81, 0x81, 0xa5, 0x81, 0xff};
const byte R02[] = {0xe7, 0xc3, 0x81, 0x99, 0x99, 0x81, 0xc3, 0xff};
const byte R03[] = {0xe7, 0x81, 0x81, 0xc3, 0xc3, 0x81, 0x81, 0xff};
const byte R04[] = {0xe7, 0xe7, 0xe7, 0xc3, 0x81, 0x81, 0xc3, 0xff};

const byte R10[] = {0xff, 0x99, 0x99, 0x00, 0x00, 0x99, 0x99, 0xff};
const byte R11[] = {0xff, 0xff, 0xff, 0x00, 0x00, 0xff, 0xff, 0xff};
const byte R12[] = {0xff, 0xc3, 0x81, 0x18, 0x18, 0x81, 0xc3, 0xff};
const byte R13[] = {0xff, 0xc3, 0x81, 0x18, 0x3c, 0xff, 0xff, 0xff};
const byte R14[] = {0xff, 0x81, 0x81, 0x00, 0x00, 0x81, 0x81, 0xff};

const byte R20[] = {0xe7, 0xe7, 0xe7, 0xe0, 0xe0, 0xe7, 0xe7, 0xe7};
const byte R21[] = {0xe7, 0x81, 0xa5, 0x98, 0x98, 0xa5, 0x81, 0xe7};
const byte R22[] = {0xe7, 0xc7, 0x8f, 0x9c, 0x88, 0xc1, 0xe3, 0xe7};
const byte R23[] = {0xe7, 0x81, 0xa5, 0x80, 0x80, 0xa5, 0x81, 0xe7};
const byte R24[] = {0xe7, 0xe3, 0xf1, 0xf8, 0xf8, 0xf1, 0xe3, 0xe7};

const byte R30[] = {0xe7, 0xe7, 0xe7, 0x00, 0x00, 0xe7, 0xe7, 0xe7};
const byte R31[] = {0xe7, 0xc3, 0x81, 0x00, 0x00, 0x81, 0xc3, 0xe7};
const byte R32[] = {0xe7, 0x81, 0xb5, 0x04, 0x20, 0xad, 0x81, 0xe7};
const byte R33[] = {0xe7, 0xe3, 0xf1, 0x38, 0x18, 0x81, 0xc3, 0xe7};
const byte R34[] = {0xe7, 0xe1, 0xf1, 0x20, 0x04, 0x8f, 0x87, 0xe7};

const byte R40[] = {0xe7, 0xe7, 0xe7, 0xe0, 0xe0, 0xff, 0xff, 0xff};
const byte R41[] = {0xe7, 0xc7, 0xcf, 0x9c, 0x98, 0x81, 0xc7, 0xff};
const byte R42[] = {0xe7, 0xe3, 0xf1, 0xf8, 0xfc, 0xff, 0xff, 0xff};
const byte R43[] = {0xe7, 0x81, 0xa5, 0x80, 0x80, 0xa5, 0x81, 0xff};
const byte R44[] = {0xe7, 0x87, 0x8f, 0x9c, 0x98, 0x81, 0x81, 0xff};

MazeCell cells[CELL_COUNT];

Room rooms[5][5];
byte currentRoom[8];
byte activeRoom;

#define TOTAL_ITEMS 5

const byte I00[] = {0x1c, 0x14, 0x1c, 0x08, 0x08, 0x18, 0x08, 0x18}; // Key
const byte I01[] = {0x18, 0x3c, 0x7e, 0x42, 0x66, 0x66, 0x66, 0x00}; // Helm
const byte I02[] = {0x08, 0x28, 0x7c, 0x7c, 0x28, 0x08, 0x08, 0x08}; // Axe
const byte I03[] = {0x3c, 0x18, 0x18, 0x3c, 0x7e, 0x7e, 0x3c, 0x18}; // Potion
const byte I04[] = {0x00, 0x3c, 0x3c, 0x3c, 0x3c, 0x3c, 0x18, 0x00}; // Max HP

#define ITEM_TYPE_KEY           0
#define ITEM_TYPE_ARMOR         1
#define ITEM_TYPE_WEAPON        2
#define ITEM_TYPE_POTION_GREEN  3
#define ITEM_TYPE_MAX_HP        4

Item items[TOTAL_ITEMS];

Mob mobs[MAX_MOBS];
Chest chests[MAX_CHESTS];

#define MOVE_LEFT  B00000001
#define MOVE_RIGHT B00000010
#define MOVE_UP    B00000100
#define MOVE_DOWN  B00001000
#define JOY_BUTTON B00010000

Player player;
long lastMove = 0;

byte redScene[8];
byte blueScene[8];
byte greenScene[8];

byte exitedPosition;

int state;
byte joystick;
byte lastPlayerX;
byte lastPlayerY;
unsigned long lastButton = 0;
unsigned long lastScroll = 0;
unsigned long lastMobMove = 0;

byte activeMob;
unsigned long lastAttack = 0;

int lastStateBeforeInventory;
int stateAfterMessage;
byte currentItem = 0;

byte currentLevel = 0;

byte leftGlyph = 0;
byte rightGlyph = 0;
byte scrollPos = 0;
byte textPos = 0;
byte displayText[25];
bool displayTextRed;
bool displayTextBlue;
bool displayTextGreen;


#define MOB_MOVE_SPEED    400
#define MOB_ATK_ANIM      300
#define PLAYER_MOVE_SPEED 200
#define BUTTON_DELAY      400
#define SCROLL_SPEED      300
#define INV_EXIT_DELAY    200
#define MESSAGE_SPEED     50

#define STATE_DUNGEON             0
#define STATE_ENTERING_FIGHT      1
#define STATE_FIGHTING            2
#define STATE_EXITING_FIGHT       3
#define STATE_STARTING_HIT        4
#define STATE_HITTING             5
#define STATE_MOB_STARTING_ATTACK 6
#define STATE_MOB_ATTACKING       7
#define STATE_INVENTORY           8
#define STATE_EXITING_INVENTORY   9
#define STATE_SCROLLING_INVENTORY 10
#define STATE_MOB_MOVING          11
#define STATE_RESTART             13
#define STATE_DISPLAY_MESSAGE     14

void setup()
{
  Serial.begin(9600);

  // Fetch Random Seed
  randomSeed(analogRead(A0));

  pinMode(joyBPin, INPUT);
  pinMode(joyBPin,INPUT_PULLUP);

  pinMode(Pin_Data, OUTPUT);
  pinMode(Pin_Latch, OUTPUT);
  pinMode(Pin_Clock, OUTPUT);

  // Clear Screen
  clearScene();
  outputScene();
  
  // Should Only Be Done Once
  initFont();
  initRoomsAndItems();
  
  // Setup Intro
  setupIntroText();
}

void loop()
{
  switch (state) {
    case STATE_DISPLAY_MESSAGE:
      joystick = pollJoystick();

      if (joystick & JOY_BUTTON) {
        state = stateAfterMessage;
      }
      
      if (millis() - lastScroll > MESSAGE_SPEED) {
        scrollDisplayText();
        
        lastScroll = millis();
      }
      break;

    case STATE_RESTART:
      currentLevel = 0;
      
      initPlayer();
      generateLevel();
      break;
      
    case STATE_DUNGEON:
      // Setup Scene, Clear Player and Mobs
      for (byte x = 0; x < 8; x++) {
        blueScene[x] = currentRoom[x];
        redScene[x] = B00000000;
        greenScene[x] = B00000000;
      }

      // If Room Has Exit, Add the Door
      if (cells[activeRoom].flags & HAS_EXIT && cells[activeRoom].flags & LOCKED) {
        blueScene[3] |= B00000001;
        blueScene[4] |= B00000001;

        redScene[3] |= B00000001;
        redScene[4] |= B00000001;
      }
  
      // Display Mobs and Chests
      displayMobs();
      displayChests();

      joystick = pollJoystick();
      
      if (joystick & JOY_BUTTON) {
        // Switch to Inventory
        lastStateBeforeInventory = state;
        state = STATE_INVENTORY;
        lastButton = millis();
      } else {
        // Poll Joystick and Update Player Position
        if (exitedPosition == 0)
          exitedPosition = updatePlayerPosition();
    
        // If Player Exited Room, Handle It
        if (exitedPosition != 0) {
          changeRooms();
        } else {
          // Test for Chest Collision
          if (collideWithChest()) {
              lastStateBeforeInventory = state;
              state = STATE_INVENTORY;
              lastButton = millis();
          } else {
            // Test for Mob Collision
            if (collideWithMob()) {
              state = STATE_ENTERING_FIGHT;
            } else {
              if (activeMob != EMPTY && (player.x != lastPlayerX || player.y != lastPlayerY)) {
                byte mobX = mobs[activeMob].x;
                byte mobY = mobs[activeMob].y;
                
                moveActiveMob();
                
                if (mobX != mobs[activeMob].x || mobY != mobs[activeMob].y) {
                  state = STATE_MOB_MOVING;
                  lastMobMove = millis(); 
                }
              }          
            }
          }
        }
      }
      break;
      
    case STATE_MOB_MOVING:
      if (millis() - lastMobMove > MOB_MOVE_SPEED) {
        if (collideWithMob()) {
          state = STATE_ENTERING_FIGHT;
        } else {
          state = STATE_DUNGEON;  
        }
      }
      break;
      
    case STATE_ENTERING_FIGHT:
      joystick = pollJoystick();
      if (!joystick)
        state = STATE_FIGHTING;
      break;

    case STATE_INVENTORY:
      displayInventoryItem();

      if (millis() - lastButton > BUTTON_DELAY) {
        joystick = pollJoystick();
    
        if (joystick & JOY_BUTTON) {
          // Use Inventory Item
          useInventoryItem();
          
          state = STATE_EXITING_INVENTORY;    
          lastButton = millis();
        } else {
          if (joystick & MOVE_UP || joystick & MOVE_DOWN) {
            state = STATE_EXITING_INVENTORY;
            lastButton = millis();
          } else {
            if (joystick & MOVE_RIGHT) {
              currentItem++;
              if (currentItem >= MAX_INVENTORY || player.inventory[currentItem].item == EMPTY)
                currentItem = 0;
              state = STATE_SCROLLING_INVENTORY;
              lastScroll = millis();
            } else {
              if (joystick & MOVE_LEFT) {
                if (currentItem == 0) {
                  currentItem = MAX_INVENTORY - 1;
                  while (player.inventory[currentItem].item == EMPTY && currentItem != 0) {
                    currentItem--;
                  }
                }
                else
                  currentItem--;
                state = STATE_SCROLLING_INVENTORY;
                lastScroll = millis();
              }
            }
          }
        }
      }
      break;

    case STATE_SCROLLING_INVENTORY:
      if (millis() - lastScroll > SCROLL_SPEED) {
        state = STATE_INVENTORY;
      }    
      break;
      
    case STATE_EXITING_INVENTORY:
      if (millis() - lastButton > INV_EXIT_DELAY) {
        state = lastStateBeforeInventory;    
      }    
      break;
      
    case STATE_FIGHTING:
      displayFightScene();

      joystick = pollJoystick();
      
      if (joystick & JOY_BUTTON) {
          lastStateBeforeInventory = state;
          state = STATE_INVENTORY;
          lastButton = millis();
      } else {
        if (joystick & MOVE_LEFT)
          state = STATE_EXITING_FIGHT;
        else
        if (joystick & MOVE_RIGHT)
          state = STATE_STARTING_HIT;
      }
      break;
      
    case STATE_STARTING_HIT:
      displayFightScene(); 
      
      joystick = pollJoystick();
      if (!(joystick & MOVE_RIGHT)) {
        state = STATE_HITTING;
      }
      break;
      
    case STATE_HITTING:
      fight(false);

      if (mobs[activeMob].health == 0) {
        activeMob = EMPTY;
        state = STATE_EXITING_FIGHT;
      } else {
        state = STATE_MOB_STARTING_ATTACK;
        lastAttack = millis();
      }
      break;      

    case STATE_MOB_STARTING_ATTACK:
      displayFightScene(); 
      
      if (millis() - lastAttack > MOB_ATK_ANIM) {
        state = STATE_MOB_ATTACKING;
      }
      break;

    case STATE_MOB_ATTACKING:
      fight(true);

      if (player.health == 0) {
        setupGameOverText();
      }
      else
        state = STATE_FIGHTING;
      break;
      
    case STATE_EXITING_FIGHT:
      joystick = pollJoystick();
      
      if (!(joystick & MOVE_LEFT)) {
        state = STATE_DUNGEON;

        // Put Player Position Back to Pre-Fight Location
        player.x = lastPlayerX;
        player.y = lastPlayerY;
      }
      break;
  }

  // Output Scene
  outputScene();
}

void loadDisplayText(const char *textToDisplay, bool red, bool green, bool blue) {
  byte textLength = strlen(textToDisplay);
  
  for (byte x = 0; x < textLength; x++) {
    if (textToDisplay[x] == 32)
      displayText[x] = 36;
    else {
      if (textToDisplay[x] < 58)
        displayText[x] = textToDisplay[x] - 48;
      else
        displayText[x] = textToDisplay[x] - 55;
    }
  }
  displayText[textLength] = 0xff;

  displayTextRed = red;
  displayTextBlue = blue;
  displayTextGreen = green;

  scrollPos = 0;
  textPos = 0;

  state = STATE_DISPLAY_MESSAGE;
  lastScroll = millis();
}

void setupIntroText() {
  loadDisplayText("DUNGEON CRAWL\0", false, false, true);

  stateAfterMessage = STATE_RESTART;
}

void setupGameOverText() {
  loadDisplayText("GAME OVER ON LEVEL \0", true, false, false);
  
  byte d1, d2, d3;
  byte value = currentLevel + 1;
  if (value > 9) {
    d1 = value / 10;
    d2 = value % 10;
    d3 = 0xff;
  } else {
    d1 = value;
    d2 = 0xff;
    d3 = 0xff;
  }
  
  displayText[19] = d1;
  displayText[20] = d2;
  displayText[21] = d3;
  
  stateAfterMessage = STATE_RESTART;
}

void scrollDisplayText() {
  clearScene();

  if (displayText[textPos] == 0xff) {
      scrollPos = 0;
      textPos = 0;
  }
      
  leftGlyph = displayText[textPos];
  rightGlyph = displayText[textPos + 1];
      
  for (byte x = 0; x < 8; x++) {
    byte *lp = font[leftGlyph].pixels + x;
    byte *rp = font[rightGlyph].pixels + x;
  
    if (scrollPos <= 7) {
      if (displayTextRed)
        redScene[x] = *lp >> (7-scrollPos);
      if (displayTextBlue)
        blueScene[x] = *lp >> (7-scrollPos);
      if (displayTextGreen)
        greenScene[x] = *lp >> (7-scrollPos);                
    } else {
      if (displayTextRed)
        redScene[x] = *lp << (scrollPos-7);
      if (displayTextBlue)
        blueScene[x] = *lp << (scrollPos-7);
      if (displayTextGreen)
        greenScene[x] = *lp << (scrollPos-7);
                      
      if (rightGlyph != 0xff) {
        if (displayTextRed)
          redScene[x] |= *rp >> (15-scrollPos);
        if (displayTextBlue)
          blueScene[x] |= *rp >> (15-scrollPos);
        if (displayTextGreen)
          greenScene[x] |= *rp >> (15-scrollPos);                    
      }
    }
  }
  
  scrollPos++;
  if (scrollPos > 15) {
    scrollPos = 8;
    textPos ++;
  }
}

void generateLevel() {
  // Clear Scene
  clearScene();
  outputScene();
  
  // Regenerate Maze and Mobs
  createMaze();
  createMobs();
  createChests();

  // Start in Upper Left Corner
  activeRoom = 0;

  // Setup Room
  setupRoom();
  
  // Set Player Start Position in Room
  initPlayerPosition();
  
  // Animate Transition
  animateTransition(10);

  // Start in Dungeon State
  state = STATE_DUNGEON;

  if (DEBUG)
    debugPrintMaze();
}

void useInventoryItem() {
  bool consume = false;
  
  switch (items[player.inventory[currentItem].item].type) {
    case ITEM_TYPE_KEY:
      if (cells[activeRoom].flags & HAS_EXIT) {
        cells[activeRoom].flags &= ~LOCKED;
        consume = true;
      }    
      break;
    case ITEM_TYPE_POTION_GREEN:
      // Restore All Health to Max HP
      player.health = player.HP;
      consume = true;
      break;            
  }

  if (consume) {
    if (player.inventory[currentItem].level == 1) {
      // Remove Item from Inventory
      for (byte x = currentItem; x < MAX_INVENTORY; x++) {
        if (x != MAX_INVENTORY - 1) {    
          player.inventory[x].item = player.inventory[x + 1].item;
          player.inventory[x].level = player.inventory[x + 1].level;
        } else {
          player.inventory[x].item = EMPTY;
          player.inventory[x].level = 0;
        }
      }
  
      // Reset Current Item
      currentItem = 0;        
    } else {
      // Reduce Qty
      player.inventory[currentItem].level--;
    }
  }
  
}

void moveActiveMob() {
  byte hitWall;
  byte locX = mobs[activeMob].x;
  byte locY = mobs[activeMob].y;
  bool moved = false;
    
  // Try to Move Left
  if (player.x < locX && moved == false) {
      hitWall = currentRoom[locY] & (1 << (7 - locX + 1));
      if (hitWall == 0) {
        locX--;
        moved = true;
      }
  }

  // Try to Move Right
  if (player.x > locX && moved == false) {
      hitWall = currentRoom[locY] & (1 << (7 - locX - 1));
      if (hitWall == 0) {
        locX++;
        moved = true;
      }
  }

  // Try to Move Up
  if (player.y < locY && moved == false) {
      hitWall = currentRoom[(locY - 1)] & (1 << (7 - locX));
      if (hitWall == 0) {
        locY--;
        moved = true;
      }
  }

  // Try to Move Down
  if (player.y > locY && moved == false) {
      hitWall = currentRoom[(locY + 1)] & (1 << (7 - locX));
      if (hitWall == 0) {
        locY++;
        moved = true;
      }
  }

  if (moved) {
    mobs[activeMob].x = locX;
    mobs[activeMob].y = locY;
  }
}

void clearScene() {
  // Clear Scene
  for (byte x = 0; x < 8; x++) {
    blueScene[x] = B00000000;
    redScene[x] = B00000000;
    greenScene[x] = B00000000;
  }
}

void displayHorizontalValue(byte value, byte row, bool red, bool green, bool blue, bool reversed) {
  byte tRow = row;
  
  if (reversed) {
    tRow++;
  }
  
  byte dots = min(value, 8);
  for (byte x = 0; x < dots; x++) {
    if (reversed) {
      if (red)
        redScene[tRow] |= (1 << x);
      if (green)
        greenScene[tRow] |= (1 << x);
      if (blue)
        blueScene[tRow] |= (1 << x);      
    } else {
      if (red)
        redScene[tRow] |= (1 << (7 - x));
      if (green)
        greenScene[tRow] |= (1 << (7 - x));
      if (blue)
        blueScene[tRow] |= (1 << (7 - x));
    }
  }
  
  if (reversed)
    tRow -= 2;
    
  if (value > 8) {
    dots = value - 8;
    for (byte x = 0; x < dots; x++) {
      if (reversed) {
        if (red)
          redScene[tRow + 1] |= (1 << x);
        if (green)
          greenScene[tRow + 1] |= (1 << x);
        if (blue)
          blueScene[tRow + 1] |= (1 << x);
      } else {
        if (red)
          redScene[tRow + 1] |= (1 << (7 - x));
        if (green)
          greenScene[tRow + 1] |= (1 << (7 - x));
        if (blue)
          blueScene[tRow + 1] |= (1 << (7 - x));
      }
    }  
  }  
}

void displayInventoryItem() {
  clearScene();

  if (currentItem == 0) {
    // Display Player's Health
    displayHorizontalValue(player.health, 0, false, true, false, false);

    // Display Player's ATK
    displayHorizontalValue(player.ATK, 2, true, false, false, false);

    // Display Player's DEF
    displayHorizontalValue(player.DEF, 4, false, false, true, false);    

    // Display Maze Level
    displayHorizontalValue(currentLevel + 1, 6, false, true, true, false);       
  } else {
    if (player.inventory[currentItem].item != EMPTY) {
      for (byte x = 0; x < 8; x++) {
        byte *image = items[player.inventory[currentItem].item].image + x;
        
        switch (items[player.inventory[currentItem].item].type) {
          case ITEM_TYPE_WEAPON:
            redScene[x] = *image;
            break;
          case ITEM_TYPE_ARMOR:
            blueScene[x] = *image;
            break;
          case ITEM_TYPE_POTION_GREEN:
          case ITEM_TYPE_MAX_HP:
            greenScene[x] = *image;
            break;            
          case ITEM_TYPE_KEY: // Pink
            redScene[x] = *image;
            blueScene[x] = *image;
            break;     
        }
      } 

      // Display Item's Level/Qty (Vertically)
      if (items[player.inventory[currentItem].item].type != ITEM_TYPE_KEY) {
        byte dots = min(player.inventory[currentItem].level, 8);
        
        for (byte x = 0; x < dots; x++) {
          greenScene[x] |= (1 << 7);
        }
        
        if (player.inventory[currentItem].level > 8) {
          dots = player.inventory[currentItem].level - 8;
          for (byte x = 0; x < dots; x++) {
            greenScene[x] |= (1 << 0);
          }  
        }
      }
    }
  }
}

void displayFightScene() {
  clearScene();

  // Player Health
  displayHorizontalValue(player.health, 0, false, true, false, false);
  
  // Player / Mob Bodies
  greenScene[3] = B01100000;
  greenScene[4] = B01100000;
  redScene[3] = B00000110;
  redScene[4] = B00000110;

  // Mob Health
  displayHorizontalValue(mobs[activeMob].health, 6, true, false, false, true);
  
  // Animate Player Hitting
  if (state == STATE_STARTING_HIT)
    greenScene[3] |= B00011000;

  // Animate Mob Hitting
  if (state == STATE_MOB_STARTING_ATTACK)
    redScene[4] |= B00011000;    
}

void animateTransition(byte delay) {
  unsigned long last_animate = 0;
  
  for (byte y = 0; y < 8; y++) {
    for (byte x = 0; x < 8; x++) {
      if (y % 2 == 0) {
        redScene[y] |= (1 << (7-x));
        blueScene[y] |= (1 << (7-x));
      } else {
        redScene[y] |= (1 << x);
        blueScene[y] |= (1 << x);  
      }

      last_animate = millis();
      while (millis() - last_animate < delay) {
        outputScene();
      }
    }  
  }
}

bool collideWithChest() {
  bool result = false;
  
  for (byte x = 0; x < MAX_CHESTS; x++) {
    if (chests[x].room == activeRoom && (7-player.x) == chests[x].x && player.y == chests[x].y && chests[x].item != EMPTY) {
      byte matched = EMPTY;
      byte lastItem = EMPTY;

      // Search Player's Inventory for a Match
      for (byte y = 0; y < MAX_INVENTORY; y++) {
        if (player.inventory[y].item != EMPTY) {
          if (chests[x].item == player.inventory[y].item) {
            // Increment Level
            player.inventory[y].level++;

            // Level Cap at 16
            player.inventory[y].level = min(player.inventory[y].level, 16);
              
            matched = y;
          }

          lastItem = y;
        }
      }

      switch (items[chests[x].item].type) {
        case ITEM_TYPE_WEAPON:
          player.ATK++;
          player.ATK = min(player.ATK, 16);
          break;
        case ITEM_TYPE_ARMOR:
          player.DEF++;
          player.DEF = min(player.DEF, 16);
          break;
        case ITEM_TYPE_MAX_HP:
          player.HP++;
          player.HP = min(player.HP, 16);
          player.health = player.HP;
          player.inventory[1].level = player.HP;      
          break;
      }

      if (lastItem == EMPTY)
        lastItem = 0;
        
      if (matched == EMPTY) {
        // Pick Next Slot
        lastItem++;
      } else {
        // Set Focus to Matched Slot
        currentItem = matched;  
      }

      // No Matches, Add to End of List (if room)
      if (matched == EMPTY && lastItem < MAX_INVENTORY) {
        player.inventory[lastItem].item = chests[x].item;
        player.inventory[lastItem].level = 1;

        // Set Focus to Last Slot
        currentItem = lastItem;
      }

      // Remove From Chest
      chests[x].item = EMPTY;
      result = true;
      break;
    }
  }

  return result;
}

void fight(bool mobAttacking) {
  byte damage = 1;
  
  if (mobAttacking) {
    if (damage > player.health)
      player.health = 0;
    else
      player.health -= damage;
  } else {
    if (damage > mobs[activeMob].health)
      mobs[activeMob].health = 0;
    else
      mobs[activeMob].health -= damage;
  }
}

bool collideWithMob() {
  bool result = false;
  activeMob = EMPTY;
  
  for (byte x = 0; x < MAX_MOBS; x++) {
    if (mobs[x].room == activeRoom && mobs[x].health > 0) {
      activeMob = x;
    
      if (player.x == mobs[x].x && player.y == mobs[x].y) {
        result = true;
        break;
      }
    }
  }

  return result;
}

void createMobs() {
  byte room;

  bool badPlacement;
  for (byte x = 0; x < MAX_MOBS; x++) {
    bool foundRoom = true;
    do  {
      // Pick a Random Room
      room = random(CELL_COUNT);

      // Look for Mob Already in Chosen Room
      foundRoom = true;
      for (byte y = 0; y < MAX_MOBS; y++) {
        if (x != y && mobs[y].room == room) {
          foundRoom = false;
          break;
        }
      }
      badPlacement = (foundRoom == false || room == 0);
    } while (badPlacement);

    // Assign Chosen Room
    mobs[x].room = room;

    // Assign Health
    mobs[x].health = random(1, currentLevel + 3);
    mobs[x].health = min(mobs[x].health, 16);
    
    // Place Mob
    initMobPosition(x);
  }
}

void createChests() {
  bool keyPlaced = false;
  
  for (byte x = 0; x < MAX_CHESTS; x++) {
    bool hitChest;
    bool hitWall;
    
    // Pick a Random Room
    byte r = random(CELL_COUNT);
    
    byte room = cells[r].details >> 5;
    byte variant = cells[r].details >> 2 & B00000111;
    byte rotation = cells[r].details & B00000011;
    
    memcpy(currentRoom, rooms[room][variant].walls, 8);
    
    // Rotate Room
    rotateCurrentRoom(rotation);    

    byte locX = 0;
    byte locY = 0;
    bool badChest;
    do  {
      locX = random(1, 7);
      locY = random(1, 7);
     
      hitWall = currentRoom[locY] & (1 << locX);
       
      if (hitWall == 0) {
        hitChest = false;
        
        for (byte y = 0; y < MAX_CHESTS; y++) {
          if (x != y && chests[y].x == locX && chests[y].y == locY && chests[y].room == r) {
            hitChest = true;
            break;
          }
        }

      }

      badChest = (hitWall || hitChest);
    } while (badChest);

    // Place Key in First Chest
    if (keyPlaced == false) {
      chests[x].item = 0;
      keyPlaced = true;
    } else {
      // Random Items After That
      chests[x].item = random(1, TOTAL_ITEMS);
    }
    
    // Assign Chosen Room, Location
    chests[x].x = locX;
    chests[x].y = locY;
    chests[x].room = r;
  }
}

void displayChests() {
  for (byte x = 0; x < MAX_CHESTS; x++) {
    if (chests[x].room == activeRoom && chests[x].item != EMPTY) {
      redScene[chests[x].y] |= (1 << (chests[x].x));
      greenScene[chests[x].y] |= (1 << (chests[x].x));
    }
  }
}


void displayMobs() {
  for (byte x = 0; x < MAX_MOBS; x++) {
    if (mobs[x].room == activeRoom && mobs[x].health > 0) {
      redScene[mobs[x].y] |= (1 << (7-mobs[x].x));
    }
  }
}

void changeRooms() {
  bool gameOver = false;
  
  // Left
  if (exitedPosition == 4) {
    activeRoom--;

    player.x = 7 - player.x;
  }
  
  // Right
  if (exitedPosition == 2) {
    // Test if Exiting Level
    if (cells[activeRoom].flags & HAS_EXIT) {
      // Move to Next Level
      currentLevel++;

      if (currentLevel < 17) 
        // Generate It
        generateLevel();
      else {
        gameOver = true;
        setupGameOverText();
      }
    } else {
      activeRoom++;

      player.x = 7 - player.x;
    }
  }
  
  // Top  
  if (exitedPosition == 1) {
    activeRoom -= COLS;
    
    player.y = 7 - player.y;
  }
  
  // Bottom
  if (exitedPosition == 3) {
    activeRoom += COLS;

    player.y = 7 - player.y;
  }

  if (!gameOver)
    // Setup Room
    setupRoom();
}

void setupRoom() {
  byte room = cells[activeRoom].details >> 5;
  byte variant = cells[activeRoom].details >> 2 & B00000111;
  byte rotation = cells[activeRoom].details & B00000011;

  // Copy to Current Room
  memcpy(currentRoom, rooms[room][variant].walls, 8);

  // Rotate Room
  rotateCurrentRoom(rotation);  

  // Reset Exited Position
  exitedPosition = 0;
}

void initPlayer() {
  player.health = PLAYER_HP;
  player.HP = PLAYER_HP;
  player.DEF = PLAYER_DEF;
  player.ATK = PLAYER_ATK;

  for (byte x = 0; x < MAX_INVENTORY; x++) {
    player.inventory[x].item = EMPTY;
    player.inventory[x].level = 0;
  }

  player.inventory[1].item = ITEM_TYPE_MAX_HP;
  player.inventory[1].level = player.HP;

  currentItem = 0;
}

void initPlayerPosition() {
  player.x = EMPTY;
  player.y = EMPTY;
  
  for (byte y = 1; y < 7; y++) {
    // Search for Open Row (Top/Down)
    if (currentRoom[y] != B11111111) {
      // Set Player Row
      player.y = y; 

      // Search for Open Column
      for (byte x = 1; x < 7; x++) {
        byte hitWall = currentRoom[player.y] & (1 << x);

        if (hitWall == 0) {
          player.x = 7 - x;
          break;
        }
      }

      if (player.x < EMPTY)
        break;
    }
  }

  lastPlayerX = player.x;
  lastPlayerY = player.y;
}

void initMobPosition(byte mob) {
  byte room = cells[mobs[mob].room].details >> 5;
  byte variant = cells[mobs[mob].room].details >> 2 & B00000111;
  byte rotation = cells[mobs[mob].room].details & B00000011;

  memcpy(currentRoom, rooms[room][variant].walls, 8);

  // Rotate Room
  rotateCurrentRoom(rotation);  

  byte x = 0;
  byte y = 0;
  bool hitWall = true;
  do {
    y = random(1, 7);
    x = random(1, 7);
    
    hitWall = currentRoom[y] & (1 << x);
  } while (hitWall == true);

  mobs[mob].x = 7 - x;
  mobs[mob].y = y;
}

void outputScene() {
  for (byte x = 0; x < 8; x++) {
    byte row = x;
    byte red = redScene[row];
    byte blue = blueScene[row];
    byte green = greenScene[row];
        
    // Disable Output
    digitalWrite(Pin_Latch, LOW);
    
    shiftOut(Pin_Data, Pin_Clock, LSBFIRST, ~(1 << (7-row)));
    shiftOut(Pin_Data, Pin_Clock, LSBFIRST, ~green);
    shiftOut(Pin_Data, Pin_Clock, LSBFIRST, ~blue);
    shiftOut(Pin_Data, Pin_Clock, LSBFIRST, ~red);
  
    // Latch Output
    digitalWrite(Pin_Latch, HIGH);
  }
}

byte pollJoystick() {
    int joyX = analogRead(joyXPin); 
    int joyY = analogRead(joyYPin);
    bool joyB = digitalRead(joyBPin);

    byte results = 0;
    
    if (joyX < 200) {
      results |= MOVE_LEFT;
    }
    
    if (joyX > 824) {
      results |= MOVE_RIGHT;
    }

    if (joyY < 200) {
      results |= MOVE_UP;
    }
    
    if (joyY > 824) {
      results |= MOVE_DOWN;
    }

    if (!joyB)
      results |= JOY_BUTTON;

    return results;
}

byte updatePlayerPosition() {
  byte result = 0;

  lastPlayerX = player.x;
  lastPlayerY = player.y;
  
  if (millis() - lastMove > PLAYER_MOVE_SPEED) {
    byte joystick = pollJoystick();
    
    if (joystick & MOVE_LEFT || joystick & MOVE_RIGHT || joystick & MOVE_UP || joystick & MOVE_DOWN) {
      
      byte hitWall = 0;
  
      if (joystick & MOVE_LEFT) {
        if (player.x > 0) {
          hitWall = blueScene[player.y] & (1 << (7 - player.x + 1));
          
          if (hitWall == 0)
            player.x--;
        } else {
          if (player.x == 0)
            result = 4;
        }
      } else {
        if (joystick & MOVE_RIGHT) {
          if (player.x < 7) {
            hitWall = blueScene[player.y] & (1 << (7 - player.x - 1));

            if (hitWall == 0)
              player.x++;
          } else {
            if (player.x == 7)
              result = 2;
          }
        } else {
          if (joystick & MOVE_UP) {
            if (player.y > 0) {
              hitWall = blueScene[player.y - 1] & (1 << (7 - player.x));
              
              if (hitWall == 0)
                player.y--;
            } else {
              if (player.y == 0)
                result = 1;
            }
          } else {
            if (joystick & MOVE_DOWN) {
              if (player.y < 7) {
                hitWall = blueScene[player.y + 1] & (1 << (7 - player.x));

                if (hitWall == 0)
                  player.y++;
              } else {
                if (player.y == 7)
                  result = 3;
              }
            }
          }
        }
      }
    }
    
    lastMove = millis();
  }

  // Add Player to Room
  greenScene[player.y] |= (1 << (7-player.x));

  return result;
}

void rotateCurrentRoom(byte rotation) {
  if (rotation == 0) return;
  
  byte temp[8];
  for (byte x = 0; x < rotation; x++) {
    temp[0] = (currentRoom[7] & B10000000) >> 0 | (currentRoom[6] & B10000000) >> 1 | (currentRoom[5] & B10000000) >> 2 | (currentRoom[4] & B10000000) >> 3 | (currentRoom[3] & B10000000) >> 4 | (currentRoom[2] & B10000000) >> 5 | (currentRoom[1] & B10000000) >> 6 | (currentRoom[0] & B10000000) >> 7;
    temp[1] = (currentRoom[7] & B01000000) << 1 | (currentRoom[6] & B01000000) >> 0 | (currentRoom[5] & B01000000) >> 1 | (currentRoom[4] & B01000000) >> 2 | (currentRoom[3] & B01000000) >> 3 | (currentRoom[2] & B01000000) >> 4 | (currentRoom[1] & B01000000) >> 5 | (currentRoom[0] & B01000000) >> 6;
    temp[2] = (currentRoom[7] & B00100000) << 2 | (currentRoom[6] & B00100000) << 1 | (currentRoom[5] & B00100000) >> 0 | (currentRoom[4] & B00100000) >> 1 | (currentRoom[3] & B00100000) >> 2 | (currentRoom[2] & B00100000) >> 3 | (currentRoom[1] & B00100000) >> 4 | (currentRoom[0] & B00100000) >> 5;
    temp[3] = (currentRoom[7] & B00010000) << 3 | (currentRoom[6] & B00010000) << 2 | (currentRoom[5] & B00010000) << 1 | (currentRoom[4] & B00010000) >> 0 | (currentRoom[3] & B00010000) >> 1 | (currentRoom[2] & B00010000) >> 2 | (currentRoom[1] & B00010000) >> 3 | (currentRoom[0] & B00010000) >> 4;
    temp[4] = (currentRoom[7] & B00001000) << 4 | (currentRoom[6] & B00001000) << 3 | (currentRoom[5] & B00001000) << 2 | (currentRoom[4] & B00001000) << 1 | (currentRoom[3] & B00001000) >> 0 | (currentRoom[2] & B00001000) >> 1 | (currentRoom[1] & B00001000) >> 2 | (currentRoom[0] & B00001000) >> 3;
    temp[5] = (currentRoom[7] & B00000100) << 5 | (currentRoom[6] & B00000100) << 4 | (currentRoom[5] & B00000100) << 3 | (currentRoom[4] & B00000100) << 2 | (currentRoom[3] & B00000100) << 1 | (currentRoom[2] & B00000100) >> 0 | (currentRoom[1] & B00000100) >> 1 | (currentRoom[0] & B00000100) >> 2;
    temp[6] = (currentRoom[7] & B00000010) << 6 | (currentRoom[6] & B00000010) << 5 | (currentRoom[5] & B00000010) << 4 | (currentRoom[4] & B00000010) << 3 | (currentRoom[3] & B00000010) << 2 | (currentRoom[2] & B00000010) << 1 | (currentRoom[1] & B00000010) >> 0 | (currentRoom[0] & B00000010) >> 1;
    temp[7] = (currentRoom[7] & B00000001) << 7 | (currentRoom[6] & B00000001) << 6 | (currentRoom[5] & B00000001) << 5 | (currentRoom[4] & B00000001) << 4 | (currentRoom[3] & B00000001) << 3 | (currentRoom[2] & B00000001) << 2 | (currentRoom[1] & B00000001) << 1 | (currentRoom[0] & B00000001) >> 0;

    memcpy(currentRoom, temp, 8);
  }
}

void initFont() {
  font[0].pixels = &F00[0];
  font[1].pixels = &F01[0];
  font[2].pixels = &F02[0];
  font[3].pixels = &F03[0];
  font[4].pixels = &F04[0];
  font[5].pixels = &F05[0];
  font[6].pixels = &F06[0];
  font[7].pixels = &F07[0];
  font[8].pixels = &F08[0];
  font[9].pixels = &F09[0];

  font[10].pixels = &F_A[0];
  font[11].pixels = &F_B[0];
  font[12].pixels = &F_C[0];
  font[13].pixels = &F_D[0];
  font[14].pixels = &F_E[0];
  font[15].pixels = &F_F[0];
  font[16].pixels = &F_G[0];
  font[17].pixels = &F_H[0];
  font[18].pixels = &F_I[0];
  font[19].pixels = &F_J[0];
  font[20].pixels = &F_K[0];
  font[21].pixels = &F_L[0];
  font[22].pixels = &F_M[0];
  font[23].pixels = &F_N[0];
  font[24].pixels = &F_O[0];
  font[25].pixels = &F_P[0];
  font[26].pixels = &F_Q[0];
  font[27].pixels = &F_R[0];
  font[28].pixels = &F_S[0];
  font[29].pixels = &F_T[0];
  font[30].pixels = &F_U[0];
  font[31].pixels = &F_V[0];
  font[32].pixels = &F_W[0];
  font[33].pixels = &F_X[0];
  font[34].pixels = &F_Y[0];
  font[35].pixels = &F_Z[0];
  font[36].pixels = &F__[0];
}

void initRoomsAndItems() {
  // One Doorway
  rooms[0][0].walls = &R00[0];
  rooms[0][1].walls = &R01[0];
  rooms[0][2].walls = &R02[0];
  rooms[0][3].walls = &R03[0];
  rooms[0][4].walls = &R04[0];

  rooms[1][0].walls = &R10[0];
  rooms[1][1].walls = &R11[0];
  rooms[1][2].walls = &R12[0];
  rooms[1][3].walls = &R13[0];
  rooms[1][4].walls = &R14[0];

  rooms[2][0].walls = &R20[0];
  rooms[2][1].walls = &R21[0];
  rooms[2][2].walls = &R22[0];
  rooms[2][3].walls = &R23[0];
  rooms[2][4].walls = &R24[0];

  rooms[3][0].walls = &R30[0];
  rooms[3][1].walls = &R31[0];
  rooms[3][2].walls = &R32[0];
  rooms[3][3].walls = &R33[0];
  rooms[3][4].walls = &R34[0];

  rooms[4][0].walls = &R40[0];
  rooms[4][1].walls = &R41[0];
  rooms[4][2].walls = &R42[0];
  rooms[4][3].walls = &R43[0];
  rooms[4][4].walls = &R44[0];

  // Key Must Be in Position Zero
  items[0].image = &I00[0];
  items[0].type = ITEM_TYPE_KEY;

  items[1].image = &I01[0];
  items[1].type = ITEM_TYPE_ARMOR; 

  items[2].image = &I02[0];
  items[2].type = ITEM_TYPE_WEAPON; 

  items[3].image = &I03[0];
  items[3].type = ITEM_TYPE_POTION_GREEN;

  items[4].image = &I04[0];
  items[4].type = ITEM_TYPE_MAX_HP;
}

byte chooseUnvisitedNeighbor(byte currentCell) {
  byte choices[4];
  byte found = 0;

  // If Unvisited Top Neighbor, Add to Choices
  if (cells[currentCell].nTop != EMPTY) {
    if (!(cells[cells[currentCell].nTop].flags & VISITED))
      choices[found++] = cells[currentCell].nTop;
  }

  // If Unvisited Left Neighbor, Add to Choices
  if (cells[currentCell].nLeft != EMPTY) {
    if (!(cells[cells[currentCell].nLeft].flags & VISITED))
      choices[found++] = cells[currentCell].nLeft;
  }

  // If Unvisited Right Neighbor, Add to Choices
  if (cells[currentCell].nRight != EMPTY) {
    if (!(cells[cells[currentCell].nRight].flags & VISITED))
      choices[found++] = cells[currentCell].nRight;
  }

  // If Unvisited Bottom Neighbor, Add to Choices
  if (cells[currentCell].nBottom != EMPTY) {
    if (!(cells[cells[currentCell].nBottom].flags & VISITED))
      choices[found++] = cells[currentCell].nBottom;
  }

  // If No Unvisited Neighbors, Exit
  if (found == 0) return EMPTY;

  // Choose a Random Choice
  byte choice = (byte)random(found);

  // Remove Top/Bottom Walls from Current Cell and Neighbor
  if (choices[choice] == cells[currentCell].nTop) {
    cells[currentCell].flags &= ~WTOP;
    cells[cells[currentCell].nTop].flags &= ~WBOTTOM;
  }

  // Remove Left/Right Walls from Current Cell and Neighbor
  if (choices[choice] == cells[currentCell].nLeft) {
    cells[currentCell].flags &= ~WLEFT;
    cells[cells[currentCell].nLeft].flags &= ~WRIGHT;
  }

  // Remove Right/Left Walls from Current Cell and Neighbor
  if (choices[choice] == cells[currentCell].nRight) {
    cells[currentCell].flags &= ~WRIGHT;
    cells[cells[currentCell].nRight].flags &= ~WLEFT;
  }

  // Remove Bottom/Top Walls from Current Cell and Neighbor
  if (choices[choice] == cells[currentCell].nBottom) {
    cells[currentCell].flags &= ~WBOTTOM;        
    cells[cells[currentCell].nBottom].flags &= ~WTOP;
  }

  // Return Choice
  return choices[choice];
}

void createMaze()
{
  // Initialize All Cells
  for (byte y = 0; y < ROWS; y++) {
    for (byte x = 0; x < COLS; x++) {
      byte current = y * COLS + x;
      
      cells[current] = MazeCell();
      cells[current].flags = WTOP | WLEFT | WRIGHT | WBOTTOM;
      cells[current].details = 0;

      // Assume No Neighbors
      cells[current].nTop = EMPTY;
      cells[current].nLeft = EMPTY;
      cells[current].nRight = EMPTY;
      cells[current].nBottom = EMPTY;

      // Add Top Neighbor
      if (y != 0)
        cells[current].nTop = current - COLS;

      // Add Left Neighbor
      if (x != 0)
        cells[current].nLeft = current - 1;

      // Add Right Neighbor
      if (x < COLS - 1)
        cells[current].nRight = current + 1;
        
      // Add Bottom Neighbor
      if (y < ROWS - 1)  
        cells[current].nBottom = current + COLS;
    }
  }

  // Create Maze
  byte cellsOnStack = 0;
  byte unvisitedCells = CELL_COUNT;
  
  byte currentCell = 0;
  cells[currentCell].flags |= VISITED;
  unvisitedCells--;

  while (unvisitedCells > 0) {
    byte nextCell = chooseUnvisitedNeighbor(currentCell);

    if (nextCell != EMPTY) {
      cells[currentCell].flags |= ONSTACK;
      cellsOnStack++;

      currentCell = nextCell;
      cells[currentCell].flags |= VISITED;
      unvisitedCells--;
    } else {
      if (cellsOnStack > 0) {
        for (byte i = 0; i < CELL_COUNT; i++) {
          if ((cells[i].flags & ONSTACK)) {
            currentCell = i;
            cells[i].flags &= ~ONSTACK;
            cellsOnStack--;
            break;
          }
        }
      }
    }
  }

  // Pick an Exit in the Last Column
  byte randomExit = random(ROWS);

  // Determine Room Details (type, rotation and variation)
  for (byte y = 0; y < ROWS; y++) {
    for (byte x = 0; x < COLS; x++) {
      byte current = y * COLS + x;
      byte doorways = 0;

      // Count Number of Doors
      if (!(cells[current].flags & WTOP))
        doorways++;

      if (!(cells[current].flags & WLEFT))
        doorways++;
        
      if (!(cells[current].flags & WRIGHT))
        doorways++;
        
      if (!(cells[current].flags & WBOTTOM))
        doorways++;  

      // This Cell Contains the Exit
      if (x == (COLS - 1) && y == randomExit) {
        // Add a Doorway to the Right
        cells[current].flags &= ~WRIGHT;
        cells[current].flags |= HAS_EXIT;
        cells[current].flags |= LOCKED;
        doorways++;
      }
      
      byte roomType = 0;
      byte rotation = 0;
      byte variation = 0;
      
      switch (doorways) {
        case 1:
          // Set Room Type
          roomType = 0;

          // Determine Rotation
          if (!(cells[current].flags & WRIGHT)) {
            rotation = 1;
          } else {
            if (!(cells[current].flags & WBOTTOM)) {
              rotation = 2;
            } else {
              if (!(cells[current].flags & WLEFT)) {
                rotation = 3;
              }
            }
          }
          break;
        case 2:
          // Determine Room Type
          if ((cells[current].flags & WLEFT && cells[current].flags & WRIGHT) || (cells[current].flags & WTOP && cells[current].flags & WBOTTOM)) {
            // Across from Each Other
            roomType = 1; 

            // Determine Rotation
            if ((cells[current].flags & WLEFT && cells[current].flags & WRIGHT)) {
              rotation = 1;
              if (random(100) < 50)
                rotation = 3;
            } else {
              if (random(100) < 50)
                rotation = 2;              
            }
          } else {
            // L-Shaped
            roomType = 4; 
            
            // Determine Rotation
            if ((!(cells[current].flags & WRIGHT) && !(cells[current].flags & WBOTTOM))) {
              rotation = 1;
            } else {
              if ((!(cells[current].flags & WBOTTOM) && !(cells[current].flags & WLEFT))) {
                rotation = 2;
              } else {
                if ((!(cells[current].flags & WLEFT) && !(cells[current].flags & WTOP))) {
                  rotation = 3;
                }  
              }  
            }
          }
          break;
        case 3:
          // Set Room Type
          roomType = 2;

          // Determine Rotation
          if (cells[current].flags & WTOP) {
            rotation = 1;
          } else {
            if (cells[current].flags & WRIGHT) {
              rotation = 2;
            } else {
              if (cells[current].flags & WBOTTOM) {
                rotation = 3;
              }
            }
          }
          break;
        case 4:
          // Set Room Type
          roomType = 3;
Serial.println("FOUND A TYPE 3!!");
          // Determine Rotation
          rotation = random(4);
          break;          
      }

      // Pick a Random Variation
      variation = random(5);

      // Assign Details to Cell
      cells[current].details = roomType << 5 | variation << 2 | rotation;
    }
  }
}

void debugPrintMaze() {
  for (byte y = 0; y < ROWS; y++) {

    // Top Row
    if (y == 0) {
      for (byte x1 = 0; x1 < COLS; x1++) {
        byte current1 = y * COLS + x1;

          
        Serial.print("+");
          
        if ((cells[current1].flags & WTOP))
          Serial.print("---");
        else
          Serial.print("   ");

        if (x1 == COLS - 1)
          Serial.print("+");
      }
  
      Serial.println("");
    }
   
    for (byte x2 = 0; x2 < COLS; x2++) {
      byte current2 = y * COLS + x2;
  
      if ((cells[current2].flags & WLEFT) && x2 == 0)
          Serial.print("|");

      if ((cells[current2].flags & HAS_EXIT) == 0)
        Serial.print("   ");
      else
        Serial.print(" X ");
      
      if ((cells[current2].flags & WRIGHT))
          Serial.print("|");
        else
          Serial.print(" ");    
    }
  
    Serial.println("");

    for (byte x3 = 0; x3 < COLS; x3++) {
      byte current3 = y * COLS + x3;

      Serial.print("+");
      if ((cells[current3].flags & WBOTTOM))
        Serial.print("---");
      else
        Serial.print("   ");
      if (x3 == COLS - 1)  
        Serial.print("+");
    }

    Serial.println("");
  }
}


