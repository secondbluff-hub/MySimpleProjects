#pragma once

#include <iostream>
#include <sstream>
#include <exception>
#include <string>
#include <map>
#include <set>
#include <vector>
#include <utility>

using namespace std;

template <class T>
ostream& operator << (ostream& os, const vector<T>& v);

template <class T>
ostream& operator << (ostream& os, const set<T>& s);

template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m);

template <class K, class V>
ostream& operator << (ostream& os, const pair<K, V>& p);

template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint);

void Assert(bool b, const string& hint);

class TestRunner {
public:
	template <class TestFunc>
	void RunTest(TestFunc func, const string& test_name);

	~TestRunner();

private:
	int fail_count = 0;
};




// VECTOR
template <class T>
ostream& operator << (ostream& os, const vector<T>& v) {
	os << "{";
	bool first = true;
	for (const auto& x : v) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

// SET
template <class T>
ostream& operator << (ostream& os, const set<T>& s) {
	os << "{";
	bool first = true;
	for (const auto& x : s) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << x;
	}
	return os << "}";
}

// MAP
template <class K, class V>
ostream& operator << (ostream& os, const map<K, V>& m) {
	os << "{";
	bool first = true;
	for (const auto& kv : m) {
		if (!first) {
			os << ", ";
		}
		first = false;
		os << kv;
	}
	return os << "}";
}

// PAIR
template <class K, class V>
ostream& operator << (ostream& os, const pair<K, V>& p) {
	return os << p.first << ' ' << p.second;
}

// ANY
template<class T, class U>
void AssertEqual(const T& t, const U& u, const string& hint)
{
	if (t != u) {
		ostringstream os;
		os << "Assertion failed: " << t << " != " << u << " Hint: " << hint;
		throw runtime_error(os.str());
	}
}

template <class TestFunc>
void TestRunner::RunTest(TestFunc func, const string& test_name) {
	try {
		func();
		cerr << test_name << " OK" << endl;
	}
	catch (runtime_error& e) {
		++fail_count;
		cerr << test_name << " fail: " << e.what() << endl;
	}
}