#include "variable.h"
#include "../../rapidjson/stringbuffer.h"
#include "../../rapidjson/prettywriter.h"
#include "../../rapidjson/document.h"
#include <iostream>
#include <string.h>
using namespace std;

variable::variable(string _json) {
	//cout << "String " << _json << " Length " << _json.length() << endl;

	//_json.append('\0');
	rapidjson::Document jsonDoc;
	char buffer[_json.length()];
    bzero(buffer,_json.length());

	_json.copy(buffer, _json.length());
	buffer[_json.length()] = '\0';
	//cout << buffer << endl;

	jsonDoc.ParseInsitu(buffer).HasParseError();


	assert(jsonDoc.IsObject());
	assert(jsonDoc.HasMember("name"));
	assert(jsonDoc.HasMember("save"));
	assert(jsonDoc.HasMember("values"));
	assert(jsonDoc.HasMember("rank"));
	assert(jsonDoc.HasMember("dimensions"));

	name = jsonDoc["name"].GetString();
	rank = jsonDoc["rank"].GetInt();
	//save = jsonDoc["save"].GetBool() ? "true" : "false";
	save = 0;

	rapidjson::Value& dimensionsArray = jsonDoc["dimensions"];
	assert(dimensionsArray.IsArray());
	dimensions = new int[rank];
	//calculatiung length of values array up here to avoid using two loops
	int length = 1;

	for (int i = 0; i < rank; ++i) {
		dimensions[i] = dimensionsArray[i].GetInt();
		length *= dimensions[i];
	}

	cout << "Length " << length << endl;

	rapidjson::Value& valueArray = jsonDoc["values"];
	assert(valueArray.IsArray());
	values = new double[length];

	for (int i = 0; i < length; ++i) {
		values[i] = valueArray[i].GetDouble();
	}
}

variable::~variable() {
	delete dimensions;
	delete values;
}

string variable::getName() {
	return name;
}

int variable::getRank() {
	return rank;
}

int variable::getDimension(int _pos) {
	if (_pos >= rank) {
		return -1;
	}

	return dimensions[_pos];
}

double variable::getValue(int _pos) {
	int size = 1;
	for (int i = 0; i < rank; ++i) {
		size = size * dimensions[i];
	}

	if (_pos >= size) {
		throw string("Oh shit this was a mistake");
	}

	return values[_pos];
}

bool variable::getSave() {
	return save;
}

void variable::printVar() {
	cout << name << " " << rank << endl;
}