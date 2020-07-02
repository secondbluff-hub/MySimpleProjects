#include "date.h"

string Date::GetStringDate() const {
	stringstream is;
	is << setfill('0') << setw(4) << year << '-' << setw(2) << month << '-' << setw(2) << day;
	string result;
	is >> result;
	return result;
}

int Date::GetYear() const {
	return year;
}

int Date::GetMonth() const {
	return month;
}

int Date::GetDay() const {
	return day;
}

Date ParseDate(istream& is) {
	//string date;
	//is >> date;
	//int year = stoi(date.substr(0, date.find('-')));
	//date.erase(date.begin(), date.begin() + date.find('-') + 1);
	//int month = stoi(date.substr(0, date.find('-')));
	//date.erase(date.begin(), date.begin() + date.find('-') + 1);
	//int day = stoi(date);

	string year, month, day;
	getline(is, year, '-');
	getline(is, month, '-');
	getline(is, day, ' ');

	return Date(stoi(year), stoi(month), stoi(day));
}