


#ifndef KEYPAD_CFG_H_
#define KEYPAD_CFG_H_



#define  FIRST_OUTPUT   PINA0
#define  FIRST_INPUT    PINB4




#define  ROWS   4
#define  COLS   4



const u8 KeysArray[ROWS][COLS]={
	{'7','8','9','/'},
	{'4','5','6','*'},	
	{'1','2','3','-'},	
	{'c','0','=','+'},	
};


#endif /* KEYPAD_CFG_H_ */