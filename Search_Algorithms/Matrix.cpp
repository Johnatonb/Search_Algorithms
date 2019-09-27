#include<vector>
#include<iostream>
#include<exception>
#include<string>
#include"Matrix.h"
#include<opencv2/core/core.hpp>
#include<opencv2/highgui/highgui.hpp>

void matrix::update()
{
	hardCheck("SIZE");
	columns = base.size();
	rows = base[0].size();
}

void matrix::hardCheck(std::string check_type) {
	try {
		if (check_type == "SIZE") {
			if (base.size() > (int)0) {
				size_t rowsBasis = base[0].size();
				for (int i = 1; i < base.size(); i++) {
					if (base[i].size() != rowsBasis) {
						throw sizeException();
					}
				}
			}
		}
		else if (check_type == "DET") {
			if (rows != columns) {
				throw opperationException();
			}
		}
		else if (check_type == "INV") {
			if (rows != columns || determinate == NULL || determinate == 0) {
				throw opperationException();
			}
		}
	}
	catch (sizeException& e) {
		std::cerr << e.what() << std::endl;
		std::exit(-1);
	}
	catch (opperationException& e) {
		std::cerr << e.what() << std::endl;
		std::exit(-1);
	}
}

void matrix::hardCheck(std::string check_type, matrix comparisonMatrix) {
	try {
		update();
		comparisonMatrix.update();
		if (check_type == "DOT" || check_type == "ADD" || check_type == "SUB") {
			if (rows != comparisonMatrix.rows || columns != comparisonMatrix.columns) {
				throw opperationException();
			}
		}
		else if (check_type == "CROSS") {
			if (columns != comparisonMatrix.rows) {
				throw opperationException();
			}
		}
	}
	catch (opperationException& e) {
		std::cerr << e.what() << std::endl;
		std::exit(-1);
	}
}

void matrix::hardCheckMatrix(std::string check_type, matrix checkee) {
	try {
		if (check_type == "SIZE") {
			if (checkee.base.size() > (int)0) {
				size_t rowsBasis = checkee.base[0].size();
				for (int i = 1; i < checkee.base.size(); i++) {
					if (checkee.base[i].size() != rowsBasis) {
						throw sizeException();
					}
				}
			}
		}
		else if (check_type == "DET") {
			if (checkee.rows != checkee.columns) {
				throw opperationException();
			}
		}
		else if (check_type == "INV") {
			if (checkee.rows != checkee.columns || checkee.determinate == NULL || checkee.determinate == 0) {
				throw opperationException();
			}
		}
	}
	catch (sizeException& e) {
		std::cerr << e.what() << std::endl;
		std::exit(-1);
	}
	catch (opperationException& e) {
		std::cerr << e.what() << std::endl;
		std::exit(-1);
	}
}

void matrix::hardCheckMatrices(std::string check_type, matrix checkee1, matrix checkee2) {
	try {
		checkee1.update();
		checkee2.update();
		if (check_type == "DOT" || check_type == "ADD" || check_type == "SUB") {
			if (checkee1.rows != checkee2.rows || checkee1.columns != checkee2.columns) {
				throw opperationException();
			}
		}
		else if (check_type == "CROSS") {
			if (checkee1.columns != checkee2.rows) {
				throw opperationException();
			}
		}
	}
	catch (opperationException& e) {
		std::cerr << e.what() << std::endl;
		std::exit(-1);
	}
}

matrix::matrix() {

}

matrix::matrix(size_t rowCount, size_t columnCount) {
	for (int i = 0; i < rowCount; i++) {
		base.push_back(std::vector<double>(columnCount, (double).75));
	}
	update();
}

std::vector<double> &matrix::operator[](int rhs) {
	return base[rhs];
};

matrix matrix::operator+(matrix rhs) {
	return matrix::add(*this, rhs);
}

void matrix::operator+=(matrix rhs) {
	this->add(rhs);
}

matrix matrix::operator-(matrix rhs) {
	return matrix::sub(*this, rhs);
}

void matrix::operator-=(matrix rhs) {
	this->sub(rhs);
}

size_t matrix::getRows() {
	update();
	return rows;
}

size_t matrix::getColumns() {
	update();
	return columns;
}

bool matrix::softCheck(std::string check_type) {
	if (check_type == "SIZE") {
		if (base.size() > (int)0) {
			size_t rowsBasis = base[0].size();
			for (int i = 1; i < base.size(); i++) {
				if (base[i].size() != rowsBasis) {
					return false;
				}
			}
		}
	}
	else if (check_type == "DET") {
		if (rows != columns) {
			return false;
		}
	}
	else if (check_type == "INV") {
		if (rows != columns || determinate == NULL || determinate == 0) {
			return false;
		}
	}
	return true;
}

bool matrix::softCheck(std::string check_type, matrix comparisonMatrix) {
	update();
	if (check_type == "DOT" || check_type == "ADD" || check_type == "SUB") {
		if (rows != comparisonMatrix.getRows() || columns != comparisonMatrix.getColumns()) {
			return false;
		}
	}
	else if (check_type == "CROSS") {
		if (columns != comparisonMatrix.getRows()) {
			return false;
		}
	}
	return true;
}

void matrix::pushRow(std::vector<double> addend) {
	update();
	if (addend.size() == columns) {
		base.push_back(addend);
	}
}

void matrix::pushColumn(std::vector<double> addend) {
	update();
	if (addend.size() == rows) {
		for (int i = 0; i < rows; i++) {
			base[i].push_back(addend[i]);

		}
	}
}

template <class T>
void matrix::scalarMult(T scalar) {
	update();
	hardCheck("SIZE");
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			base[i][j] *= scalar;
		}
	}
}

template <class T>
static matrix matrix::scalarMult(T scalar, matrix multiplicand) {
	multiplicand.update();
	matrix::hardCheckMatrix("SIZE", multiplicand);
	matrix multiplier(multiplicand.rows, multiplicand.columns);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			multiplier[i][j] *= scalar;
		}
	}
}

void matrix::add(matrix multiplicand) {
	hardCheck("ADD", multiplicand);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			base[i][j] += multiplicand[i][j];
		}
	}
	update();
}

matrix matrix::add(matrix multiplicand1, matrix multiplicand2) {
	matrix::hardCheckMatrices("ADD", multiplicand1, multiplicand2);
	matrix multiplier(multiplicand1.rows, multiplicand1.columns);
	std::cout << "Hello" << std::endl;
	for (int i = 0; i < multiplicand1.rows; i++) {
		for (int j = 0; j < multiplicand1.columns; j++) {
			multiplier[i][j] = (multiplicand1[i][j] + multiplicand2[i][j]);
		}
	}
	multiplier.update();
	return multiplier;
}

void matrix::sub(matrix multiplicand) {
	hardCheck("SUB", multiplicand);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			base[i][j] -= multiplicand[i][j];
		}
	}
	update();
}

matrix matrix::sub(matrix multiplicand1, matrix multiplicand2) {
	matrix::hardCheckMatrices("SUB", multiplicand1, multiplicand2);
	matrix multiplier(multiplicand1.rows, multiplicand1.columns);
	for (int i = 0; i < multiplicand1.rows; i++) {
		for (int j = 0; j < multiplicand1.columns; j++) {
			multiplier[i][j] = multiplicand1[i][j] - multiplicand2[i][j];
		}
	}
	multiplier.update();
	return multiplier;
}

void matrix::dot(matrix multiplicand) {
	hardCheck("DOT", multiplicand);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			base[i][j] *= multiplicand[i][j];
		}
	}
	update();
}

matrix matrix::dot(matrix multiplicand1, matrix multiplicand2) {
	matrix::hardCheckMatrices("DOT", multiplicand1, multiplicand2);
	matrix multiplier(multiplicand1.rows, multiplicand1.columns);
	for (int i = 0; i < multiplicand1.rows; i++) {
		for (int j = 0; j < multiplicand1.columns; j++) {
			multiplier[i][j] = multiplicand1[i][j] * multiplicand2[i][j];
		}
	}
	multiplier.update();
	return multiplier;
}

void matrix::cross(matrix multiplicand) {
	hardCheck("CROSS", multiplicand);
	matrix multiplier(rows, multiplicand.columns);
	for (int i = 0; i < multiplier.rows; i++) {
		for (int j = 0; j < multiplier.columns; j++) {
			double k = 0;
			for (int l = 0; l < columns; l++) {
				k += base[i][l] * multiplicand[l][j];
			}
			multiplier[i][j] = k;
		}
	}
	base = multiplier.base;
	update();
}

matrix matrix::cross(matrix multiplicand1, matrix multiplicand2) {
	matrix::hardCheckMatrices("CROSS", multiplicand1, multiplicand2);
	matrix multiplier(multiplicand1.rows, multiplicand2.columns);
	for (int i = 0; i < multiplier.rows; i++) {
		for (int j = 0; j < multiplier.columns; j++) {
			double k = 0;
			for (int l = 0; l < multiplicand1.columns; l++) {
				k += multiplicand1[i][l] * multiplicand2[l][j];
			}
			multiplier[i][j] = k;
		}
	}
	return multiplier;
}

cv::Mat matrix::visualize() {
	cv::Mat visualization(static_cast<int>(rows), static_cast<int>(columns), CV_64F);
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < columns; j++) {
			visualization.at<double>(i, j) = ((base[i][j] > 1) ? 0 : (base[i][j] * -1 + 1));
		}
	}
	return visualization;
}