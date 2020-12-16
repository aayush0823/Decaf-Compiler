#ifndef SCOPE_CLASS_H
#define SCOPE_CLASS_H

#include <iostream>
#include <vector>
#include <string>
#include <map>

#include "Record.h"

class Scope {

	public:
        int next;
        Scope* parent;
        vector <Scope *> children;
        map <string, Record *> records;

        string name;
        string type;

	Scope(Scope* parent ) {
        if(parent != NULL){
    		this->parent = parent;
        } else {
			this->parent = NULL;
		}
	}

    Scope* nextChild() {
		
		Scope* nextChild;

		if (this->next >= this->children.size()) {

			nextChild = new Scope(this);
			this->children.push_back(nextChild);
		
        } else {

			nextChild = this->children[next];
		}

		this->next++;
		
        return nextChild;
	}

    Scope* getParent(){
        return this->parent;
    }

    void addRecord(string key, Record* item){
        this->records.insert({key, item});
    }

	Record* lookup(string key) {
		
		if (this->records.find(key) != this->records.end()) 
			return this->records[key];
		else { 
			if (this->parent == NULL)
				return NULL; 
			else
				return this->parent->lookup(key); // Check for variable in parentScope
		}
	}

	void printScope(){
		for (auto it=this->records.begin(); it!=this->records.end(); ++it){
			string key = it->first;
			Record* value = it->second;
			string id = value->getId();
			string type = value->getType();

			std::cout << key << " " << id << " " << type << endl;
		}
		
		for (auto scope : this->children){
			scope->printScope();
		}
	}

	void resetScope() {// Must be called after each traversal
		this->next = 0;
		
		for (int i = 0; i < this->children.size(); i++){
			this->children[i]->resetScope();
		}
	}

	std::string getName() {
		return this->name;
	}

	std::string getType() {
		return this->type;
	}

	void setName(std::string name) {
		this->name = name;
	}

	void setType(std::string type) {
		this->type = type;
	}

};

#endif