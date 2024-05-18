#pragma once

#include <cstdlib>

// Реалізуйте шаблон SimpleVector
template <typename T>
class SimpleVector {
public:
    SimpleVector() : data(nullptr), size_(0), capacity_(0) {} // Конструктор за замовчуванням

    explicit SimpleVector(size_t size) : data(new T[size]), size_(size), capacity_(size) {} // Конструктор з параметром

    ~SimpleVector() { delete[] data; } // Деструктор

    T& operator[](size_t index) { return data[index]; } // Оператор індексації

    T* begin() { return data; } // Початковий ітератор

    T* end() { return data + size_; } // Кінцевий ітератор

    size_t Size() const { return size_; } // Розмір вектора

    size_t Capacity() const { return capacity_; } // Вміст вектора

    void PushBack(const T& value) { // Додавання елемента у кінець вектора
        if (size_ >= capacity_) { // Якщо вектор заповнений, потрібно збільшити його розмір
            size_t new_capacity = capacity_ == 0 ? 1 : 2 * capacity_; // Подвоїти поточний розмір вектора
            T* new_data = new T[new_capacity]; // Виділити пам'ять для нового більшого масиву
            for (size_t i = 0; i < size_; ++i) { // Скопіювати елементи зі старого масиву у новий
                new_data[i] = data[i];
            }
            delete[] data; // Видалити старий масив
            data = new_data; // Перевстановити вказівник на новий масив
            capacity_ = new_capacity; // Оновити поточний розмір вектора
        }
        data[size_] = value; // Додати новий елемент у кінець вектора
        ++size_; // Збільшити розмір вектора
    }

private:
    T* data; // Вказівник на масив елементів
    size_t size_; // Поточний розмір вектора
    size_t capacity_; // Максимальний розмір вектора
};
