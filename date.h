#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <vector>

using namespace std;

class Date {
public:
	Date(const int y = 0, const int m = 0, const int d = 0) : year(y), month(m), day(d) {}

	string GetStringDate() const;
	int GetYear() const;
	int GetMonth() const;
	int GetDay() const;

private:
	const int year;
	const int month;
	const int day;
};

Date ParseDate(istream& is);

inline bool operator<(const Date& lhs, const Date& rhs) {
	//return lhs.GetStringDate() < rhs.GetStringDate();
	return vector<int>{lhs.GetYear(), lhs.GetMonth(), lhs.GetDay()} < vector<int>{rhs.GetYear(), rhs.GetMonth(), rhs.GetDay()};
}

//inline bool operator<=(const Date& lhs, const Date& rhs) {
//	return lhs.GetStringDate() <= rhs.GetStringDate();
//}
//
//inline bool operator>(const Date& lhs, const Date& rhs) {
//	return lhs.GetStringDate() > rhs.GetStringDate();
//}
//
//inline bool operator>=(const Date& lhs, const Date& rhs) {
//	return lhs.GetStringDate() >= rhs.GetStringDate();
//}
//
//inline bool operator==(const Date& lhs, const Date& rhs) {
//	return lhs.GetStringDate() == rhs.GetStringDate();
//}
//
//inline bool operator!=(const Date& lhs, const Date& rhs) {
//	return lhs.GetStringDate() != rhs.GetStringDate();
//}

inline ostream& operator << (ostream& os, const Date& d) {
	return os << d.GetStringDate();
}