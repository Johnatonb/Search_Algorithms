#include<vector>
#include<iostream>
#include<exception>

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
	int columns = (int)0;
	int rows = (int)0;
	double determinate = NULL;
	std::vector<std::vector<double>> base;

	matrix() {

	}

	std::vector<double> operator[](int rhs) {
		return base[rhs];
	};

	void update() {
		hardCheck("SIZE");
		columns = base.size();
		rows = base[0].size();
	}

	void hardCheck(std::string check_type) {
		try {
			if (check_type == "SIZE") {
				if (base.size() > (int)0) {
					int rowsBasis = base[0].size();
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
		}
		catch (opperationException& e) {
			std::cerr << e.what() << std::endl;
		}
	}

	void hardCheck(std::string check_type, matrix comparisonMatrix) {
		try {
			update();
			comparisonMatrix.update();
			if (check_type == "DOT" || check_type == "ADD" || check_type == "SUB") {
				if (rows != comparisonMatrix.getRows() || columns != comparisonMatrix.getColumns()) {
					throw opperationException();
				}
			}
			else if (check_type == "CROSS") {
				if (columns != comparisonMatrix.getRows()) {
					throw opperationException();
				}
			}
		}
		catch (opperationException& e) {
			std::cerr << e.what() << std::endl;
		}
	}

public:
	int getRows() {
		update();
		return rows;
	}

	int getColumns() {
		update();
		return columns;
	}

	bool softCheck(std::string check_type) {
		if (check_type == "SIZE") {
			if (base.size() > (int)0) {
				int rowsBasis = base[0].size();
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
	}

	bool softCheck(std::string check_type, matrix comparisonMatrix) {
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
	}

	void pushRow( std::vector<double> addend) {
		update();
		if (addend.size() == columns) {
			base.push_back(addend);
		}
	}

	void pushColumn( std::vector<double> addend) {
		update();
		if (addend.size() == rows) {
			for (int i = 0; i < rows; i++) {
				base[i].push_back(addend[i]);

			}
		}
	}

	void dot(matrix multiplicand) {
		hardCheck("DOT", multiplicand);
		for(int i = 0; i < rows; i++) {
			for (int j = 0; j < columns; j++) {
				base[i][j] *= multiplicand[i][j];
			}
		}
	}

	static matrix dot(matrix multiplicand1, matrix multiplicand2) {
		matrix multiplier;
		multiplicand1.update();
		multiplicand2.update();
	}
};