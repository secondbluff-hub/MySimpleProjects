#pragma once

#include "date.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;

enum class LogicalOperation {
	Or,
	And,
};

enum class Comparison {
	Less,
	LessOrEqual,
	Greater,
	GreaterOrEqual,
	Equal,
	NotEqual,
};

class Node {
public:
	virtual bool Evaluate(const Date& date, const string& event) const = 0;
};

class EmptyNode : public Node {
public:
	explicit EmptyNode() {}

	bool Evaluate(const Date& date, const string& event) const override;
};

class DateComparisonNode : public Node {
public:
	explicit DateComparisonNode(const Comparison& cmp, const Date& date) : _cmp(cmp), _date(date) {}

	bool Evaluate(const Date& date, const string& event) const override;

private:
	const Comparison _cmp;
	const Date _date;
};

class EventComparisonNode : public Node {
public:
	explicit EventComparisonNode(const Comparison& cmp, const string& event) : _cmp(cmp), _event(event) {}

	bool Evaluate(const Date& date, const string& event) const override;

private:
	const Comparison _cmp;
	const string _event;
};

class LogicalOperationNode : public Node {
public:
	explicit LogicalOperationNode(const LogicalOperation& lop, const shared_ptr<Node>& left, const shared_ptr<Node>& right) : _lop(lop), _left(left), _right(right) {}

	bool Evaluate(const Date& date, const string& event) const override;

private:
	const LogicalOperation _lop;
	const shared_ptr<Node> _left;
	const shared_ptr<Node> _right;
};

bool CompareString(const Comparison& cmp, const string& left, const string& right);