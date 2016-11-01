#pragma once

#include "Variables.hpp"

struct ConfigNames
{
	//string WindowHeigh("WindowHeight");

	ConfigNames();
};

class Config final
{
private:
	mutable map<string, string> properties_;

protected:
	VOID setDefaults();
	VOID createLog();

	inline VOID setBool(string name, bool value)     { properties_[name] = (value)? "true" : "false"; }
	inline VOID setInt(string name, INT value)       { properties_[name] = to_string(value); }
	inline VOID setString(string name, string value) { properties_[name] = value; }
public:
	Config();
	~Config();

	inline BOOL exist(string name) const { return properties_.find(name) != properties_.end(); }

	inline BOOL    getBool(string name)    const { return (properties_[name] == "true")? TRUE : FALSE; }
	inline INT     getInt(string name)     const { return stoul(properties_[name]); }
	inline string  getString(string name)  const { return properties_[name]; }
	inline wstring getWString(string name) const { wstring_convert<codecvt_utf8_utf16<WCHAR>> converter; return wstring(converter.from_bytes(properties_[name])); }
};

