#include <iostream>
#include <algorithm>

const size_t INIT_SIZE = 4;

class Vector
{
public:
    
    Vector() = default;
    
    ~Vector()
    {
        delete[] m_data;
    }

    void push_back(int value)
    {
        if (m_data)
        {
            if (m_size +1 > m_campacity)
            {
                m_campacity *= 2;
                int* temp_data = new int[m_campacity];
                std::copy(m_data, m_data + m_size, temp_data);
                delete[] m_data;
                m_data = temp_data;
            }
        }
        else
        {
            m_data = new int[INIT_SIZE];
            m_campacity = INIT_SIZE;
        }
        m_data[m_size++] = value;
    }

    void sortVector()
    {
        std::sort(m_data, m_data + m_size);
    }

    void pop_front()
    {
        if (m_size > 1)
        {
            int* temp_data = new int[m_campacity];
            std::copy(m_data+1, m_data + m_size, temp_data);
            delete[] m_data;
            m_data = temp_data;
        }
        else
        {
            std::cout << "vector is empty" << std::endl;
            m_data = nullptr;
        }
    }

    void print()
    {
       for (size_t i = 0;  i < m_size; ++i)
           {
            std::cout << *(m_data + i) << "\t";
           }
           std::cout << std::endl;
    }

    void pop_back()
    {
        if (!empty())
        {
            --m_size;
        }
    }
     
    int operator [](size_t index)
    {
        return m_data[index];
    }

    size_t size() const
    {
        return m_size;
    }

    size_t capacity() const
    {
        return m_campacity;
    }

    bool empty() const
    {
        return (m_size != 0);
    }

    size_t differentSort()
    {
        int temp = 0;
        std::sort(m_data, m_data + m_size);
        for (size_t i = 0; i < m_size; ++i)
            if (m_data[i] != m_data[i + 1])
            {
                temp++;
            }
        return temp;    
    }
    
private:
    size_t m_size = 0;
    size_t m_campacity = 0;
    int* m_data = nullptr;
};



int main()
{
    Vector myVector;
    myVector.push_back(2);
    myVector.push_back(1);
    myVector.push_back(3);
    myVector.push_back(5);
    myVector.push_back(4);
    myVector.push_back(2);
    myVector.push_back(5);
    myVector.print();
    myVector.sortVector();
    myVector.print();
    std::cout << "different num = " << myVector.differentSort() << std::endl;

}
