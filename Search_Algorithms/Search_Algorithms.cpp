//#include <iostream>
#include"Matrix.h"

int main(){
	size_t  x = 100;
	size_t  y = 100;
	matrix myMatrix(x, y);
	matrix myMatrix2(x, y);
	matrix addMatrix = matrix::dot(myMatrix, myMatrix2);
	//myMatrix.visualize();
	std::cerr << "Matrix1 " + std::to_string(myMatrix[1][1]) + "myMatrix2 " + std::to_string(myMatrix2[1][1]) + "addMatrix " + std::to_string(addMatrix[1][1]) << std::endl;
	cv::imshow("window", addMatrix.visualize());
	//cv::imshow("myWindow", theMat);
	cv::waitKey(10000);
	return 0;
}