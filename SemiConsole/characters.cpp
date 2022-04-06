#include "entity.h"
#include "characters.h"

//Functions to create specific NPCs and set their dialogs

//NPC "C" test
NPC createNPC_C() {
    NPC C = createNPC("C", "Welcoming NPC");
    C.addDialog("Hello, world!");

    return C;
}
