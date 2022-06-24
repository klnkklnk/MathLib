#include "header.hpp"


int main()
{
	setlocale(LC_ALL, "Rus");
	ak::math::Matrix A(3, 4); // Система линейных уравнений (Расширенная матрица, состоящая из квадратной матрицы коэфицентов и стобца свободных членов)
	ak::math::Matrix B(3, 3);
	ak::math::Matrix C(3, 3);
	std::cout << "Введите расширенную матрицу: " << std::endl;
	std::cin >> A;
	std::cout << "Матрица А: " << std::endl << A;
	std::cout << "Введите матрицу B: " << std::endl;
	std::cin >> B;
	std::cout << "Матрица B: " << std::endl << B << std::endl;
	C = B.Inverse();
	A.SLE();
	std::cout << std::endl << "Определитель матрицы B равен: " << B.Determinant() << std::endl;
	std::cout << std::endl << "Обратная к B матрица: " << std::endl << B.Inverse() << std::endl;
	std::cout << std::endl << "Транспонированная матрица B: " << std::endl << B.Transposition() << std::endl;
	std::cout << std::endl << "Единичная матрица, полученная произведением B на обратную к ней: " << std::endl << B*C << std::endl;
	return 0;
}

