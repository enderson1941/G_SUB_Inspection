#pragma once
#ifndef INI_PARSER_H
#define INI_PARSER_H

#include "iostream"
#include "fstream"
#include "sstream"
#include "vector"
#include "cstdlib"
#include "map"

using namespace std;

class ININode
{
public:
	ININode(string root, string key, string value)
	{
		this->root	= root;
		this->key	= key;
		this->value	= value;
	}
	string root;
	string key;
	string value;
};

class SubNode
{
public:
	void InsertElement(string key, string value)
	{
		sub_node.insert(pair<string,	string>(key, value));
	}
	map<string, string> sub_node;
};

class INIParser
{
public:
	int ReadINI(char*	path);
	CString GetValue(string root, CString key, int& size_);
	vector<ININode>::size_type GetSize() { return map_ini.size(); }
	vector<ININode>::size_type SetValue(string root, string key, CString value);
	int WriteINI(char*	path);
	void Clear() { map_ini.clear(); }
	
private:
	map<string, SubNode> map_ini;
};
#endif
// INI_PARSER_H