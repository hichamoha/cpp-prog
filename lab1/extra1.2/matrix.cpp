#include "matrix.h"

//#include "colormod.h" // namespace Color
#include <cctype>
#include<cstdlib>
#include <string.h>

Matrix::Matrix() :
   m_vectors(0),
   m_rows(0),
   m_cols(0) { }

Matrix::Matrix(size_t rows, size_t cols) :
    m_vectors(rows, matrix_row(cols)), // initial value is copied to each row
    m_rows(rows),
    m_cols(cols) { }

Matrix::Matrix(const Matrix& m) :
    m_vectors(m.rows(), matrix_row(m.cols())),
    m_rows(m.rows()),
    m_cols(m.cols())
{
    for (size_t r = 0; r < m_rows; ++r) {
        for (size_t c = 0; c < m_cols; ++c) {
            (*this)[r][c] = m[r][c];
        }
    }
}

Matrix::Matrix(size_t size) :
    m_vectors(size, matrix_row(size)),
    m_rows(size),
    m_cols(size)
{
    // Create identity matrix
    for (size_t i = 0; i < size; ++i) {
        (*this)[i][i] = 1;
    }
}

Matrix::~Matrix()
{
    // m_vectors is not a pointer so it's automatically de-allocated
}

size_t Matrix::rows() const { return m_rows; }
size_t Matrix::cols() const { return m_cols; }

Matrix& Matrix::operator=(const Matrix& m)
{
    if (&m != this) {
        // Resize if size if different
        size_t mr = m.rows();
        size_t mc = m.cols();
        if (mr != m_rows || mc != m_cols) {
            m_vectors.clear();
            m_vectors.resize(mr, matrix_row(mc));
            m_rows = mr;
            m_cols = mc;
        }
        
        // Copy elements
        for (size_t r = 0; r < mr; ++r) {
            for (size_t c = 0; c < mc; ++c) {
                (*this)[r][c] = m[r][c];
            }
        }
    }
    return *this;
}

void Matrix::check_same_size(const Matrix& m) const
{
    if (m.rows() != m_rows || m.cols() != m_cols) {
        throw std::logic_error("matrices must have the same size");
    }
}

Matrix Matrix::operator+(const Matrix& m) const
{
    check_same_size(m);
    
    Matrix res(*this);
    for (size_t r = 0; r < m_rows; ++r) {
        for (size_t c = 0; c < m_cols; ++c) {
            res[r][c] += m[r][c];
        }
    }
    return res;
}

Matrix Matrix::operator*(const Matrix& m) const
{
    size_t mr = m.rows();
    size_t mc = m.cols();
    
    if (m_cols != mr) {
        throw std::logic_error("these matrices cannot be multiplied");
    }

    Matrix res(m_rows, mc);
    // For each result cell
    for (size_t r = 0; r < m_rows; ++r) {
        for (size_t c = 0; c < mc; ++c) {
            // Calculate vector product
            int sum = 0;
            for (size_t i = 0; i < mr; ++i) {
                sum += (*this)[r][i] * m[i][c];
            }
            res[r][c] = sum;
        }
    }
    return res;
}

Matrix Matrix::operator*(int factor) const
{
    Matrix res(*this);
    for (size_t r = 0; r < m_rows; ++r) {
        for (size_t c = 0; c < m_cols; ++c) {
            res[r][c] *= factor;
        }
    }
    return res;
}

Matrix Matrix::operator-(const Matrix& m) const
{
    check_same_size(m);
    
    Matrix res(*this);
    for (size_t r = 0; r < m_rows; ++r) {
        for (size_t c = 0; c < m_cols; ++c) {
            res[r][c] -= m[r][c];
        }
    }
    return res;
}

Matrix Matrix::operator-() const
{
    return *this * -1;
}

Matrix& Matrix::transpose()
{
    Matrix copy = *this;
    
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
            (*this)[r][c] = copy[c][r];
        }
    }
    
    return *this;
}

Matrix::matrix_row& Matrix::operator[](index i)
{
    return m_vectors[i];
}

const Matrix::matrix_row& Matrix::operator[](index i) const
{
    return m_vectors[i];
}

static void skip_space(std::istream& is)
{
    while (is.good()) {
        if (!std::isspace(is.get())) {
            is.unget();
            break;
        }
    }
}

std::istream& operator>>(std::istream& is, Matrix& m)
{
    // Read [
    skip_space(is);
    if (!is.good() || is.get() != '[') {
        throw std::invalid_argument("does not start with [");
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
                // Empty matrix
                m = Matrix();
                return is;
            } else if (r == 0) {
                // First row
                cols = c;
                m = Matrix(1, cols);
                m.m_vectors.clear(); // remove zero row
            } else if (c != cols) {
                // Not same length as first row
                throw std::invalid_argument("rows have different lengths");
            } else {
                ++m.m_rows;
            }
            
            // Add this row
            m.m_vectors.push_back(values);
            values.clear();
            c = 0;
            ++r;
            
            if (ch == ']') return is;
            else continue;
        }
        
        // Number
        is.unget();
        int num;
        is >> num;
        values.push_back(num);
        ++c;
    }
    
    throw std::invalid_argument("unexpected end of stream");
}

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


Matrix operator*(int factor, const Matrix& m)
{
    // Commutative operation
    return m * factor;
}

//######################################################################
// Deprecated functions 

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

// ################ labyrint ###########################################

// read() ==============================================================

Matrix& Matrix::read(const char** data){
    m_vectors.clear();
    m_rows = 0;

    while(data[m_rows]!='\0'){  // \0' is the null termination character. 
                                //It marks the end of the string.
        m_rows++;
    }
    m_cols = strlen(data[0]);

    for(std::size_t i=0; i<m_rows; i++){
        m_vectors.push_back(matrix_row(m_cols));

        for(std::size_t j=0; j<m_cols; j++){
            (*this)[i][j] = data[i][j];
        }
    }
    return *this;
}

// solve() =============================================================

bool Matrix::solve(){ //order of search: up, left, down, right
    std::size_t rownr = 0;
    std::size_t colnr = 0;

    bool foundStart = false;

    this->mark_exit();  // XXX mark exit and entrance with E

    for(std::size_t i=0; i<m_rows; i++){
        for(std::size_t j=0; j<m_cols; j++){

            if((*this)[i][j] == 'E'){
                rownr=i;
                colnr=j;
                (*this)[i][j] = 'S'; //start
                foundStart = true;
                break;
            }
        }
        if(foundStart){
            break;
        }
    }

    if(foundStart){
        return checkout(rownr, colnr); // XXX Trying to access the path in the matrix
    }
    else{
        std::cerr<<"\n\t in solve: no entrance found"<<std::endl;
        return false;
    }
}

// checkout() =========================================================

bool Matrix::checkout(size_t rownr, size_t colnr)
{
    
//
#ifdef DMAZE
    std::cout <<"in checkout: "<<"rownr="<< rownr <<" colnr="<< colnr << std::endl;
#endif
    
//
    if(rownr<0 || rownr>(m_rows-1) || colnr<0 || colnr>(m_cols-1) ){ //out_of_range, 
    //important to check first before trying to access a certain element in the matrix
        return false;
    }

    char* path = &(*this)[rownr][colnr];
    if(*path == '#' || *path == '.'){ //invalid paths
        return false;
    }

    if(*path == 'E'){ //found the exit
        //Color::Modifier red(Color::FG_RED);
        *path = '.';
        return true;
    }

    else{ //only option left is path == ' ' (whitespace) XXX
        *path = '.';

        if(checkout(rownr-1, colnr)){ //up
            return true;
        }

        if(checkout(rownr, colnr-1)){ //left
            return true;
        }

        if(checkout(rownr+1, colnr)){ //down
            return true;
        }

        if(checkout(rownr, colnr+1)){ //right
            return true;
        }

        *path = ' ';
        return false;
    }
}

// mark_exit() =========================================================

Matrix& Matrix::mark_exit(){
    for(std::size_t i=0; i<m_cols; i++){
        if((*this)[0][i] == ' '){
            (*this)[0][i] = 'E'; //entrance/exit represented with E
        }
        if((*this)[m_rows-1][i] == ' '){
            (*this)[m_rows-1][i] = 'E';
        }
    }
    for(std::size_t i=0; i<m_rows; i++){
        if((*this)[i][0] == ' '){
            (*this)[i][0] = 'E'; //entrance/exit represented with E
        }
        if((*this)[i][m_cols-1] == ' '){
            (*this)[i][m_cols-1] = 'E';
        }
    }
    return *this;
}

