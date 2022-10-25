#ifndef MATRIX_H
#define MATRIX_H

#include "vector.h"
//#include "../1.5/vector.h"

#include <iostream>
#include <stdexcept>

class Matrix
{
 public:
    typedef unsigned int index;
    
    class matrix_row : private Vector< char >
    {
    public:
        matrix_row( std::size_t s = 0) : Vector< char >( s ) {}
        using Vector<char>::operator [];
    private:
        friend std::istream& operator>>( std::istream&, Matrix& );
    };
    
    Matrix( );
    Matrix( std::size_t, std::size_t);
    Matrix( const Matrix& );
    Matrix(std::size_t size); // think on explicit XXX
    Matrix(int size); // XXX male. 
    ~Matrix( );
/*
        Matrix m = 1; // how can we do it ? you need "explicit"
	int get_mat() { ... } 
	Matrix get_matrix() { .... }
	Matrix m = get_mat(); 
  */  
    Matrix& operator= ( const Matrix& );
    Matrix operator+ ( const Matrix& ) const;
    Matrix operator* ( const Matrix& ) const;
    Matrix operator* ( int ) const;
    Matrix operator-( const Matrix& ) const;
    Matrix operator-( ) const;
    
    Matrix& transpose( );
    
    matrix_row& operator[]( index i );
    const matrix_row& operator[]( index i ) const;
    
    std::size_t rows() const;
    std::size_t cols() const;
    
    //for lab1.2 maze  xxx
    Matrix& read(const char**);
    bool solve();
    
 protected:
 private:
    Vector< matrix_row >        m_vectors;
    std::size_t                 m_rows;
    std::size_t                 m_cols;
    
    void check_same_size(const Matrix&) const;
    friend std::istream& operator>> ( std::istream&, Matrix& );
    
    //for lab1.2 maze  XXX
    bool checkout(size_t, size_t);
    Matrix& mark_exit();
};

std::istream& operator>> ( std::istream&, Matrix& );
std::ostream& operator<< ( std::ostream&, const Matrix& );
std::ostream& operator<< ( std::ostream&, Matrix& ); // XXX male.  
Matrix operator* ( int, const Matrix& );

#endif // MATRIX_H

