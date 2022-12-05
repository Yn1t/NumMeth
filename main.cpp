#include <iostream>
#include <vector>
#include <exception>
#include <string>
#include <fstream>
using namespace std;

class Matrix {

public:
	vector<vector<float>> matrix;

	Matrix operator* (Matrix m2);
	Matrix& operator= (Matrix m2);
	Matrix& swap(const int& i, const int& j);
	void readMatrix(const string& file_name);
	friend ostream& operator<< (ostream& out, const Matrix& m);
};

void task1();

int main()
{
	task1();
	return 0;
}

void task1()
{
	Matrix m;
	m.readMatrix("matrix.txt");
	float determenant = 1;

	for (int j = 0; j < m.matrix[0].size() - 1; ++j)
	{
		for (int i = j + 1; i < m.matrix.size(); ++i)
		{
			int temp = j;

			if (m.matrix[i][j] == 0)
				continue;

			if (m.matrix[temp][j] == 0)
			{
				m.swap(temp, i);
			}
			else
			{
				float multiplier = -1 * m.matrix[i][j] / m.matrix[temp][j];
				for (int index = j; index < m.matrix[i].size(); ++index)
				{
					m.matrix[i][index] += m.matrix[temp][index] * multiplier;
				}
			}
		}
	}

	for (int i = 0; i < m.matrix.size(); ++i)
	{
		determenant *= m.matrix[i][i];
	}

	float* sol = new float[m.matrix.size()];

	for (int i = m.matrix.size() - 1; i >= 0; i--) {
		float temp = 0;
		for (int j = i + 1; j < m.matrix.size(); j++) {
			temp += m.matrix[i][j] * sol[j];
		}
		sol[i] = (m.matrix[i][m.matrix.size()] - temp) / m.matrix[i][i];
	}


	cout << "Solution : ";
	for (int i = 0; i < m.matrix.size(); ++i)
	{
		cout << "x_1 = " << sol[i] << ";\t";
	}
	cout << endl;

	cout << "Determenant : " << determenant << endl;

	cout << "Matrix : " << endl;
	cout << m;

}

Matrix Matrix::operator*(Matrix m2)
{
	if (this->matrix[0].size() != m2.matrix.size())
		throw exception("Multiply error");

	Matrix result;

	for (int i = 0; i < this->matrix[0].size(); ++i)
	{
		vector<float> vec;
		result.matrix.push_back(vec);
		for (int j = 0; j < m2.matrix.size(); ++j)
		{
			result.matrix[0].push_back(0);
		}
	}

	for (int i = 0; i < result.matrix.size(); ++i)
	{
		for (int j = 0; j < result.matrix[i].size(); ++j)
		{

		}
	}

	return result;
}

Matrix& Matrix::operator=(Matrix m2)
{
	this->matrix.clear();

	for (int i = 0; i < m2.matrix.size(); ++i)
	{
		vector<float> vec;
		for (int j = 0; j < m2.matrix[i].size(); ++j)
		{
			vec.push_back(m2.matrix[i][j]);
		}
		this->matrix.push_back(vec);
	}

	return *this;
}

Matrix& Matrix::swap(const int& i, const int& j)
{
	float temp;

	for (int index = 0; index < this->matrix[0].size(); ++index)
	{
		temp = this->matrix[i][index];
		this->matrix[i][index] = this->matrix[j][index];
		this->matrix[j][index] = temp;
	}

	return *this;
}

void Matrix::readMatrix(const string& file_name)
{
	ifstream file_in(file_name);
	float temp;
	int x, y;

	file_in >> y;
	file_in >> x;

	for (int i = 0; i < y; ++i)
	{
		vector<float> vec;
		this->matrix.push_back(vec);
		for (int j = 0; j < x; ++j)
		{
			file_in >> temp;
			this->matrix[i].push_back(temp);
		}
	}

}

ostream& operator<<(ostream& out, const Matrix& m)
{
	for (int i = 0; i < m.matrix.size(); ++i)
	{
		for (int j = 0; j < m.matrix[i].size(); ++j)
		{
			out << m.matrix[i][j] << "\t\t";
		}
		out << endl;
	}

	return out;
}
