#include "my_matrix.h"
#include <cctype>

// Default constructor .......................................................

Matrix::Matrix() :
   m_vectors(0),
   m_rows(0),
   m_cols(0) { }

// constructor with 2 arguments ..............................................

Matrix::Matrix(size_t rows, size_t cols) :
    m_vectors(rows, matrix_row(cols)), // initial value is copied to each row
    m_rows(rows),			// m_vectors is a vector of vector-rows
    m_cols(cols) { }
    // NOTE:m_vectors is a constructor with 2 arguments (size, T), 
    //T: default value for all elements 

// copy constructor ..........................................................

Matrix::Matrix(const Matrix& mcopy) :
    m_vectors(mcopy.rows(), matrix_row(mcopy.cols())),
    m_rows(mcopy.rows()),
    m_cols(mcopy.cols())
{
    for (size_t r = 0; r < m_rows; ++r) {
        for (size_t c = 0; c < m_cols; ++c) {
            (*this)[r][c] = mcopy[r][c];
        }
    }
}

// constructor with one argument (XXX) ........................................
// QUADRATIC matrix
Matrix::Matrix(size_t size) :
    m_vectors(size, matrix_row(size)),
    m_rows(size),
    m_cols(size)
{
    // Create identity matrix from the quadratic matrix
    for (size_t i = 0; i < size; ++i) {
        (*this)[i][i] = 1;
    }
}

// Destructor ................................................................

Matrix::~Matrix()
{
    // m_vectors is not a pointer so it's automatically de-allocated
}

// rows() and cols() .........................................................

size_t Matrix::rows() const { return m_rows; }
size_t Matrix::cols() const { return m_cols; }

// Assignment Operator=() ....................................................

Matrix& Matrix::operator=(const Matrix& mright)
{
    if (&mright != this) {
        // Resize if size is different
        size_t mr = mright.rows();
        size_t mc = mright.cols();

        if (mr != m_rows || mc != m_cols) {
            m_vectors.clear();

            // adjust the size with vector::resize()
            m_vectors.resize(mr, matrix_row(mc));
            m_rows = mr;
            m_cols = mc;
        }
        
        // Copy elements
        for (size_t r = 0; r < mr; ++r) {
            for (size_t c = 0; c < mc; ++c) {
                (*this)[r][c] = mright[r][c];
            }
        }
    }
    return *this;
}

// check_same_size() .........................................................

void Matrix::check_same_size(const Matrix& m) const
{
    if (m.rows() != m_rows || m.cols() != m_cols) {
        throw std::logic_error("\n\t matrices must have the same dimensions");
    }
}

// Overloading operator+() ...................................................

Matrix Matrix::operator+(const Matrix& m) const
{
    check_same_size(m);
    
    Matrix sum(*this);
    for (size_t r = 0; r < m_rows; ++r) {
        for (size_t c = 0; c < m_cols; ++c) {
            sum[r][c] += m[r][c];
        }
    }
    return sum;
}

// Overloading operator*() ...................................................

Matrix Matrix::operator*(const Matrix& m) const
{
    size_t mr = m.rows();
    size_t mc = m.cols();
    
    if (m_cols != mr) {
        throw std::logic_error(" \n\t Multiplication of these matrices is UNDEFINED");
    }

    Matrix product(m_rows, mc);
    // For each result cell
    for (size_t r = 0; r < m_rows; ++r) {
        for (size_t c = 0; c < mc; ++c) {

            // Calculate vector product
            int sum = 0;
            for (size_t i = 0; i < mr; ++i) {
                sum += (*this)[r][i] * m[i][c];
            }
            product[r][c] = sum;
        }
    }
    return product;
}

// operator*() -- scalar multiplication .....................................

Matrix Matrix::operator*(int scalar) const
{
    Matrix product(*this);
    for (size_t r = 0; r < m_rows; ++r) {
        for (size_t c = 0; c < m_cols; ++c) {
            product[r][c] *= scalar;
        }
    }
    return product;
}

// operator-() .............................................................

Matrix Matrix::operator-(const Matrix& m) const
{
    check_same_size(m);
    
    Matrix sub(*this);
    for (size_t r = 0; r < m_rows; ++r) {
        for (size_t c = 0; c < m_cols; ++c) {
            sub[r][c] -= m[r][c];
        }
    }
    return sub;
}

// operator-() ............................................................

Matrix Matrix::operator-() const
{
    return *this * -1;
}

// transpose() .............................................................

Matrix& Matrix::transpose()
{
    Matrix temp = *this;
    
    size_t mr = m_cols;
    size_t mc = m_rows;

    // Resize (not needed for square matrices)
    if (mr != mc) {
        m_vectors.clear();
        m_vectors.resize(mr, matrix_row(mc));
        m_rows = mr;
        m_cols = mc;
    }
    
    // Assign transposed
    for (size_t r = 0; r < mr; ++r) {
        for (size_t c = 0; c < mc; ++c) {
            (*this)[r][c] = temp[c][r];
        }
    }
    
    return *this;
}

// operator[]() ...........................................................

Matrix::matrix_row& Matrix::operator[](index i)
{
    return m_vectors[i];
}

// constant operator[]() .................................................

const Matrix::matrix_row& Matrix::operator[](index i) const
{
    return m_vectors[i];
}

// skip_space() ..........................................................

static void skip_space(std::istream& is)
{
    while (is.good()) {
        if (!std::isspace(is.get())) {
            is.unget();
            break;
        }
    }
}

// operator>>() .........................................................

std::istream& operator>>(std::istream& is, Matrix& m)
{
    // Read [
    skip_space(is);

    // first token must be always [
    if (!is.good() || is.get() != '[') {
        throw std::invalid_argument("\n\t This matrix does not start with [");
    }

    skip_space(is);
    
    size_t c = 0, r = 0;; // current column / row
    size_t cols = -1; // number of columns
    Matrix::matrix_row values;

    while (is.good()) {
        int ch = is.get();
        
        // Ignore whitespace
        if (std::isspace(ch)) continue;
        
        if (ch == ';' || ch == ']') {

            // Set / check column count
            if (r == 0 && c == 0 && ch == ']') {
                // Empty matrix [ ; ; ; ]
                m = Matrix();
                return is;
            } 
            
            else if (r == 0) {
                // First row
                cols = c;
                m = Matrix(1, cols);
                m.m_vectors.clear(); // remove zero row
            } 

            else if (c != cols) {
                // Not same length as first row
                throw std::invalid_argument("\n\t Rows have different dimensions");
            } 

            else {
                ++m.m_rows;
            }
            
            // Add this row
            m.m_vectors.push_back(values);
            values.clear();
            c = 0;
            ++r;
            
            if (ch == ']') return is;
            else continue;
        } // end if (ch == ';' || ch == ']') 
        
        // read a number
        is.unget();  // unget() backs up the input stream so that whatever
                     // value was last returned is still on the stream. (Lippman p761)
        int num;
        is >> num;
        values.push_back(num);
        ++c;
    } // end while: istream is good()
    
    throw std::invalid_argument("\n\t Unexpected end of stream");
}

/*
std::istream& operator>>(std::istream& in, Matrix& m){
  std::string tmp;
  in >> tmp;
 
     // ### case 1
     if(strcmp(tmp.c_str(), "]") == 0){  // c_str() returns a C-style character string
       m.m_rows = m.m_vectors.size();
       m.m_cols = m.m_vectors[0].size(); //size of the first matrix_row, 
                                         //so if input [ 1 2 ; 3 ] 
                                         //then calling m[1][1] will throw out_of_range
      
       if((m.m_cols==0||m.m_rows==0)){ // if input [ ; ; ; ] then it should be a 0x0 matrix
	 m.m_cols = m.m_rows = 0;
	 m.m_vectors.clear();
       }

       return in; // när man kommer till slutet av matrisen 
     //returnera det som är kvar :)
    }
    
    // #### case 2
    else if(strcmp(tmp.c_str(), "[") == 0){
        m.m_vectors.clear();
        m.m_vectors.push_back( Matrix::matrix_row() ); // if input "[ ]" (empty matrix) 
                                                       //then m_vectors.cur_size = 1. bad? 
                                                       //otherwise m.m_cols = m.m_vectors[0].size() 
                                                       //won't work
        return(in >> m);
    }

    // #### case 3
    else if(strcmp(tmp.c_str(), ";") == 0){
        m.m_vectors.push_back( Matrix::matrix_row() );
        return(in >> m);
    }

    // #### case 4
    else{ // read a number
        m.m_vectors[m.m_vectors.size()-1].push_back( atoi(tmp.c_str()) );
        return(in >> m);
    }
}
*/

// operator<<() XXX ..................................................
// to print matrix on MATLAB format

std::ostream& operator<<(std::ostream& os, const Matrix& m)
{
    size_t rows = m.rows(), cols = m.cols();
    
    os << "[ ";
    for (size_t r = 0; r < rows; ++r) {
        for (size_t c = 0; c < cols; ++c) {
            os << m[r][c] << " ";
        }
        
        if (r != rows-1) {
            os << "\n; ";
        }
    }

    os << "]";
    return os;
}

// operator*() .....................................................

Matrix operator*(int factor, const Matrix& m)
{
    // Commutative operation
    return m * factor;
}


// Deprecated functions ============================================

Matrix::Matrix(int size) :
    m_vectors(size, matrix_row(size)),
    m_rows(size),
    m_cols(size)
{
    // Create identity matrix
    for (int i = 0; i < size; ++i) {
        (*this)[i][i] = 1;
    }
}

std::ostream& operator<<(std::ostream& os, Matrix& m)
{
    return os << static_cast<const Matrix&>(m);
}


