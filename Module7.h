// Module 7, Yurkina Marya
#pragma once;

#ifndef INTARRAY_H
#define INTARRAY_H

#include <exception>
#include <iostream>
using namespace std;

class BadRange : public exception
{
public:
    virtual const char* what() const noexcept override
    {
        return "ERROR: Bad range!";
    }
};

class BadLength : public exception
{
public:
    virtual const char* what() const noexcept override
    {
        return "ERROR: Bad length!";
    }
};

class IntArray
{
private:
    int m_length{};
    int* m_data{};

public:
    IntArray() = default;

    IntArray(int length) : m_length{ length }
    {
        if (length < 0)
        {
            throw BadLength();
        }

        if (length > 0)
            m_data = new int[length] {};
    }

    ~IntArray()
    {
        delete[] m_data;
    }

    void erase()
    {
        delete[] m_data;
        m_data = nullptr;
        m_length = 0;
    }

    int& operator[](int index)
    {
        if (index < 0 && index > m_length)
        {
            throw BadRange();
        }

        return m_data[index];
    }

    void reallocate(int newLength)
    {
        erase();
        if (newLength <= 0)
            return;
        m_data = new int[newLength];
        m_length = newLength;
    }

    void resize(int newLength)
    {
        if (newLength == m_length)
            return;
        if (newLength <= 0)
        {
            erase();
            return;
        }

        int* data{ new int[newLength] };

        if (m_length > 0)
        {
            int elementsToCopy{ (newLength > m_length) ? m_length : newLength };
            for (int index{ 0 }; index < elementsToCopy; ++index)
                data[index] = m_data[index];
        }

        delete[] m_data;
        m_data = data;
        m_length = newLength;
    }

    void insertBefore(int value, int index)
    {
        if (index < 0 && index > m_length)
        {
            throw BadRange();
        }
        int* data{ new int[m_length + 1] };
        for (int before{ 0 }; before < index; ++before)
            data[before] = m_data[before];
        data[index] = value;
        for (int after{ index }; after < m_length; ++after)
            data[after + 1] = m_data[after];
        delete[] m_data;
        m_data = data;
        ++m_length;
    }

    void remove(int index)
    {
        if (index < 0 && index > m_length)
        {
            throw BadRange();
        }
        if (m_length == 1)
        {
            erase();
            return;
        }

        int* data{ new int[m_length - 1] };
        for (int before{ 0 }; before < index; ++before)
            data[before] = m_data[before];
        for (int after{ index + 1 }; after < m_length; ++after)
            data[after - 1] = m_data[after];

        delete[] m_data;
        m_data = data;
        --m_length;
    }

    void insertAtBeginning(int value) { insertBefore(value, 0); }
    void insertAtEnd(int value) { insertBefore(value, m_length); }

    int getLength() const { return m_length; }
};

#endif
