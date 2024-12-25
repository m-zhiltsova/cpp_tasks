#include "CSVParser.h"


// Конструктор класса CSVParser.
// Инициализирует объект CSVParser с указанным потоком ввода, количеством строк для пропуска, разделителем, символом экранирования и разделителем строк.
template <typename... Args>
CSVParser<Args...>::CSVParser(std::istream& stream, std::size_t skip_lines, char delimiter, char escape, char row_delimiter)
    : stream(stream), delimiter(delimiter), escape(escape), row_delimiter(row_delimiter), skip_lines(skip_lines) {}

// Конструктор итератора CSVParser. 
// Инициализирует итератор с указанным потоком ввода, количеством строк для пропуска, разделителем, символом экранирования и разделителем строк
template <typename... Args>
CSVParser<Args...>::iterator::iterator(std::istream* stream, std::size_t skip_lines, char delimiter, char escape, char row_delimiter)
    : stream(stream), delimiter(delimiter), escape(escape), row_delimiter(row_delimiter), line_number(0), column_number(0) {
    if (skip_lines > 0) {
        std::string line;
        for (std::size_t i = 0; i < skip_lines; ++i) {
            std::getline(*stream, line);
        }
    }
    read_next_row();
}
// Конструктор итератора по умолчанию. 
// Инициализирует итератор с нулевым указателем на поток ввода и устанавливает флаг конца потока в true.
template <typename... Args>
CSVParser<Args...>::iterator::iterator() : stream(nullptr), delimiter(','), escape('"'), row_delimiter('\n'), line_number(0), column_number(0), is_end(true) {}


// Операторы инкремента, неравенства, равенства, разыменования для итераторов
template <typename... Args>
typename CSVParser<Args...>::iterator& CSVParser<Args...>::iterator::operator++() {
    read_next_row();
    return *this;
}

template <typename... Args>
bool CSVParser<Args...>::iterator::operator!=(const iterator& other) const {
    return !is_end || !other.is_end;
}

template <typename... Args>
bool CSVParser<Args...>::iterator::operator==(const iterator& other) const {
    return is_end && other.is_end;
}

template <typename... Args>
std::tuple<Args...> CSVParser<Args...>::iterator::operator*() const {
    return current_row;
}


// Метод read_next_row читает следующую строку из потока ввода и разбирает её в кортеж.
template <typename... Args>
void CSVParser<Args...>::iterator::read_next_row() {
    if (!stream) {
        is_end = true;
        return;
    }
    std::string line;
    while (std::getline(*stream, line, row_delimiter)) {
        if (line.empty()) {
            continue;
        }
        std::stringstream ss(line);
        std::string item;
        std::vector<std::string> row;
        while (std::getline(ss, item, delimiter)) {
            row.push_back(item);
        }
        if (row.size() != sizeof...(Args)) {
            throw std::runtime_error("CSVParser: Incorrect number of columns at line " + std::to_string(line_number));
        }
        current_row = parse_row<Args...>(row, std::index_sequence_for<Args...>{});
        line_number++;
        return;
    }
    current_row = std::tuple<Args...>();
    is_end = true;
}
// Метод parse_row разбирает строку в кортеж, используя последовательность индексов.
template <typename... Args>
template <typename... T, std::size_t... Is>
std::tuple<T...> CSVParser<Args...>::iterator::parse_row(const std::vector<std::string>& row, std::index_sequence<Is...>) {
    return std::make_tuple(parse_item<T>(row[Is])...);
}

// Метод parse_item разбирает элемент строки в соответствующий тип.
template <typename... Args>
template <typename T>
T CSVParser<Args...>::iterator::parse_item(const std::string& item) {
    std::stringstream ss(item);
    T value;
    ss >> value;
    return value;
}

// Метод begin возвращает итератор на начало последовательности.
template <typename... Args>
typename CSVParser<Args...>::iterator CSVParser<Args...>::begin() {
    return iterator(&stream, skip_lines, delimiter, escape, row_delimiter);
}

// Метод end возвращает итератор на конец последовательности.
template <typename... Args>
typename CSVParser<Args...>::iterator CSVParser<Args...>::end() {
    return iterator();
}

