#include "entity.h"
#include "characters.h"

//Functions to create specific NPCs and set their dialogs

//NPC "Cindy" test
NPC createNPC_Cindy() {
    NPC Cindy = createNPC("Cindy", "Mrs Broger");
    Cindy.addDialog("Lionel m'a engrossé à l'aide!!!!\n");

    return Cindy;
}

/*NPC "Lionel"
NPC createNPC_Lionel() {

}*/
