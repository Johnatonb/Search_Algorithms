#pragma once
#include<vector>
#include<iostream>
#include<exception>
#include<string>
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

struct sizeException : public std::exception {
	const char * what() const throw () {
		return "Matrix size is invlaid!";
	}
};

struct opperationException : public std::exception {
	const char * what() const throw () {
		return "Matrix sizes are invlaid for this opperation!";
	}
};

class matrix {
private:
	size_t columns = (size_t)0;
	size_t rows = (size_t)0;
	double determinate = NULL;
	std::vector<std::vector<double>> base;

	void update();

	void hardCheck(std::string check_type);

	void hardCheck(std::string check_type, matrix comparisonMatrix);

	static void hardCheckMatrix(std::string check_type, matrix checkee);

	static void hardCheckMatrices(std::string check_type, matrix checkee1, matrix checkee2);

public:
	matrix();

	matrix(size_t rowCount, size_t columnCount);

	std::vector<double> &operator[](int rhs);

	matrix operator+(matrix rhs);

	void operator+=(matrix rhs);

	matrix operator-(matrix rhs);

	void operator-=(matrix rhs);

	size_t getRows();

	size_t getColumns();

	bool softCheck(std::string check_type);

	bool softCheck(std::string check_type, matrix comparisonMatrix);

	void pushRow(std::vector<double> addend);

	void pushColumn(std::vector<double> addend);

	template <class T>
	void scalarMult(T scalar);

	template <class T>
	static matrix scalarMult(T scalar, matrix multiplicand);

	void add(matrix multiplicand);

	static matrix add(matrix multiplicand1, matrix multiplicand2);

	void sub(matrix multiplicand);

	static matrix sub(matrix multiplicand1, matrix multiplicand2);
	
	void dot(matrix multiplicand);

	static matrix dot(matrix multiplicand1, matrix multiplicand2);

	void cross(matrix multiplicand);

	static matrix cross(matrix multiplicand1, matrix multiplicand2);

	cv::Mat visualize();
};