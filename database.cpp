#include "database.h"

void Database::Add(const Date& date, const string& event) {
	if (!events[date].count(event) && !event.empty()) {
		events[date].insert(event);
		db[date].push_back(event);
	}
	else if(events.at(date).empty()){
		events.erase(date);
	}
}

void Database::Print(ostream& out) const {
	for (const auto& [key, value] : db) {
		for (const auto& v : value) {
			out << key << ' ' << v << endl;
		}
	}
}

string Database::Last(const Date& date) const {
	auto it = db.upper_bound(date);
	if (db.empty() || it == db.begin()) {
		return "No entries";
	}
	else {
		--it;
		return it->first.GetStringDate() + ' ' + *(it->second.rbegin());
	}
}

int Database::RemoveIf(const function<bool(const Date&, const string&)>& predicate) {
	int count = 0;

	
	//for (auto it = db.begin(); it != db.end();) {
	//	auto bound = stable_partition(it->second.begin(), it->second.end(), [&](const string& event) { return !predicate(it->first, event); });

	//	if (bound == it->second.begin()) {
	//		count += it->second.size();
	//		if (it->first == db.begin()->first && db.size() == 1) {
	//			db.clear();
	//			events.clear();
	//			break;
	//		}
	//		else {
	//			events.erase(it->first);
	//			db.erase(it++);
	//		}
	//	}
	//	else if (bound != it->second.end()) {
	//		events[it->first].clear();
	//		events[it->first].insert(it->second.begin(), bound);
	//		count += distance(bound, it->second.end());

	//		//db[it->first].erase(bound, it->second.end());
	//		db[it->first].resize(distance(it->second.begin(), bound));

	//		++it;
	//	}
	//	else {
	//		++it;
	//	}
	//}
	
	vector<Date> dateToRemove;
	for (auto& [key, value] : db) {
		auto bound = stable_partition(value.begin(), value.end(), [&, key = key](const string& event) { return !predicate(key, event); });

		if (bound == value.begin()) {
			count += db.at(key).size();
			dateToRemove.push_back(key);
			events.erase(key);
		}
		else if(bound != db[key].end()){

			events[key].clear();
			events[key].insert(db[key].begin(), bound);
			count += distance(bound, db.at(key).end());

			//db[key].erase(bound, db[key].end());
			db[key].resize(distance(db.at(key).begin(), bound));
		}
	}
	for (const auto& item : dateToRemove) {
		db.erase(item);
	}
	
	return count;
}

vector<string> Database::FindIf(function<bool(const Date&, const string&)> predicate) const {

	vector<string> result;

	for (const auto& d : db) {
		vector<string> out;
		copy_if(d.second.begin(), d.second.end(), inserter(out, out.begin()), [&](const string& event) { return predicate(d.first, event); });
		for (auto i = out.begin(); i != out.end(); ++i) {
			result.push_back(d.first.GetStringDate() + ' ' + *i);
		}
	}
	return result;
}