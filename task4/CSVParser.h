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

template <typename Ch, typename Tr, typename Tuple, std::size_t... Is>
void print_tuple_impl(std::basic_ostream<Ch, Tr>& os, const Tuple& t, std::index_sequence<Is...>) {
    (void)std::initializer_list<int>{((os << (Is == 0 ? "" : ", ") << std::get<Is>(t)), 0)...};
}

template <typename Ch, typename Tr, typename... Args>
std::basic_ostream<Ch, Tr>& operator<<(std::basic_ostream<Ch, Tr>& os, const std::tuple<Args...>& t) {
    os << "(";
    print_tuple_impl(os, t, std::make_index_sequence<sizeof...(Args)>{});
    return os << ")";
}

template <typename... Args>
class CSVParser {
public:
    CSVParser(std::istream& stream, std::size_t skip_lines = 0, char delimiter = ',', char escape = '"', char row_delimiter = '\n')
        : stream(stream), delimiter(delimiter), escape(escape), row_delimiter(row_delimiter), skip_lines(skip_lines) {}

    class iterator {
    public:
        iterator(std::istream& stream, std::size_t skip_lines, char delimiter, char escape, char row_delimiter)
            : stream(stream), delimiter(delimiter), escape(escape), row_delimiter(row_delimiter), line_number(0), column_number(0) {
            if (skip_lines > 0) {
                std::string line;
                for (std::size_t i = 0; i < skip_lines; ++i) {
                    std::getline(stream, line);
                }
            }
            read_next_row();
        }
        iterator() : stream(nullptr), delimiter(','), escape('"'), 
		     row_delimiter('\n'), line_number(0), column_number(0) {}
        iterator& operator++() {
            read_next_row();
            return *this;
        }

        bool operator!=(const iterator& other) const {
            return stream.eof() != other.stream.eof();
        }

        bool operator==(const iterator& other) const {
            return stream.eof() == other.stream.eof();
        }

        std::tuple<Args...> operator*() const {
            return current_row;
        }

    private:
        void read_next_row() {
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

        template <typename... T, std::size_t... Is>
        std::tuple<T...> parse_row(const std::vector<std::string>& row, std::index_sequence<Is...>) {
            return std::make_tuple(parse_item<T>(row[Is])...);
        }

        template <typename T>
        T parse_item(const std::string& item) {
            std::stringstream ss(item);
            T value;
            ss >> value;
            return value;
        }

        std::istream& stream;
        char delimiter;
        char escape;
        char row_delimiter;
        std::size_t line_number;
        std::size_t column_number;
        std::tuple<Args...> current_row;
    };

    iterator begin() {
        return iterator(stream, skip_lines, delimiter, escape, row_delimiter);
    }

    iterator end() {
        return iterator();
    }

private:
    std::istream& stream;
    char delimiter;
    char escape;
    char row_delimiter;
    std::size_t skip_lines;
};

#endif // CSVPARSER_H
