#pragma once

#include "date.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <utility>
#include <map>
#include <functional>
#include <set>

using namespace std;

class Database {
public:
	void Add(const Date& d, const string& event);

	void Print(ostream& out) const;

	string Last(const Date& date) const;

	int RemoveIf(const function<bool(const Date&, const string&)>& predicate);

	vector<string> FindIf(function<bool(const Date&, const string&)> predicate) const;

private:
	map<Date, vector<string>> db;
	map<Date, set<string>> events;
};

