#include "menu.h"
using namespace Pololu3piPlus32U4;

OLED display;
ButtonA buttonA;
ButtonB buttonB;
ButtonC buttonC;

// MENU STATE
MenuState state = Mainmenu;
int cursor = 0;
bool Displayupdate = true;

// INVOER STATE
bool Invoer_SelectX = true;
bool Invoer_SelectY = false;

int orderX[6];
int orderY[6];

int xCoord = 0;
int yCoord = 0;

// INIT
void InitMenuSystem() {
  display.init();
  display.clear();
  display.setLayout21x8();
}

// BUTTON INPUT
ButtonEvent readButtons() {
  if(buttonA.getSingleDebouncedPress()) return BACK;
  if(buttonB.getSingleDebouncedPress()) return NEXT;
  if(buttonC.getSingleDebouncedPress()) return CONFIRM;
  return NONE;
}

// DISPLAY FUNCTIES
void DisplayFooter() {
  display.gotoXY(0,6);
  display.print("---------------------");
  display.gotoXY(0,7);
  display.print("Back   Next   Confirm");
}

void DisplayCursor(bool on, int cursorY) {
  for(int i = 0; i < 6; i++) {
    display.gotoXY(0,i);
    display.print("  ");
  }
  if(on) {
    display.gotoXY(0, cursorY);
    display.print("> ");
  }
}

void DisplayMainMenu() {
  const char* MainMenuItems[4] = {
    "Order inzien",
    "Order invoeren",
    "Order verwijderen",
    "Start order"
  };

  display.clear();
  DisplayFooter();

  for(int i = 0; i < 4; i++) {
    display.gotoXY(2, i);
    display.print(MainMenuItems[i]);
  }

  display.gotoXY(0, cursor);
  display.print("> ");
}

void DisplayInvoeren() {
  display.clear();
  DisplayFooter();

  display.gotoXY(0,6);

if(Invoer_SelectX)
{
    display.print("X=");
    display.print(xCoord);
}
else
{
    display.print("Y=");
    display.print(yCoord);
}

  for(int i = 0; i < 6; i++) {
    display.gotoXY(2, i);
    display.print(i);
    display.print(": ");

    display.gotoXY(5,i);
    display.print("X:");
    display.print(orderX[i]);
    display.print(",");
    display.gotoXY(10,i);
    display.print("Y:");
    display.print(orderY[i]);
  }
}

// INVOER LOGICA
void HandleInvoeren(ButtonEvent event) {

  if(event == BACK) {
    cursor = 0;
    Invoer_SelectX = true;
    Invoer_SelectY = false;
    state = Mainmenu;
    Displayupdate = true;
    return;
  }

  if(Invoer_SelectX) {
    if(event == NEXT) {
      xCoord = (xCoord + 1) % 5;
      Displayupdate = true;
    }

    if(event == CONFIRM) {
      Invoer_SelectX = false;
      Invoer_SelectY = true;
      Displayupdate = true;
    }
  } 
  else if(Invoer_SelectY) {
    if(event == NEXT) {
      yCoord = (yCoord + 1) % 5;
      Displayupdate = true;
    }

    if(event == CONFIRM) {
      orderX[cursor] = xCoord;
      orderY[cursor] = yCoord;

      cursor = (cursor + 1) % 6;

      xCoord = 0;
      yCoord = 0;

      Invoer_SelectX = true;
      Invoer_SelectY = false;
      Displayupdate = true;
    }
  }
}

// UPDATE DISPLAY
void UpdateDisplay() {
  if(state == Mainmenu) {
    DisplayMainMenu();
  } 
  else if(state == Invoeren) {
    DisplayInvoeren();
  }
}

// MENU STATE MACHINE
void Menu() {
  ButtonEvent event = readButtons();

  switch (state)
  {
  case Mainmenu:
    if(event == NEXT) {
      cursor = (cursor + 1) % 4;
      Displayupdate = true;
    }

    if (event == CONFIRM) {
      MenuState next[4] = {OrderInzien, Invoeren, Verwijderen, Start};
      state = next[cursor];
      cursor = 0;
      Displayupdate = true;
    }
    break;

  case Invoeren:
    HandleInvoeren(event);
    break;

  default:
    break;
  }

  if(Displayupdate) {
    Displayupdate = false;
    UpdateDisplay();
    DisplayCursor(true, cursor);
  }
}
