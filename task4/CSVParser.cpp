#include "CSVParser.h"

template <typename... Args>
CSVParser<Args...>::CSVParser(std::istream& stream, std::size_t skip_lines, char delimiter, char escape, char row_delimiter)
    : stream(stream), delimiter(delimiter), escape(escape), row_delimiter(row_delimiter), skip_lines(skip_lines) {}

template <typename... Args>
CSVParser<Args...>::iterator::iterator(std::istream& stream, std::size_t skip_lines, char delimiter, char escape, char row_delimiter)
    : stream(stream), delimiter(delimiter), escape(escape), row_delimiter(row_delimiter), line_number(0), column_number(0) {
    if (skip_lines > 0) {
        std::string line;
        for (std::size_t i = 0; i < skip_lines; ++i) {
            std::getline(stream, line);
        }
    }
    read_next_row();
}

template <typename... Args>
typename CSVParser<Args...>::iterator& CSVParser<Args...>::iterator::operator++() {
    read_next_row();
    return *this;
}

template <typename... Args>
bool CSVParser<Args...>::iterator::operator!=(const iterator& other) const {
    return !stream.eof();
}

template <typename... Args>
std::tuple<Args...> CSVParser<Args...>::iterator::operator*() const {
    return current_row;
}

template <typename... Args>
void CSVParser<Args...>::iterator::read_next_row() {
    std::string line;
    while (std::getline(stream, line, row_delimiter)) {
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
}

template <typename... Args>
template <typename... T, std::size_t... Is>
std::tuple<T...> CSVParser<Args...>::iterator::parse_row(const std::vector<std::string>& row, std::index_sequence<Is...>) {
    return std::make_tuple(parse_item<T>(row[Is])...);
}

template <typename... Args>
template <typename T>
T CSVParser<Args...>::iterator::parse_item(const std::string& item) {
    std::stringstream ss(item);
    T value;
    ss >> value;
    return value;
}

template <typename... Args>
typename CSVParser<Args...>::iterator CSVParser<Args...>::begin() {
    return iterator(stream, skip_lines, delimiter, escape, row_delimiter);
}

template <typename... Args>
typename CSVParser<Args...>::iterator CSVParser<Args...>::end() {
    return iterator(stream, skip_lines, delimiter, escape, row_delimiter);
}

