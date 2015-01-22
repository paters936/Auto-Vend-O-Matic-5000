
//Setup the database for the items
// The read and write handlers for using the EEPROM Library
void writer(unsigned long address, byte data) {
    EEPROM.write(address, data);     //external
}
byte reader(unsigned long address) {
    return EEPROM.read(address);     //external
}



//Setup the structure of the stored dispenser item data
struct ItemData {
  char id[13];
  char name[21];
  int price;
  int stockLevel;
  int vendsSinceCashout;
} 
itemData;

// Create an EDB object with the appropriate write and read handlers
EDB itemDb(&writer, &reader);




//Helper method
void copyString(char *p1, char *p2)
{
    while(*p2 !='\0')
    {
       *p1 = *p2;
       p1++;
       p2++;
     }
    *p1= '\0';
}


void createDefaultRecords() {
  //create records - testing
  for (int recno = 1; recno <= 11; recno++)
  {
    copyString(itemData.id, "ID");
    copyString(itemData.name, "Name");
    itemData.price = recno * 2;
    itemData.vendsSinceCashout = 0;
    itemData.stockLevel = 10;
    itemDb.appendRec(EDB_REC itemData);
  }
}

void initDatabase() { 
  
  
  
  //Database - wipe existing db
  itemDb.create(ITEM_DB_START, ITEM_DB_TABLE_SIZE, sizeof(itemData));
  
  //Database - open without wiping
  itemDb.open(ITEM_DB_START);
  
  
  
  createDefaultRecords();
  
}


boolean lookupItem(int keyPress) {
  
  //fetch the item from the db
  EDB_Status result = itemDb.readRec(keyPress, EDB_REC itemData);
  if (result == EDB_OK) {
    return true;
  } else {
    return false;
  }
}


boolean updateItem(int keyPress) {
  EDB_Status result = itemDb.updateRec(keyPress, EDB_REC itemData);
  if (result == EDB_OK) {
    return true;
  } else {
    return false;
  }
}



