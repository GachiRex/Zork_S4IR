#include "entity.h"
#include "characters.h"

//Functions to create specific NPCs and set their dialogs

//NPC "Cindy" test
NPC createNPC_Cindy() {
    NPC Cindy = createNPC("Cindy", "Welcoming NPC");
    Cindy.addDialog("Hello, world!");

    return Cindy;
}

/*NPC "Lionel"
NPC createNPC_Lionel() {

}*/
