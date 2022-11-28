# Лабораторная работа №1
Программа тестирует сортировки и на основе полученных данных строит график зависимости времени сортировки от количества элементов в массиве.

## Интерфейс
Программа имеет консольный интерфейс(параметры запуска). Список параметров представлен ниже:

| Short | Long | Description |
|---|---|---|
| -h | --help |  print this help |
| -t | --test | run unit tests (located in ./src/test/**) |
| -s | --sequence-type | type of sequence (list, array) |
| -a | --algorithms | tested sort algorithms (heap, shell, quick) |
| -r | --range | sequence length range, as follows 'MIN MAX STEP' |
| -o | --output | output file(if unspecified plot will be built) |
| -g | --gaps | gaps for shell sort(default is '701 301 132 57 23 10 4 1') |
| -c | --check | checks sort correctness on a given sequence |

## Особенности
Для построения графиков требуется gnuplot
