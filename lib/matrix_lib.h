#pragma once

#include <iostream>
#include <map>

template<typename T, T DEF>
class Value {
public:
	Value(std::map<size_t, std::map<size_t, T>>* matrix, size_t x, size_t y) {
		matrix_ = matrix;
		x_ = x;
		y_ = y;

		auto itX = matrix_->find(x_);
		if (itX != matrix_->end()) {
			if (itX->second.find(y_) != itX->second.end()) {
				value_ = (*matrix_)[x_][y_];
				return;
			}
		}
		value_ = DEF;
	}

	Value& operator=(const T& value) {
		(*matrix_)[x_][y_] = value;
		return *this;
	}

	bool operator==(const T& value) const {
		return value_ == value;
	}

	friend std::ostream& operator<< (std::ostream& out, const Value& value)
	{
		out << value.value_;
		return out;
	}

private:
	std::map<size_t, std::map<size_t, T>>* matrix_;
	size_t x_;
	size_t y_;
	T value_;
};

template<typename T, T DEF>
class Helper {
public:
	Helper(std::map<size_t, std::map<size_t, T>>* matrix, size_t x) : matrix_(matrix), x_(x) {}

	Value<T, DEF> operator[](const size_t index) {
		return Value<T, DEF>(matrix_, x_, index);
	}

private:
	std::map<size_t, std::map<size_t, T>>* matrix_;
	size_t x_;
};

template<typename T, T DEF>
class HelperIterator {
	using ItLine = typename std::map<size_t, std::map<size_t, T>>::iterator;
	using ItColumn = typename std::map<size_t, T>::iterator;
public:
	HelperIterator(std::map<size_t, std::map<size_t, T>>* matrix, bool isBegin) : matrix_(matrix) {
		if (isBegin) {
			currentLine = matrix->begin();
			currentColumn = currentLine->second.begin();
		}
		else {
			currentLine = matrix->end();
		}
	}

	auto operator*() const {
		return std::make_tuple(currentLine->first, currentColumn->first, currentColumn->second);
	}

	auto const& operator++() {
		currentColumn++;
		if (currentColumn == currentLine->second.end()) {
			currentLine++;
			if (currentLine != matrix_->end()) {
				currentColumn = currentLine->second.begin();
			}
		}

		return *this;
	}

	bool operator!=(HelperIterator const& other) const
	{
		return currentLine != other.currentLine;
	}

private:
	std::map<size_t, std::map<size_t, T>>* matrix_;
	ItLine currentLine;
	ItColumn currentColumn;
};

template<typename T, T DEF>
class Matrix {
public:
	Matrix() {}
	~Matrix() = default;

	Helper<T, DEF> operator[](size_t index) {
		return typename Helper<T, DEF>::Helper(&data_, index);
	}

	size_t size() const {
		size_t size = 0;

		for (const auto& line : data_)
			size += line.second.size();

		return size;
	}

	HelperIterator<T, DEF> begin() {
		return typename HelperIterator<T, DEF>::HelperIterator(&data_, true);
	}

	HelperIterator<T, DEF> end() {
		return typename HelperIterator<T, DEF>::HelperIterator(&data_, false);
	}

private:
	std::map<size_t, std::map<size_t, T>> data_;
};