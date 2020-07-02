#include "node.h"

bool EmptyNode::Evaluate(const Date& date, const string& event) const {
	return true;
}

bool DateComparisonNode::Evaluate(const Date& date, const string& event) const {
	return CompareString(_cmp, date.GetStringDate(), _date.GetStringDate());
}

bool EventComparisonNode::Evaluate(const Date& date, const string& event) const {
	return CompareString(_cmp, event, _event);
}

bool LogicalOperationNode::Evaluate(const Date& date, const string& event) const {
	switch (_lop) {
		case LogicalOperation::Or: return (_left->Evaluate(date, event) || _right->Evaluate(date, event));
		case LogicalOperation::And: return (_left->Evaluate(date, event) && _right->Evaluate(date, event));
	}
	throw logic_error("Broken logical operation");
}

bool CompareString(const Comparison& cmp, const string& left, const string& right) {
	switch (cmp) {
		case Comparison::Less: return left < right;
		case Comparison::LessOrEqual: return left <= right;
		case Comparison::Greater: return left > right;
		case Comparison::GreaterOrEqual: return left >= right;
		case Comparison::Equal: return left == right;
		case Comparison::NotEqual: return left != right;
	}
	throw logic_error("Broken comparison operation");
}