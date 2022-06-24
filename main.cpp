#include "header.hpp"


int main()
{
	setlocale(LC_ALL, "Rus");
	ak::math::Matrix A(3, 4); // ������� �������� ��������� (����������� �������, ��������� �� ���������� ������� ����������� � ������ ��������� ������)
	ak::math::Matrix B(3, 3);
	ak::math::Matrix C(3, 3);
	std::cout << "������� ����������� �������: " << std::endl;
	std::cin >> A;
	std::cout << "������� �: " << std::endl << A;
	std::cout << "������� ������� B: " << std::endl;
	std::cin >> B;
	std::cout << "������� B: " << std::endl << B << std::endl;
	C = B.Inverse();
	A.SLE();
	std::cout << std::endl << "������������ ������� B �����: " << B.Determinant() << std::endl;
	std::cout << std::endl << "�������� � B �������: " << std::endl << B.Inverse() << std::endl;
	std::cout << std::endl << "����������������� ������� B: " << std::endl << B.Transposition() << std::endl;
	std::cout << std::endl << "��������� �������, ���������� ������������� B �� �������� � ���: " << std::endl << B*C << std::endl;
	return 0;
}

