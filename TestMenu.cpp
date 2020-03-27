/*
==============================================================
Author: Mamadou BA Neige
Email: naedioba@gmail.comp

Name of Library: TestMenu

This Library allows to create LCD Menus with  line of title and 3 lines of options for LCD 20x04.
In order to be able to scroll in the menu, I have added the possibiité to attache 3 boutons: UP, Down, OK.

How to use this Library:

1. Include the library in your arduino  sketch: #include <TestMenu.h>

2. create the object of the menu: TestMenu myMenu(MenuTitle, title1, title2, title3, Up, Down, Ok);
	Replace the titles with your own tilte, and the boutons (Up, Down, OK) with the pins to which your buttons are attached.
	Exemple: my buttons are attached respectivley to pins 2, 4, 3, myMenu is created with the following line:
		TestMenu myMenu("Title of Menu", "My title 1", "My title 2", "My title 3", 2, 4, 3);
		
	The result on the LCD dispaly should like like this:
	
	 ___________________
	|	Title of Menu	|
	|	  My title 1	|
	|	>>My title 2	|
	|	  My title 3	|
	 -------------------
	 
	 Remark: A small arrow (>>) indicates the active option.

3. Include the following line in the Setup() section of your sketch: myMenu.monSetup();

4. Use the menu like in this code:
	if (myMenu.monMenuTest()==1){
      Action1();
    }
    if (myMenu.monMenuTest()==2){
      Action2();
    }
    if (myMenu.monMenuTest()==3){
      Action3();
    }
==============================================================
*/
#include "TestMenu.h"
#include "Arduino.h"
#include "SoftwareSerial.h"
#include <avr/io.h>
#include <avr/wdt.h>
//---------------
#include <LCD.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd2(0x20, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);


 TestMenu::TestMenu (String TitreMenu, String Titre1, String Titre2, String Titre3, int BoutonS, int BoutonB, int BoutonH) // (sans boutons Rouge et Vert)
 {
	
	monTitreMenu=TitreMenu; 
	monTitre1=Titre1;
	monTitre2=Titre2;
	monTitre3=Titre3;
	
	// This is for the buttons
	BoutonSelect=BoutonS;
	BoutonBas=BoutonB;
	BoutonHaut=BoutonH;
}

void TestMenu::monSetup() {

  Serial.begin(9600);  
  lcd2.begin(20,4); 

  pinMode(BoutonSelect, INPUT_PULLUP);

  lcd2.createChar(1, FlecheHaut2);
  lcd2.createChar(2, FlecheBas2);
  lcd2.createChar(3, FlecheMenu2);
  lcd2.createChar(4, FlecheGauche2);
  lcd2.createChar(5, indic2);

}

//Tu peux par exemple changer le void TestMenu::monMenuTest() en uint8_t TestMenu::monMenuTest()
uint8_t TestMenu::monMenuTest()

{

	while(1) {

	  EtatBoutonHAUT = digitalRead(BoutonHaut);
	  EtatBoutonBAS = digitalRead(BoutonBas);
	  EtatBoutonSELECT = digitalRead(BoutonSelect);

	  if(EtatBoutonHAUT == HIGH && EtatBoutonSELECT == HIGH) { // redemarrage par appui sur boutons Haut et Select
		resetFunc();
	  }

	  if(EtatBoutonHAUT == HIGH && EtatBoutonBAS == HIGH) { 
		loop();
	  }

    //---------------------------------------------
	// début de mon programme ici
	
	  if(digitalRead(BoutonHaut) == HIGH) {
		ValMenu--;
	  }
	  if(digitalRead(BoutonBas) == HIGH) {
		ValMenu++;
	  }
	  if(ValMenu >=4) {ValMenu = 1;}
	  if(ValMenu <=0) {ValMenu = 3;}
	  
	  
	  switch (ValMenu) { // debut de la structure
		case 1: // cas 1
		lcd2.clear();
		lcd2.setCursor(0,0);
		lcd2.print(monTitreMenu);
		lcd2.setCursor(0,1);
		lcd2.write(3);         	// indicateur sur option 1
		lcd2.print("1:");   		// option 1
		lcd2.print(monTitre1);
		lcd2.setCursor(1,2);
		lcd2.print("2:");     	// option 2
		lcd2.print(monTitre2);
		lcd2.setCursor(1,3);
		lcd2.print("3:");     	// option 3
		lcd2.print(monTitre3);
		  
		  if(EtatBoutonSELECT ==1){
			delay(50);
			EtatBoutonSELECT = digitalRead(BoutonSelect);
			if(EtatBoutonSELECT ==0){
			  action=1;
			  return action;
			}
		  } else {delay(150);}
		break;
	//************************************************************************
	   case 2: // cas 2
		lcd2.clear();
		lcd2.setCursor(0,0);
		lcd2.print(monTitreMenu);
		lcd2.setCursor(1,1);
		lcd2.print("1:");  		// option 1
		lcd2.print(monTitre1);
		lcd2.setCursor(0,2);
		lcd2.write(3);          	// indicateur sur option 2
		lcd2.print("2:"); 		// option 2
		lcd2.print(monTitre2);
		lcd2.setCursor(1,3);
		lcd2.print("3:"); 		// option 3
		lcd2.print(monTitre3);
		
		  if(EtatBoutonSELECT ==1){
			delay(50);
			EtatBoutonSELECT = digitalRead(BoutonSelect);
			if(EtatBoutonSELECT ==0){
			  action=2;
			  return action;
			}
		  } else {delay(150);}
	  break;
	//-------------------------------
	  case 3: // cas 3
			  lcd2.clear();
			  lcd2.setCursor(0,0);
			  lcd2.print(monTitreMenu);
			  lcd2.setCursor(1,1);
			  lcd2.print("1:");  		// option 1
			  lcd2.print(monTitre1);
			  lcd2.setCursor(1,2);
			  lcd2.print("2:"); 			// option 2
			  lcd2.print(monTitre2);
			  lcd2.setCursor(0,3);
			  lcd2.write(3);       		// indicateur sur option 3
			  lcd2.print("3:"); 			// option 3
			  lcd2.print(monTitre3);
			  if(EtatBoutonSELECT ==1){
				delay(50);
				EtatBoutonSELECT = digitalRead(BoutonSelect);
				if(EtatBoutonSELECT ==0){
				  action=3;
				  return action;
				}
			  } else {delay(150);}
		  break;
	//-------------------------------
	} // fin switch
	// fin de mon programme
    //---------------------------------------------     
  } // fin while
  //return action;
} // fin void 