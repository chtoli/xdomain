#pragma once
#include<iostream>
#include<string>

enum XValue {
	POS_INF,
	NEG_INF,
	NDEF
};

template<typename T>
class XDomain {
private:
	T data;
	bool isPosInf;
	bool isNegInf;

public:

	//Ctor
	XDomain();
	XDomain(const XValue& value);
	XDomain(const T& data);
	XDomain(const XDomain& other);
	//Basic Operators
	XDomain<T> operator+(const XDomain<T>& rhs) const;
	XDomain<T> operator-(const XDomain<T>& rhs) const;
	XDomain<T> operator*(const XDomain<T>& rhs) const;
	XDomain<T> operator/(const XDomain<T>& rhs) const;
	XDomain<T> operator+() const;
	XDomain<T> operator-() const;

	//Assignment
	XDomain<T>& operator=(const XValue& rhs);
	XDomain<T>& operator=(const T& rhs);
	XDomain<T>& operator=(const XDomain<T>& rhs);
	//AssignmentOperator
	XDomain<T>& operator+=(const XDomain<T>& rhs);
	XDomain<T>& operator-=(const XDomain<T>& rhs);
	XDomain<T>& operator*=(const XDomain<T>& rhs);
	XDomain<T>& operator/=(const XDomain<T>& rhs);

	//! Prefix increment operator
	XDomain<T>& operator++();
	//! Prefix decrement operator
	XDomain<T>& operator--();
	//! Posfix increment operator
	XDomain<T> operator++(int);
	//! Postfix decrement operator
	XDomain<T> operator--(int);

	//Comparison
	bool operator==(const XDomain<T>& rhs) const;
	bool operator!=(const XDomain<T>& rhs) const;
	bool operator<(const XDomain<T>& rhs) const;
	bool operator>(const XDomain<T>& rhs) const;
	bool operator<=(const XDomain<T>& rhs) const;
	bool operator>=(const XDomain<T>& rhs) const;

	//IO
	template<typename U>
	friend std::ostream& operator<< (std::ostream& os, const XDomain<U>& x);

	friend std::istream& operator>> (std::istream& is, XDomain<int>& x);
	friend std::istream& operator>> (std::istream& is, XDomain<long>& x);
	friend std::istream& operator>> (std::istream& is, XDomain<long long>& x);
	friend std::istream& operator>> (std::istream& is, XDomain<float>& x);
	friend std::istream& operator>> (std::istream& is, XDomain<double>& x);
	friend std::istream& operator>> (std::istream& is, XDomain<long double>& x);
	template<typename U>
	friend bool inStreamHelper(std::string& str, XDomain<U>& x);
};

#pragma region Constructors
template<typename T>
XDomain<T>::XDomain()
{
	data = 0;
	isPosInf = false;
	isNegInf = false;
}

template<typename T>
XDomain<T>::XDomain(const XValue& value)
{
	data = 0;
	isPosInf = value == POS_INF;
	isNegInf = value == NEG_INF;
	//NDEF case
	if (!isPosInf && !isNegInf) {
		isPosInf = true;
		isNegInf = true;
	}
}

template<typename T>
XDomain<T>::XDomain(const T& data)
{
	this->data = data;
	isPosInf = false;
	isNegInf = false;
}

template<typename T>
XDomain<T>::XDomain(const XDomain& other)
{
	data = other.data;
	isPosInf = other.isPosInf;
	isNegInf = other.isNegInf;
}
#pragma endregion

#pragma region Operators
template<typename T>
XDomain<T> XDomain<T>::operator+(const XDomain<T>& rhs) const
{
	XDomain result = *this;
	result += rhs;
	return result;
}

template<typename T>
XDomain<T> XDomain<T>::operator-(const XDomain<T>& rhs) const
{
	XDomain result = *this;
	result -= rhs;
	return result;
}

template<typename T>
XDomain<T> XDomain<T>::operator*(const XDomain<T>& rhs) const
{
	XDomain result = *this;
	result *= rhs;
	return result;
}

template<typename T>
XDomain<T> XDomain<T>::operator/(const XDomain<T>& rhs) const
{
	XDomain result = *this;
	result /= rhs;
	return result;
}

template<typename T>
XDomain<T> XDomain<T>::operator+() const {
	return *this;
}

template<typename T>
XDomain<T> XDomain<T>::operator-() const {
	//NDEF
	if (isPosInf && isNegInf) return *this;
	//Val
	if (!isPosInf && !isNegInf) return XDomain(-this->data);
	//+inf
	if (isPosInf) return XDomain(NEG_INF);
	//-inf
	if (isNegInf) return XDomain(POS_INF);
}

#pragma endregion

#pragma region Assignment
template<typename T>
XDomain<T>& XDomain<T>::operator=(const XValue& rhs) {
	data = 0;
	isPosInf = value == POS_INF;
	isNegInf = value == NEG_INF;
	//NDEF case
	if (!isPosInf && !isNegInf) {
		isPosInf = true;
		isNegInf = true;
	}
	return *this;
}

template<typename T>
XDomain<T>& XDomain<T>::operator=(const T& rhs) {
	data = rhs;
	isPosInf = false;
	isNegInf = false;

	return *this;
}

template<typename T>
XDomain<T>& XDomain<T>::operator=(const XDomain<T>& rhs) {
	if (rhs != this) {
		data = rhs.data;
		isPosInf = rhs.isPosInf;
		isNegInf = rhs.isNegInf;
	}

	return *this;
}
#pragma endregion

#pragma region AssignmentOperator

template<typename T>
XDomain<T>& XDomain<T>::operator+=(const XDomain<T>& rhs) {
	//this == val
	if (!isPosInf && !isNegInf) {
		//rhs == +inf
		if (rhs.isPosInf && !rhs.isNegInf) {
			isPosInf = true;
			isNegInf = false;
			data = 0;
			return *this;
		}
		//rhs == -inf
		if (!rhs.isPosInf && rhs.isNegInf) {
			isPosInf = false;
			isNegInf = true;
			data = 0;
			return *this;
		}
		//rhs == val
		if (!rhs.isPosInf && !rhs.isNegInf) {
			isPosInf = false;
			isNegInf = false;
			data += rhs.data;
			return *this;
		}
	}
	//this == +inf
	else if (isPosInf && !isNegInf) {
		//rhs == +inf || rhs == val
		if (rhs.isPosInf && !rhs.isNegInf || !rhs.isPosInf && !rhs.isNegInf) {
			isPosInf = true;
			isNegInf = false;
			data = 0;
			return *this;
		}
	}
	//this == -inf
	else if (!isPosInf && isNegInf) {
		//rhs == -inf || rhs == val
		if (!rhs.isPosInf && rhs.isNegInf || !rhs.isPosInf && !rhs.isNegInf) {
			isPosInf = false;
			isNegInf = true;
			data = 0;
			return *this;
		}
	}

	//=>NDEF
	isPosInf = true;
	isNegInf = true;
	data = 0;
	return *this;
}

template<typename T>
XDomain<T>&  XDomain<T>::operator-=(const XDomain<T>& rhs) {
	*this += -rhs;
	return *this;
}

template<typename T>
XDomain<T>& XDomain<T>::operator*=(const XDomain<T>& rhs) {
	//this == val
	if (!isPosInf && !isNegInf) {
		// 0*NDEF = NDEF, 0*anything else = 0
		if (data == 0) {
			isPosInf = rhs.isPosInf && rhs.isNegInf;
			isNegInf = rhs.isPosInf && rhs.isNegInf;
			return *this;
		}
		else if (data > 0) {
			//rhs == +inf
			if (rhs.isPosInf && !rhs.isNegInf) {
				isPosInf = true;
				isNegInf = false;
				data = 0;
				return *this;
			}
			//rhs == -inf
			if (!rhs.isPosInf && rhs.isNegInf) {
				isPosInf = false;
				isNegInf = true;
				data = 0;
				return *this;
			}
			//rhs == val
			if (!rhs.isPosInf && !rhs.isNegInf) {
				isPosInf = false;
				isNegInf = false;
				data *= rhs.data;
				return *this;
			}
		}
		else {
			//rhs == +inf
			if (rhs.isPosInf && !rhs.isNegInf) {
				isPosInf = false;
				isNegInf = true;
				data = 0;
				return *this;
			}
			//rhs == -inf
			if (!rhs.isPosInf && rhs.isNegInf) {
				isPosInf = true;
				isNegInf = false;
				data = 0;
				return *this;
			}
			//rhs == val
			if (!rhs.isPosInf && !rhs.isNegInf) {
				isPosInf = false;
				isNegInf = false;
				data *= rhs.data;
				return *this;
			}
		}
		
	}
	//this == +inf
	else if (isPosInf && !isNegInf) {
		//rhs == val
		if (!rhs.isPosInf && !rhs.isNegInf) {
			if (rhs.data == 0) {
				isPosInf = false;
				isNegInf = false;
			}
			else if (data > 0) {
				isPosInf = true;
				isNegInf = false;
			} else{
				isPosInf = false;
				isNegInf = true;
			}
			data = 0;
			return *this;
		}
		//rhs == +inf
		if (rhs.isPosInf && !rhs.isNegInf) {
			isPosInf = true;
			isNegInf = false;
			data = 0; 
			return *this;
		}
		//rhs == -inf
		if (rhs.isPosInf && !rhs.isNegInf) {
			isPosInf = false;
			isNegInf = true;
			data = 0;
			return *this;
		}
	}
	//this == -inf
	else if (!isPosInf && isNegInf) {
		//rhs == val
		if (!rhs.isPosInf && !rhs.isNegInf) {
			if (rhs.data == 0) {
				isPosInf = false;
				isNegInf = false;
			}
			else if (data > 0) {
				isPosInf = false;
				isNegInf = true;
			}
			else {
				isPosInf = true;
				isNegInf = false;
			}
			data = 0;
			return *this;
		}
		//rhs == +inf
		if (rhs.isPosInf && !rhs.isNegInf) {
			isPosInf = false;
			isNegInf = true;
			data = 0;
			return *this;
		}
		//rhs == -inf
		if (rhs.isPosInf && !rhs.isNegInf) {
			isPosInf = true;
			isNegInf = false;
			data = 0;
			return *this;
		}
	}

	//=>NDEF
	isPosInf = true;
	isNegInf = true;
	data = 0;
	return *this;
}


template<typename T>
XDomain<T>& XDomain<T>::operator/=(const XDomain<T>& rhs) {
	//this==val
	if (!isPosInf && !isNegInf) {
		if (data == 0) {
			//rhs== +inf,-inf, !=0
			if (!(rhs.isPosInf && rhs.isNegInf) && rhs.data != 0) {
				isPosInf = false;
				isNegInf = false;
				data = 0;
				return *this;
			}
		}
		else {
			//rhs==val
			if (!rhs.isPosInf && !rhs.isNegInf) {
				if (rhs.data == 0) {
					isPosInf = data >= 0;
					isNegInf = data < 0;
					data = 0;
					return *this;
				} 
				isPosInf = false;
				isNegInf = false;
				data /= data;
				return *this;
			}
			//rhs==+inf || rhs == -inf
			if (rhs.isPosInf && !rhs.isNegInf || !rhs.isPosInf && rhs.isNegInf) {
				isPosInf = false;
				isNegInf = false;
				data = 0;
				return *this;
			}
		}
	} 
	//this==+inf
	else if (isPosInf && !isNegInf) {
		//rhs==val
		if (!rhs.isPosInf && !rhs.isNegInf) {
			if (rhs.data > 0) {
				isPosInf = true;
				isNegInf = false;
				data = 0;
				return *this;
			}
			else if (rhs.data < 0) {
				isPosInf = false;
				isNegInf = true;
				data = 0;
				return *this;
			}
		}
	}
	//this==-inf
	else if (!isPosInf && isNegInf) {
		//rhs==val
		if (!rhs.isPosInf && !rhs.isNegInf) {
			if (rhs.data > 0) {
				isPosInf = false;
				isNegInf = true;
				data = 0;
				return *this;
			}
			else if (rhs.data < 0) {
				isPosInf = true;
				isNegInf = false;
				data = 0;
				return *this;
			}
		}
	}

	//=>NDEF
	isPosInf = true;
	isNegInf = true;
	data = 0;
	return *this;
}

#pragma endregion

#pragma region Incremendt/Decrement

template<typename T>
XDomain<T>& XDomain<T>::operator++() {
	if (!isPosInf && !isNegInf) data++;
	return *this;
}

template<typename T>
XDomain<T>& XDomain<T>::operator--() {
	if (!isPosInf && !isNegInf) data--;
	return *this;
}

template<typename T>
XDomain<T> XDomain<T>::operator++(int) {
	XDomain result = *this;
	(*this++);
	return result;
}

template<typename T>
XDomain<T> XDomain<T>::operator--(int) {
	XDomain result = *this;
	(*this--);
	return result;
}

#pragma endregion

#pragma region Comparison
template <typename T>
bool XDomain<T>::operator==(const XDomain<T>& rhs) const {
	return data == rhs.data && isPosInf == rhs.isPosInf && isNegInf == rhs.isNegInf;
}

template <typename T>
bool XDomain<T>::operator!=(const XDomain<T>& rhs) const {
	return !(data == rhs);
}

template <typename T>
bool XDomain<T>::operator<(const XDomain<T>& rhs) const {
	//NDEF
	if (isPosInf && isNegInf || rhs.isPosInf && rhs.isNegInf) throw ComparableException();
	//-inf < -inf
	if (!isPosInf && isNegInf && !rhs.isPosInf && rhs.isNegInf) throw ComparableException();
	//+inf < +inf
	if (isPosInf && !isNegInf && rhs.isPosInf && !rhs.isNegInf) throw ComparableException();

	//-inf
	if (!isPosInf && isNegInf) return true;
	//+inf
	if (isPosInf && !isNegInf) return false;

	//rhs -inf
	if (!rhs.isPosInf && rhs.isNegInf) return false;
	//rhs +inf
	if (rhs.isPosInf && !rhs.isNegInf) return true;
	return data < rhs.data;
}

template <typename T>
bool XDomain<T>::operator>(const XDomain<T>& rhs) const {
	//NDEF
	if (isPosInf && isNegInf || rhs.isPosInf && rhs.isNegInf) throw ComparableException();
	//-inf > -inf
	if (!isPosInf && isNegInf && !rhs.isPosInf && rhs.isNegInf) throw ComparableException();
	//+inf > +inf
	if (isPosInf && !isNegInf && rhs.isPosInf && !rhs.isNegInf) throw ComparableException();

	//-inf
	if (!isPosInf && isNegInf) return false;
	//+inf
	if (isPosInf && !isNegInf) return true;

	//rhs -inf
	if (!rhs.isPosInf && rhs.isNegInf) return true;
	//rhs +inf
	if (rhs.isPosInf && !rhs.isNegInf) return false;
	return data > rhs.data;
}

template <typename T>
bool XDomain<T>::operator<=(const XDomain<T>& rhs) const {
	return *this < rhs || *this == rhs;
}

template <typename T>
bool XDomain<T>::operator>=(const XDomain<T>& rhs) const {
	return *this > rhs || *this == rhs;
}

#pragma endregion

#pragma region friends

template<typename U>
std::ostream& operator<< (std::ostream& os, const XDomain<U>& x) {

	if (x.isNegInf && x.isPosInf) {
		os << "NDEF";
	}
	else if (x.isNegInf && !x.isPosInf)
	{
		os << "-INF";
	}
	else if (!x.isNegInf && x.isPosInf)
	{
		os << "+INF";
	}
	else {
		os << x.data;
	}
	return os;
}

template<typename U>
bool inStreamHelper(std::string& str, XDomain<U>& x)
{
	if (str == "+INF") {
		x.data = 0;
		x.isNegInf = false;
		x.isPosInf = true;
		return true;
	}
	else if (str == "-INF")
	{
		x.data = 0;
		x.isNegInf = true;
		x.isPosInf = false;
		return true;
	}
	else if (str == "NDEF") {
		x.data = 0;
		x.isNegInf = true;
		x.isPosInf = true;
		return true;
	}
	return false;
}


std::istream& operator>> (std::istream& is, XDomain<int>& x) {

	std::string str;
	is >> str;
	if (!inStreamHelper(str, x)) {
		try {
			x.data = std::stoi(str);
		}
		catch (std::invalid_argument& e) {
			throw;
		}
		catch (std::out_of_range& e) {
			throw;
		}

		x.isNegInf = false;
		x.isPosInf = false;
	}
	return is;
}

std::istream& operator>> (std::istream& is, XDomain<long>& x) {

	std::string str;
	is >> str;
	if (!inStreamHelper(str, x)) {
		try {
			x.data = std::stol(str);
		}
		catch (std::invalid_argument& e) {
			throw;
		}
		catch (std::out_of_range& e) {
			throw;
		}

		x.isNegInf = false;
		x.isPosInf = false;
	}
	return is;
}

std::istream& operator>> (std::istream& is, XDomain<long long>& x) {

	std::string str;
	is >> str;
	if (!inStreamHelper(str, x)) {
		try {
			x.data = std::stoll(str);
		}
		catch (std::invalid_argument& e) {
			throw;
		}
		catch (std::out_of_range& e) {
			throw;
		}

		x.isNegInf = false;
		x.isPosInf = false;
	}
	return is;
}

std::istream& operator>> (std::istream& is, XDomain<float>& x) {

	std::string str;
	is >> str;
	if (!inStreamHelper(str, x)) {
		try {
			x.data = std::stof(str);
		}
		catch (std::invalid_argument& e) {
			throw;
		}
		catch (std::out_of_range& e) {
			throw;
		}

		x.isNegInf = false;
		x.isPosInf = false;
	}
	return is;
}

std::istream& operator>> (std::istream& is, XDomain<double>& x) {

	std::string str;
	is >> str;
	if (!inStreamHelper(str, x)) {
		try {
			x.data = std::stod(str);
		}
		catch (std::invalid_argument& e) {
			throw;
		}
		catch (std::out_of_range& e) {
			throw;
		}

		x.isNegInf = false;
		x.isPosInf = false;
	}
	return is;
}

std::istream& operator >> (std::istream& is, XDomain<long double>& x) {

	std::string str;
	is >> str;
	if (!inStreamHelper(str, x)) {
		try {
			x.data = std::stold(str);
		}
		catch (std::invalid_argument& e) {
			throw;
		}
		catch (std::out_of_range& e) {
			throw;
		}

		x.isNegInf = false;
		x.isPosInf = false;
	}
	return is;
}



#pragma endregion Contains Implementation of IOStream

#pragma region TypeDefs
typedef XDomain<int> Xint;
typedef XDomain<long> Xlong;
typedef XDomain<long long> Xlonglong;
typedef XDomain<float> Xfloat;
typedef XDomain<double> Xdouble;
typedef XDomain<long double> Xlongdouble;
#pragma endregion Some shorthand notation

class ComparableException : public std::exception
{
	const char* what() const throw() { return "Comparison Failed\n"; }
};
