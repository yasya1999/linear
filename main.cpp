#include <iostream>
#include <vector>

using namespace std;


class Vector3D {
private:
    double a, b, c;
public:
    Vector3D() {
        this->a = 0;
        this->b = 0;
        this->c = 0;
    }
    
    Vector3D(double a, double b, double c) : a(a), b(b), c(c) {};
    
    Vector3D& operator = (const Vector3D &other) {
        this->a = other.a;
        this->b = other.b;
        this->c = other.c;
        
        return *this;
    }
    
    Vector3D(const Vector3D &other) {
        (*this) = other;
    }
    
    friend Vector3D operator * (double, Vector3D);
    friend Vector3D operator * (Vector3D, double);
    
    Vector3D operator + (const Vector3D &other) {
        return Vector3D(this->a + other.a, this->b + other.b, this->c + other.c);
    }
    
    Vector3D operator * (const Vector3D &other) {
        return Vector3D(this->a * other.a, this->b * other.b, this->c * other.c);
    }
    
    Vector3D operator - (const Vector3D &other) {
        return *this + (other * (-1));
    }
    
    
    double get_a() const {
        return a;
    }
    
    double get_b() const {
        return b;
    }
    
    double get_c() const {
        return c;
    }
    
    void print() {
        cout << a << " " << b << " " << c;
    }
    
};

Vector3D operator * (double numb, Vector3D right) {
    return Vector3D(right.a * numb, right.b * numb, right.c * numb);
}

Vector3D operator * (Vector3D left, double numb) {
    return Vector3D(left.a * numb, left.b * numb, left.c * numb);
}

////////////////////////////////////////////////////////

class Matrix3D {
private:
    vector<vector<double> > matrix;
public:
    Matrix3D() {
        for (int i = 0; i < 3; i++) {
            vector<double> temp;
            for (int j = 0; j <3; j++) {
                temp.push_back(0);
            }
            this->matrix.push_back(temp);
        }
    }
    
    Matrix3D(istream &is) {
        for (int i = 0; i < 3; i++) {
            vector<double> temp;
            for (int j = 0; j < 3; j++) {
                double val;
                is >> val;
                temp.push_back(val);
            }
            matrix.push_back(temp);
        }
    }
    
    ~Matrix3D() {
        this->matrix.erase(this->matrix.begin());
    }
    
    //гарантируется, что любая матрица  уже размера 3х3
    Matrix3D operator = (const Matrix3D &other) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                this->matrix[i][j] = other.matrix[i][j];
            }
        }
        return (*this);
    }
    
    double det() {
        double a, b, c;
        a = this->matrix[0][0] * (this->matrix[1][1] * this->matrix[2][2] - this->matrix[1][2] * this->matrix[2][1]);
        b = this->matrix[0][1] * (this->matrix[1][0] * this->matrix[2][2] - this->matrix[1][2] * this->matrix[2][0]);
        c = this->matrix[0][2] * (this->matrix[1][0] * this->matrix[2][1] - this->matrix[1][1] * this->matrix[2][0]);
        
        return a - b + c;
    }
    
    void print(ostream &os) {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                os << "matrix[" << i << "][" << j << "] = " << matrix[i][j] << endl;
            }
            os << endl;
        }
    }
    
    
    friend Matrix3D operator * (double numb, const Matrix3D &other);
    friend Matrix3D operator * (const Matrix3D &other, double numb);
    
    Matrix3D operator + (const Matrix3D &other) {
        Matrix3D *output = new Matrix3D();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                output->matrix[i][j] = this->matrix[i][j] + other.matrix[i][j];
            }
        }
        return *output;
    }
    
    Matrix3D operator - (const Matrix3D &other) {
        return *this + (other * (-1));
    }
    
    Matrix3D operator * (const Matrix3D &other) {
        Matrix3D *output = new Matrix3D();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j <3; j++) {
                double c = 0;
                for (int k = 0; k < 3; k++) {
                    c += this->matrix[i][k] * other.matrix[k][i];
                }
                output->matrix[i][j] = c;
            }
        }
        return *output;
    }
    
    // так как матрица 3х3 умножается на вектор 3х1, то результатом будет матрица 3х1 => то есть вектор
    Vector3D operator * (const Vector3D &v) {
        double a = this->matrix[0][0] * v.get_a() + this->matrix[0][1] * v.get_b() + this->matrix[0][2] * v.get_c();
        double b = this->matrix[1][0] * v.get_a() + this->matrix[1][1] * v.get_b() + this->matrix[1][2] * v.get_c();
        double c = this->matrix[2][0] * v.get_a() + this->matrix[2][1] * v.get_b() + this->matrix[2][2] * v.get_c();

        return Vector3D(a, b, c);
    }
};


Matrix3D operator * (double numb, const Matrix3D &other) {
    Matrix3D *output = new Matrix3D();
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++) {
            output->matrix[i][j] = other.matrix[i][j] * numb;
        }
    }
    return *output;
}

Matrix3D operator * (const Matrix3D &other, double numb) {
    Matrix3D *output = new Matrix3D();
    for (int i = 0; i < 3; i++){
        for (int j = 0; j < 3; j++) {
            output->matrix[i][j] = other.matrix[i][j] * numb;
        }
    }
    return *output;
}


int main() {
//    Vector3D v(1, 2, 3);
//    Vector3D k(v);
//    double num = 3;
//    (k * v).print();
    return 0;
}