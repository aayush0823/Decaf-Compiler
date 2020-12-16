#ifndef RECORD_CLASS_H
#define RECORD_CLASS_H

#include <iostream>
#include <vector>
#include <string>

class Record {

	public:
        string id;
	    string type;

	Record(string id, string type) {
		this->id = id;
		this->type = type;
	}

	std::string getId() {
		return this->id;
	}

	std::string getType() {
		return this->type;
	}

	void setId(std::string id) {
		this->id = id;
	}

	void setType(std::string type) {
		this->type = type;
	}

};

class VariableRecord : public Record
{
public:
	VariableRecord(string id, string type):Record(id, type){

	}
     
};

class MethodRecord : public Record
{
public:
	vector<VariableRecord*> paramList;
	vector<VariableRecord*> variableList;

	// MethodRecord(string id, string type, vector<VariableRecord*> paramList, vector<VariableRecord*> variableList):Record(id, type){
	MethodRecord(string id, string type):Record(id, type){
		
	}
     
	void addParam(VariableRecord* param){
		this->paramList.push_back(param);
	}

	vector<VariableRecord*> getParamList(){
		return this->paramList;
	}

	void setParamList(vector<VariableRecord*> paramList){
		this->paramList = paramList;
	}

	void addVariable(VariableRecord* variable){
		this->variableList.push_back(variable);
	}

	vector<VariableRecord*> getVariableList(){
		return this->variableList;
	}

	void setVariableList(vector<VariableRecord*> variableList){
		this->variableList = variableList;
	}
};

#endif