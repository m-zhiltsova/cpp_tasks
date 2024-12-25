#ifndef CSVPARSER_H
#define CSVPARSER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <tuple>
#include <stdexcept>
#include <string>
#include <type_traits>


// Шаблон print_tuple_impl ниже используется для вывода элементов кортежа в поток.
// Принимает поток вывода, кортеж и последовательность индексов.
// Выводит элементы кортежа, разделенные запятыми.

template <typename Ch, typename Tr, typename Tuple, std::size_t... Is>
void print_tuple_impl(std::basic_ostream<Ch, Tr>& os, const Tuple& t, std::index_sequence<Is...>) {
    (void)std::initializer_list<int>{((os << (Is == 0 ? "" : ", ") << std::get<Is>(t)), 0)...};
}


// Этот шаблон перегружает оператор `<<` для кортежей, позволяя выводить кортежи в поток вывода.
// Использует функцию `print_tuple_impl` для вывода элементов кортежа.

template <typename Ch, typename Tr, typename... Args>
std::basic_ostream<Ch, Tr>& operator<<(std::basic_ostream<Ch, Tr>& os, const std::tuple<Args...>& t) {
    os << "(";
    print_tuple_impl(os, t, std::make_index_sequence<sizeof...(Args)>{});
    return os << ")";
}


// Объявление шаблонного класса CSVParser.
// Принимает произвольное количество типов Args.
// Конструктор класса принимает поток ввода, количество строк для пропуска, разделитель, символ экранирования и разделитель строк.

template <typename... Args>
class CSVParser {
public:
    CSVParser(std::istream& stream, std::size_t skip_lines = 0, char delimiter = ',', char escape = '"', char row_delimiter = '\n');


    // Объявление вложенного класса iterator, который представляет итератор для класса CSVParser. 
    // Включает конструкторы, операторы инкремента, неравенства, равенства и разыменования.
    
    class iterator {
    public:
        iterator(std::istream* stream, std::size_t skip_lines, char delimiter, char escape, char row_delimiter);
        iterator();
        iterator& operator++();
        bool operator!=(const iterator& other) const;
        bool operator==(const iterator& other) const;
        std::tuple<Args...> operator*() const;


    // Объявление приватных методов класса iterator:
    //    read_next_row читает следующую строку из потока.
    //    parse_row разбирает строку в кортеж.
    //    parse_item разбирает элемент строки в соответствующий тип.

    private:
        void read_next_row();
        template <typename... T, std::size_t... Is>
        std::tuple<T...> parse_row(const std::vector<std::string>& row, std::index_sequence<Is...>);
        template <typename T>
        T parse_item(const std::string& item);


    // Это объявление приватных членов класса iterator:
    //     stream указатель на поток ввода.
    //     delimiter разделитель столбцов.
    //     escape символ экранирования.
    //     row_delimiter разделитель строк.
    //     line_number текущий номер строки.
    //     column_number текущий номер столбца.
    //     current_row текущая строка в виде кортежа.
    //     is_end флаг, указывающий, достигнут ли конец потока.
        
	std::istream* stream;
        char delimiter;
        char escape;
        char row_delimiter;
        std::size_t line_number;
        std::size_t column_number;
        std::tuple<Args...> current_row;
        bool is_end = false;
    };


    // Объявление методов begin и end.
    // Возвращают итераторы на начало и конец последовательности.
    
    iterator begin();
    iterator end();


// Объявление приватных членов класса CSVParser:
// 	stream ссылка на поток ввода.
// 	delimiter разделитель столбцов.
// 	escape символ экранирования.
// 	row_delimiter разделитель строк.
// 	skip_lines количество строк для пропуска.

private:
    std::istream& stream;
    char delimiter;
    char escape;
    char row_delimiter;
    std::size_t skip_lines;
};

#include "CSVParser.cpp"

#endif // CSVPARSER_H

