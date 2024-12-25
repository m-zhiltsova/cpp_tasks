## Если нужно использовать тесты

git clone https://github.com/google/googletest.git

mdkir build

cd build

cmake ..

make

./runTests


## Если без тестов

g++ main.cpp CSVParser.cpp -o CSV

./CSV
