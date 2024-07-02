// Complex.hpp

#pragma once
#include <iostream>
#include <string> // Include string header for std::to_string

class Complex {
private:
    double real;
    double imag;

public:
    Complex(double r = 0.0, double i = 0.0) : real(r), imag(i) {}

    // Getter for real part
    double getReal() const {
        return real;
    }

    // Getter for imaginary part
    double getImaginary() const {
        return imag;
    }

    // Convert Complex to string representation
    std::string to_string() const {
        return std::to_string(real) + (imag >= 0 ? " + " : " - ") + std::to_string(std::abs(imag)) + "i";
    }

    // Overload + operator
    Complex operator+(const Complex& other) const {
        return Complex(real + other.real, imag + other.imag);
    }

    // Overload - operator
    Complex operator-(const Complex& other) const {
        return Complex(real - other.real, imag - other.imag);
    }

    // Overload * operator
    Complex operator*(const Complex& other) const {
        return Complex(real * other.real - imag * other.imag, real * other.imag + imag * other.real);
    }

    // Overload / operator
    Complex operator/(const Complex& other) const {
        double denominator = other.real * other.real + other.imag * other.imag;
        return Complex((real * other.real + imag * other.imag) / denominator, 
                       (imag * other.real - real * other.imag) / denominator);
    }

    // Overload == operator
    bool operator==(const Complex& other) const {
        return real == other.real && imag == other.imag;
    }

    // Overload != operator
    bool operator!=(const Complex& other) const {
        return !(*this == other);
    }

    // Overload > operator
    bool operator>(const Complex& other) const {
        return this->norm() > other.norm();
    }

    // Overload < operator
    bool operator<(const Complex& other) const {
        return this->norm() < other.norm();
    }

    // Friend function to overload << operator for easy output
    friend std::ostream& operator<<(std::ostream& os, const Complex& c) {
        os << c.to_string();
        return os;
    }

    // Function to compute the norm (magnitude squared) of the complex number
    double norm() const {
        return real * real + imag * imag;
    }
};
