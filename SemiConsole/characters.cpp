#include "entity.h"
#include "characters.h"

//Functions to create specific NPCs and set their dialogs

//NPC "Cindy" test
NPC createNPC_Cindy() {
    NPC Cindy = createNPC("Cindy l'Abrogée", "A strange little lady");
    Cindy.addDialog("Lionel m'a engrossé à l'aide!!!!\n");

    return Cindy;
}

NPC createNPC_Maxime() {
    NPC Maxime = createNPC("Maxime Ouais-Sinon", "An obnoxious looking lady");
    string longIntro;
    longIntro += "Mine brother. Thee were did summon by Herr Prosious himself. Thee shalt findeth Prosious in the most northern room. ";
    longIntro += "However, thee shalt findeth two keys before meeting that gent. One to unlock this northern gate, another for the northern gate behind this northern gate. ";
    longIntro += "Now, begone and findeth the first key, maggot!\n";
    Maxime.addDialog("Shoo! Shoo, sheeple!");
    Maxime.addDialog(longIntro);
    return Maxime;
}

/*NPC "Lionel"
NPC createNPC_Lionel() {

}*/
