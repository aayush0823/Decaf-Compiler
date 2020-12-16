#ifndef SYMBOL_TABLE_CLASS_H
#define SYMBOL_TABLE_CLASS_H

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "Record.h"
#include "Scope.h"

class SymbolTable{

    public:
        Scope* current;
        Scope* root;

        SymbolTable(){
            this->root = new Scope(NULL);
            this->current = this->root;
        }

        void enterScope() {
            // cout << "Entering Children Scope" << endl;
            this->current = this->current->nextChild();
        }

        void exitScope() {
            // cout << "Entering parent Scope" << endl;
            this->current = this->current->getParent();
        }

        void addRecord(string key, Record* item){
            this->current->addRecord(key, item);
        }

        Record* lookup(string key){
            return current->lookup(key);
        }

        void printTable(){
            this->root->printScope();
        }

        void resetTable() {
            this->current = this->root;
            this->root->resetScope();
        }

        Scope* getCurrent() {
            return this->current;
        }

        void setCurrent(Scope* current) {
            this->current = current;
        }
};

#endif