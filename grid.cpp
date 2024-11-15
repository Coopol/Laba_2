#include <iostream>
using namespace std;

template<typename T>
class Grid final
{
public:
    using value_type = T;
    using size_type = unsigned;

private:
    T* data;                   
    size_type y_size, x_size;  

public:
    Grid(T const& t): y_size(1), x_size(1) // конструктор 1
    {
        data = new T(t);
    }

    Grid(size_type y_size, size_type x_size): y_size(y_size), x_size(x_size) // конструктор 2
    {
        data = new T[y_size * x_size];
    }

    Grid(size_type y_size, size_type x_size, T const& t): y_size(y_size), x_size(x_size) // конструктор 3
    {
        data = new T[y_size * x_size];
        for (size_type i = 0; i < y_size * x_size; ++i)
            data[i] = t;
    }

    ~Grid() // деструктор
    {
           if (y_size == 1 && x_size == 1) 
           {delete data;} 
           else 
           {delete[] data;}
    }

    Grid(Grid const& other): y_size(other.y_size), x_size(other.x_size) // конструктор копирования
    {
        data = new T[y_size * x_size];
        for (size_type i = 0; i < y_size * x_size; ++i)
            data[i] = other.data[i];
    }

    Grid& operator=(Grid const& other) // оператор копирования
    {
        if (this != &other) 
        {
            delete[] data;
            y_size = other.y_size;
            x_size = other.x_size;
            data = new T[y_size * x_size]; 
            for (size_type i = 0; i < y_size * x_size; ++i)
                data[i] = other.data[i];
        }
        return *this;
    }

    Grid(Grid&& other): data(other.data), y_size(other.y_size), x_size(other.x_size) // конструктор перемещения
    {
        other.data = nullptr;
        other.y_size = other.x_size = 0;
    }

    Grid& operator=(Grid&& other) // оператор перемещения
    {
        if (this != &other) 
        {
            delete[] data;
            data = other.data;
            y_size = other.y_size;
            x_size = other.x_size;
            other.data = nullptr; 
            other.y_size = other.x_size = 0;
        }
        return *this;
    }

    T operator()(size_type y_idx, size_type x_idx) const // + проверка на выход из массива
    {
        if (y_idx >= y_size || x_idx >= x_size) 
        {
            return T();
        }
        return data[y_idx * x_size + x_idx];
    }

    T& operator()(size_type y_idx, size_type x_idx) // + проверка на выход из массива
    {
        if (y_idx >= y_size || x_idx >= x_size) {
            return T(); 
        }
        return data[y_idx * x_size + x_idx];
    }

    Grid& operator=(T const& t)
    {
        for (auto it = data, end = data + x_size * y_size; it != end; ++it) 
        {
            *it = t;
        }
        return *this;
    }

    size_type get_y_size() const { return y_size; }
    size_type get_x_size() const { return x_size; }
};
