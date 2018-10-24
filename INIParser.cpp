#include "stdafx.h"
#include "INIParser.h"

//remove all blank space
string& TrimString(string &str)
{
	string::size_type pos = 0;
	while (str.npos != (pos = str.find("	")))
		str = str.replace(pos, pos + 1, "");
	return str;
}

//read in INI file and parse it
int INIParser::ReadINI(char*	path)
{
	ifstream in_conf_file(path);
	if (!in_conf_file) 
		return 0;
	string str_line = "";
	string str_root = "";
	vector<ININode> vec_ini;
	while (getline(in_conf_file,	str_line))
	{
		string::size_type left_pos = 0;
		string::size_type right_pos = 0;
		string::size_type equal_div_pos = 0;
		string str_key = "";
		string str_value = "";
		if ((str_line.npos != (left_pos = str_line.find("[")))
					&& (str_line.npos != (right_pos = str_line.find("]"))))
		{
			//cout << str_line.substr(left_pos + 1, right_pos - 1) << endl;
			str_root = str_line.substr(left_pos + 1, right_pos - 1);
		}
		if (str_line.npos	!= (equal_div_pos = str_line.find("=")))
		{
			str_key	= str_line.substr(0, equal_div_pos);
			str_value = str_line.substr(equal_div_pos + 1, str_line.size() - 1);
			str_key	= TrimString(str_key);
			str_value = TrimString(str_value);
			//cout << str_key << "=" << str_value << endl;
		}
		if ((!str_root.empty())
			&& (!str_key.empty()) && (!str_value.empty()))
		{
			ININode ini_node(str_root, str_key, str_value);
			vec_ini.push_back(ini_node);
			//cout << vec_ini.size() << endl;
		}
	}
	in_conf_file.close();
	in_conf_file.clear();

	//vector convert to map
	map<string, string> map_tmp;
	vector<ININode>::iterator itr;
	for (itr = vec_ini.begin(); itr != vec_ini.end(); ++itr)
	{
		map_tmp.insert(pair<string, string>(itr->root, ""));
	}
	for (map<string, string>::iterator itr = map_tmp.begin(); itr != map_tmp.end(); ++itr)
	{
		SubNode sn;
		//cout << itr->first << endl;
		vector<ININode>::iterator sub_itr;
		for (sub_itr = vec_ini.begin(); sub_itr != vec_ini.end(); ++sub_itr)
		{
			if (sub_itr->root == itr->first)
			{
				//cout << sub_itr->key << "=" << sub_itr->value << endl;
				sn.InsertElement(sub_itr->key,	sub_itr->value);
			}
		}
		map_ini.insert(pair<string, SubNode>(itr->first, sn));
	}
	return 1;
}

//get value by root and key
CString INIParser::GetValue(string root, CString key, int& size_)
{
	CString trs_msg;
	string tmp_string;
	string key_;
	map<string, SubNode>::iterator itr;
	map<string, string>::iterator sub_itr;
	key_ = CW2A(key.GetString());
	itr = map_ini.find(root);
	if (key_ == "-")
	{
		/*for (sub_itr = itr->second.sub_node.begin(); 
			sub_itr != itr->second.sub_node.end(); sub_itr++)
		{
			tmp_string = sub_itr->first;
			trs_msg = tmp_string.c_str();
			msg_.push_back(trs_msg);
		}*/
		trs_msg.Format(L"%d", itr->second.sub_node.size());
		return trs_msg;
	}
	else
	{
		size_ = itr->second.sub_node.size();
		sub_itr = itr->second.sub_node.find(key_);
		if (!(sub_itr->second).empty())
		{
			tmp_string = sub_itr->second;
			trs_msg = tmp_string.c_str();
			return trs_msg;
		}
		else
		{
			trs_msg = L"-";
			return trs_msg;
		}
	}
}

//write ini file
int INIParser::WriteINI(char*	path)
{
	ofstream out_conf_file(path);
	if (!out_conf_file)
		return -1;
	//cout << map_ini.size() << endl;
	map<string, SubNode>::iterator itr;
	for (itr = map_ini.begin(); itr != map_ini.end(); ++itr)
	{
		//cout << itr->first << endl;
		out_conf_file	<< "[" << itr->first << "]" << endl;
		map<string, string>::iterator sub_itr;
		for (sub_itr = itr->second.sub_node.begin(); sub_itr != itr->second.sub_node.end(); ++sub_itr)
		{
			//cout << sub_itr->first << "=" << sub_itr->second << endl;
			out_conf_file	<< sub_itr->first << "=" << sub_itr->second << endl;
		}
	}
	out_conf_file.close();
	out_conf_file.clear();
	return 1;
}

//set value
vector<ININode>::size_type
INIParser::SetValue(string root, CString key_, CString value)
{
	string value_;
	string key;
	value_ = CW2A(value.GetString());
	USES_CONVERSION;
	key = W2A(key_);
	map<string, SubNode>::iterator itr = map_ini.find(root);
	if (map_ini.end()!= itr)
		itr->second.sub_node.insert(pair<string, string>(key, value_));
	else
	{
		SubNode sn;
		sn.InsertElement(key, value_);
		map_ini.insert(pair<string, SubNode>(root, sn));
	}
	return map_ini.size();
}