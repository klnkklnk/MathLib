#pragma once
#include <iostream>

namespace ak::math
{
	class Matrix
	{
	public:

		//Конструктор
		Matrix(int n, int m)
		{
			//std::cout << "Constructor" << std::endl;
			m_n = n;
			m_m = m;
			m_x = new float[m_m];
			m_mat = new float* [m_n];
			for (int i = 0; i < m_n; i++)
				m_mat[i] = new float[m_m];
		}

		//Деструктор
		~Matrix()
		{
			//std::cout << "Destructor" << std::endl;
			for (int i = 0; i < m_n; i++)
				delete[] m_mat[i];
			delete m_mat;
			delete [] m_x;
		}

		//Конструктор копирования
		Matrix(const Matrix& mat)
		{
			//std::cout << "Copy constructor" << std::endl;

			m_n = mat.m_n;
			m_m = mat.m_m;

			m_mat = new float* [m_n];
			for (int i = 0; i < m_n; i++)
				m_mat[i] = new float[m_m];

			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = mat.m_mat[i][j];
		}
		//Присваивание
		Matrix& operator=(const Matrix& mat)
		{
			//std::cout << "Operator=" << std::endl;

			m_n = mat.m_n;
			m_m = mat.m_m;

			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					m_mat[i][j] = mat.m_mat[i][j];

			return *this;
		}
		//Сложение
		Matrix operator+(const Matrix& mat)
		{
			//std::cout << "Operator+" << std::endl;
			Matrix tmp(m_n, m_m);

			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					tmp.m_mat[i][j] = m_mat[i][j] + mat.m_mat[i][j];

			return tmp;
		}
		//Вычитание
		Matrix operator-(const Matrix& mat)
		{
			//std::cout << "Operator-" << std::endl;
			Matrix tmp(m_n, m_m);

			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					tmp.m_mat[i][j] = m_mat[i][j] - mat.m_mat[i][j];

			return tmp;
		}
		//Умножение
		Matrix operator*(const Matrix& mat)
		{
			//std::cout << "Operator*" << std::endl;
			Matrix tmp(m_n, mat.m_m);
			float s = 0;
			if (m_m != mat.m_n)
			{
				std::cout << "Операция не поддерживается";
				for (int i = 0; i < m_n; i++)
					for (int j = 0; j < mat.m_m; j++)
						tmp.m_mat[i][j] = 0;
				return tmp;
			}
			else
			{
				for (int i = 0; i < m_n; i++)
				{
					for (int j = 0; j < mat.m_m; j++)
					{
						s = 0;
						for (int k = 0; k < mat.m_n; k++)
							s += m_mat[i][k] * mat.m_mat[k][j];
						tmp.m_mat[i][j] = s;
					}
				}
				return tmp;
			}
		}
		// Метод для нахождения определителя
		float Determinant() // Является рекурсивной функцией
		{
			float D;
			if (m_n == m_m)
			{
				if (m_n == 1)
				{
					D = m_mat[0][0];
					return D;
				}
				else
				{
					Matrix tmp(m_n - 1, m_m - 1);
					float k;
					for (int i = 1; i < m_n; i++)
					{
						k = m_mat[i][0] / m_mat[0][0];
						for (int j = 0; j < m_m - 1; j++)
						{
							tmp.m_mat[i - 1][j] = m_mat[i][j + 1] - k * m_mat[0][j + 1];
						}
					}
					return m_mat[0][0] * tmp.Determinant();
				}
			}
			else
				throw std::invalid_argument("The matrix is not square");
		}

		//Метод нахождения обратной матрицы
		Matrix Inverse()
		{
			Matrix tmp(m_n, m_m);
			float D;
			D = Determinant();
			if ((D != 0) && (m_n == m_m))
			{
				for (int i = 0; i < m_n; i++) // Заполнение обратной матрицы
					for (int j = 0; j < m_m; j++)
					{
						int x = 0;
						int y = 0;
						Matrix A(m_n - 1, m_m - 1); // Минор порядка N-1
						for (int k = 0; k < m_n; k++) // Заполнение минора
						{
							for (int l = 0; l < m_n; l++)
								if ((k != j) && (l != i))
								{
									A.m_mat[x][y] = m_mat[k][l];
									y++;
								}
							if (k != j)
								x++;
							y = 0;
						}
						if ((i + j) % 2 == 0)
							tmp.m_mat[i][j] = A.Determinant() / D; // (-1)^(i+j) * A(j,i) / D
						else tmp.m_mat[i][j] = -1 * A.Determinant() / D;

					}
				return tmp;
			}
			else
				throw std::invalid_argument("The matrix is not square or determinant = 0");
		}

		Matrix Transposition() // Транспонирование матрицы
		{
			Matrix tmp(m_m, m_n);
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					tmp.m_mat[j][i] = m_mat[i][j];
			return tmp;
		}

		void SLE() // Приводит матрицу, составленную из коэфицентов, к диагональному виду 
		{
			Matrix tmp(m_n, m_m - 1);
			Matrix tmp2(m_n, 1);
			if (tmp.m_n == tmp.m_m)
			{
				for (int i = 0; i < m_n; i++)
				{
					for (int j = 0; j < m_m - 1; j++)
						tmp.m_mat[i][j] = m_mat[i][j];
					tmp2.m_mat[i][0] = m_mat[i][m_m - 1];
				}

				float k;  // Нули под главной диагональю 
				for (int l = 1; l < tmp.m_n; l++)
				{
					for (int i = l; i < tmp.m_n; i++)
					{
						k = tmp.m_mat[i][l - 1] / tmp.m_mat[l - 1][l - 1];
						for (int j = l - 1; j < tmp.m_m; j++)
						{
							tmp.m_mat[i][j] -= k * tmp.m_mat[l - 1][j];
						}
						tmp2.m_mat[i][0] -= k * tmp2.m_mat[l - 1][0];
					}
				}

				for (int l = tmp.m_n - 1; l > 0; l--) // Нули над главной диагональю 
				{
					for (int i = l; i > 0; i--)
					{
						k = tmp.m_mat[i - 1][l] / tmp.m_mat[l][l];
						for (int j = l; j > 0; j--)
						{
							tmp.m_mat[i - 1][j] -= k * tmp.m_mat[l][j];
						}
						tmp2.m_mat[i - 1][0] -= k * tmp2.m_mat[l][0];
					}
				}
				std::cout << std::endl << "Решение системы: " << std::endl;
				for (int i = 0; i < m_m - 1; i++)
				{
					m_x[i] = tmp2.m_mat[i][0] / tmp.m_mat[i][i];
					std::cout << "x" << i + 1 << " = " << m_x[i] << std::endl;
				}
			}
			else
				throw std::invalid_argument("The matrix is not square");
		}

		float getSolution(int n)
		{
			return m_x[n-1];
		}

		friend std::istream& operator>>(std::istream& in, Matrix& mat);
		friend std::ostream& operator<<(std::ostream& out, const Matrix& mat);

	private:
		int m_n, m_m;
		float** m_mat;
		float* m_x = nullptr;
	};

	std::istream& operator>>(std::istream& in, Matrix& mat)
	{
		for (int i = 0; i < mat.m_n; i++)
			for (int j = 0; j < mat.m_m; j++)
				in >> mat.m_mat[i][j];
		return in;
	}

	std::ostream& operator<<(std::ostream& out, const Matrix& mat)
	{
		out << "Матрица " << mat.m_n << "x" << mat.m_m << std::endl;
		for (int i = 0; i < mat.m_n; i++)
		{
			for (int j = 0; j < mat.m_m; j++)
				out << floor(mat.m_mat[i][j] * 100) / 100 << "\t\t";
			out << std::endl;
		}
		return out;
	}
}


