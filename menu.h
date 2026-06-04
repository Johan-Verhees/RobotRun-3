#include <Arduino.h>
#include <Pololu3piPlus32U4.h>

typedef enum MenuState {
    Mainmenu,
    OrderInzien,
    Invoeren,
    Verwijderen,
    Start
};

typedef enum ButtonEvent {
  NONE,
  NEXT,
  BACK,
  CONFIRM
};

void InitMenuSystem();
void Menu();
ButtonEvent readButtons();