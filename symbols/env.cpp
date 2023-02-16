#include "env.h"

Env::Env(Env* n) : prev(n) {}

Env::~Env() {
    for(auto iter = table.begin(); iter != table.end(); iter++) {
        if(iter->second) delete iter->second;
        iter->second = NULL;
    }    
}

void Env::put(Token* w, Id* i) {
    table.insert(envHashTable::value_type(w, i));
}

Id* Env::get(Token* w) {
    for (Env* e = this; e != NULL; e = e->prev ) {
        envHashTable::iterator iter = e->table.find(w);
        if(iter != e->table.end()) {
            return iter->second;
        }
    }
    return NULL;
}

