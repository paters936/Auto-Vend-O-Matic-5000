
 
 
 byte colPins[COLS] = {KEYPAD_COL0, KEYPAD_COL1};
 
byte rowPins[ROWS] = {KEYPAD_ROW0, 
              KEYPAD_ROW1,
              KEYPAD_ROW2,
              KEYPAD_ROW3,
              KEYPAD_ROW4,
              KEYPAD_ROW5,
              KEYPAD_ROW6,
              KEYPAD_ROW7,
              KEYPAD_ROW8,
              KEYPAD_ROW9};
char keys[ROWS][COLS] = {
                {1,11},
                {2,12},
                {3,13},
                {4,14},
                {5,15},
                {6,16},
                {7,17},
                {8,18},
                {9,19},
                {10,20}
              };
              
int dispenserKeyAssignments[] = {40,39,38,37,36,35,34,33,31,32,30,-1,-1,-1,-1};

