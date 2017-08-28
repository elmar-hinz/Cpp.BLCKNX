//
// Created by Elmar Hinz on 2017-08-28 15:59:33.048187.
//

#include "Ctbl.h"
#include "CharacterTable.h"

namespace blcknx {

    void Ctbl::calc() {
        CharacterTable table(input);
        output = CharacterTable::to_string(table);
    }
    
}