/**
 *  КДЗ по дисциплине Алгоритмы и структуры данных, 2019-2020 уч.год
 *  выполнила Фролова Елизавета Данииловна, группа БПИ-185, дата (02.04.2020)
 *  IDE: CLion 2019.3.5,
 *  Состав проекта (файлы *.cpp и *.h)
 *  Сделано:
 *  > сжатие и распаковка методом Шеннона - Фано
 *  Не сделано:
 *  > сжатие и распаковка методом LZ77
 *  > сжатие и распаковка методом LZW*
 *  > проведен вычислительный эксперимент
 *  > построены таблицы и графики (для измерения времени выполнения использовалось ХХХ)
 *  > оформлен отчет
 */

#include "ShannonFano.cpp"

void get_coding()
{

}


int main()
{
    std::string path = "DATA/image.jpg";
    std::string path_code = "DATA/image.shan";
    std::string path_decode = "DATA/image.unshan";
    std::string jpg_path = "DATA/image.jpg";
    std::string jpg_path_code = "DATA/image.shan";
    std::string jpg_path_decode = "DATA/image.unshan";

    auto *shan = new ShannonFano();
    shan->fano_compress(path, path_code);
    shan->fano_decompress(path_code, path_decode);
    return 0;
}
