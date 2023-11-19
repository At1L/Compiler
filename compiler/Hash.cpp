#include "Hash.h"

Hash::Hash(){
    table = vector<Node>(100000);
}
//func that create  id in table for current word
ll Hash::getTableId(string& word)
{
    ll id = 0;
    ll constant = 33;
    for (int i = 0; i < word.size(); i++) {
        id += (word[i] * constant) % table.size();
        id %= table.size();
        constant *= constant;
    }
    while (id < 0) {
        id += table.size();
    }
    return id;
}
//check posiible collision
bool collisionCheck(Token t, Node* node) {
    Node* dummy = node;
    while (dummy != NULL) {
        if (dummy->val.type == t.type && dummy->val.name == t.name) return false;
        dummy = dummy->next;
    }
    return true;
}
//take token and put it in hash table
void Hash::addToken(Token t)
{
    int id = this->getTableId(t.name);
    if (this->table[id].val.type == "None" &&
        this->table[id].val.name == "None") {
        this->table[id].val = t;
    }
    //if collision happened and this is not token with same type and name just put it in node of table
    else if(collisionCheck(t, &table[id])) {
        Node* dummyNode = new Node;
        dummyNode->val = this->table[id].val;
        dummyNode-> next = this->table[id].next;
        this->table[id].val = t;
        this->table[id].next = dummyNode;
        dummyNode->prev = this->table[id].prev;
    }
}
