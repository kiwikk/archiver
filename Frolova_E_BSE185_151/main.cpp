/**
 *  КДЗ по дисциплине Алгоритмы и структуры данных, 2019-2020 уч.год
 *  выполнила Фролова Елизавета Данииловна, группа БПИ-185, дата (02.04.2020)
 *  IDE: CLion 2019.3.5,
 *  Состав проекта (файлы *.cpp и *.h)
 *  main.cpp
 *  ShannonFano.cpp
 *  LZ77.cpp
 *  Сделано:
 *  > сжатие и распаковка методом Шеннона - Фано
 *  > сжатие и распаковка методом LZ77
 *  > проведен вычислительный эксперимент
 *  > построены таблицы и графики
 *  (для измерения времени выполнения
 *  использовалось милисекунды из <chrono>)
  *  > оформлен отчет
 *  Не сделано:
 *  > сжатие и распаковка методом LZW*
 */

#include "ShannonFano.cpp"
#include "LZ77.cpp"
#include <chrono>
#include <cmath>

//paths:
//const std::string path1="DATA/1.txt";
//const std::string path2="DATA/2.docx";
//const std::string path3="DATA/3.pptx";
//const std::string path4="DATA/4.pdf";
//const std::string path5="DATA/5.dll";
//const std::string path6="DATA/6.jpg";
//const std::string path7="DATA/7.jpg";
//const std::string path8="DATA/8.bmp";
//const std::string path9="DATA/9.bmp";
//const std::string path10="DATA/10.mp3";

// я знаю, что это всё выглядит не оч и
// по-хорошему можно уместить в 1-2 метода, но порой
// в 6 утра легче скопировать и изменить пару стрингов,
// чем придавать всему этому красивый вид
void start_shan(std::vector<std::string> &paths, int cycles)
{
    std::ofstream fout("shann.csv");
    std::cout << "shannfann\n";
    fout << "compress\n";
    std::cout << "compress\n";
    for (auto item : paths)
    {
        fout << item << "\n";
        std::cout << item << " ";
        int pos = item.find('.');
        std::string compress = item;
        compress.replace(pos, item.size() - pos, ".shan");
        for (int i = 0; i < cycles; ++i)
        {
            auto *sf = new ShannonFano();
            auto begin = std::chrono::steady_clock::now();
            sf->fano_compress(item, compress);
            auto end = std::chrono::steady_clock::now();
            auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            fout << elapsed_ms.count() << "\n";
            std::cout << i << " ";
        }
        fout << "\n";
        std::cout << "\n";
    }

    fout << "decompress\n";
    std::cout << "decompress\n";
    for (auto item:paths)
    {
        fout << item << "\n";
        std::cout << item << " ";
        int pos = item.find('.');
        std::string compress = item;
        std::string decompress = item;
        compress.replace(pos, item.size() - pos, ".shan");
        decompress.replace(pos, item.size() - pos, ".unshan");
        for (int i = 0; i < cycles; ++i)
        {
            auto *sf = new ShannonFano();
            auto begin = std::chrono::steady_clock::now();
            sf->fano_decompress(compress, decompress);
            auto end = std::chrono::steady_clock::now();
            auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            fout << elapsed_ms.count() << "\n";
            std::cout << i << " ";
        }
        fout << "\n";
        std::cout << "\n";
    }
    std::cout << "shan end\n";
    fout.close();
}

void start_LZ775(std::vector<std::string> &paths, int cycles)
{
    std::cout << "\n" << "~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~" << "\n";
    std::ofstream fout("lz775.csv");
    std::cout << "lz775\n";
    fout << "compress\n";
    std::cout << "compress\n";
    for (auto item : paths)
    {
        fout << item << "\n";
        std::cout << item << " ";
        int pos = item.find('.');
        std::string compress = item;
        compress.replace(pos, item.size() - pos, ".lz775");
        for (int i = 0; i < cycles; ++i)
        {
            auto *lz775 = new LZ77(1, 4);
            auto begin = std::chrono::steady_clock::now();
            lz775->lz77_compress(item, compress);
            auto end = std::chrono::steady_clock::now();
            auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            fout << elapsed_ms.count() << "\n";
            std::cout << i << " ";
        }
        fout << "\n";
        std::cout << "\n";
    }

    fout << "decompress\n";
    std::cout << "decompress\n";
    for (auto item:paths)
    {
        fout << item << "\n";
        std::cout << item << " ";
        int pos = item.find('.');
        std::string compress = item;
        std::string decompress = item;
        compress.replace(pos, item.size() - pos, ".lz775");
        decompress.replace(pos, item.size() - pos, ".unlz775");
        for (int i = 0; i < cycles; ++i)
        {
            auto *lz775 = new LZ77(1, 4);
            auto begin = std::chrono::steady_clock::now();
            lz775->lz77_decompress(compress, decompress);
            auto end = std::chrono::steady_clock::now();
            auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            fout << elapsed_ms.count() << "\n";
            std::cout << i << " ";
        }
        fout << "\n";
        std::cout << "\n";
    }

    std::cout << "lz775 end\n";
    fout.close();
}

void start_LZ7710(std::vector<std::string> &paths, int cycles)
{
    std::cout << "\n" << "~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~" << "\n";

    std::ofstream fout("lz7710.csv");
    std::cout << "lz7710\n";
    fout << "compress\n";
    std::cout << "compress\n";
    for (auto item : paths)
    {
        fout << item << "\n";
        std::cout << item << " ";
        int pos = item.find('.');
        std::string compress = item;
        compress.replace(pos, item.size() - pos, ".lz7710");
        for (int i = 0; i < cycles; ++i)
        {
            auto *lz7710 = new LZ77(2, 8);
            auto begin = std::chrono::steady_clock::now();
            lz7710->lz77_compress(item, compress);
            auto end = std::chrono::steady_clock::now();
            auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            fout << elapsed_ms.count() << "\n";
            std::cout << i << " ";
        }
        fout << "\n";
        std::cout << "\n";
    }

    fout << "decompress\n";
    std::cout << "decompress\n";
    for (auto item:paths)
    {
        fout << item << "\n";
        std::cout << item << " ";
        int pos = item.find('.');
        std::string compress = item;
        std::string decompress = item;
        compress.replace(pos, item.size() - pos, ".lz7710");
        decompress.replace(pos, item.size() - pos, ".unlz7710");
        for (int i = 0; i < cycles; ++i)
        {
            auto *lz7710 = new LZ77(2, 8);
            auto begin = std::chrono::steady_clock::now();
            lz7710->lz77_decompress(compress, decompress);
            auto end = std::chrono::steady_clock::now();
            auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            fout << elapsed_ms.count() << "\n";
            std::cout << i << " ";
        }
        fout << "\n";
        std::cout << "\n";
    }

    std::cout << "lz7710 end\n";
    fout.close();
}

void start_LZ720(std::vector<std::string> &paths, int cycles)
{
    std::cout << "\n" << "~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~ ~" << "\n";
    std::ofstream fout("lz7720.csv");
    std::cout << "lz7720\n";
    fout << "compress\n";
    std::cout << "compress\n";
    for (auto item : paths)
    {
        fout << item << "\n";
        std::cout << item << " ";
        int pos = item.find('.');
        std::string compress = item;
        compress.replace(pos, item.size() - pos, ".lz7720");
        for (int i = 0; i < cycles; ++i)
        {
            auto *lz7720 = new LZ77(4, 16);
            auto begin = std::chrono::steady_clock::now();
            lz7720->lz77_compress(item, compress);
            auto end = std::chrono::steady_clock::now();
            auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            fout << elapsed_ms.count() << "\n";
            std::cout << i << " ";
        }
        fout << "\n";
        std::cout << "\n";
    }

    fout << "decompress\n";
    std::cout << "decompress\n";
    for (auto item:paths)
    {
        fout << item << "\n";
        std::cout << item << " ";
        int pos = item.find('.');
        std::string compress = item;
        std::string decompress = item;
        compress.replace(pos, item.size() - pos, ".lz7720");
        decompress.replace(pos, item.size() - pos, ".unlz7720");
        for (int i = 0; i < cycles; ++i)
        {
            auto *lz7720 = new LZ77(4, 16);
            auto begin = std::chrono::steady_clock::now();
            lz7720->lz77_decompress(compress, decompress);
            auto end = std::chrono::steady_clock::now();
            auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
            fout << elapsed_ms.count() << "\n";
            std::cout << i << " ";
        }
        fout << "\n";
        std::cout << "\n";
    }

    std::cout << "lz7720 end\n";
    fout.close();
}

std::map<char, double> probability_table(std::string &data)
{
    std::map<char, double> frequency_table;

    for (auto item : data)
    {
        std::map<char, double>::iterator iter;
        iter = frequency_table.find(item);
        if (iter == frequency_table.end())
        {
            frequency_table.insert({item, 1});
        } else
        {
            ++frequency_table[item];
        }
    }

    for (auto item:frequency_table)
    {
        frequency_table[item.first] /= data.size();
    }

    return frequency_table;
}

double get_enrophy(std::map<char, double> prob_table)
{
    double entrophy = 0;
    for (auto item:prob_table)
    {
        entrophy -= item.second * std::log2(item.second);
    }
    return entrophy;
}

void get_table(std::vector<std::string> &paths)
{
    std::ofstream ofs("table.csv");
    std::map<char, double> probs;
    std::string str;
    for (auto item:paths)
    {
        ofs << item << "\n";
        std::ifstream ifs(item);
        ifs >> str;
        ifs.close();
        probs = probability_table(str);
        for (auto pr:probs)
        {
            ofs << pr.first << " " << pr.second << "\n";
        }
        ofs << "entrophy: " << get_enrophy(probs) << "\n";
    }

}

int main()
{
    std::vector<std::string> paths;
    paths.emplace_back("DATA/1.txt");
    paths.emplace_back("DATA/2.docx");
    paths.emplace_back("DATA/3.pptx");
    paths.emplace_back("DATA/4.pdf");
    paths.emplace_back("DATA/5.dll");
    paths.emplace_back("DATA/6.jpg");
    paths.emplace_back("DATA/7.jpg");
    paths.emplace_back("DATA/8.bmp");
    paths.emplace_back("DATA/9.bmp");
    paths.emplace_back("DATA/10.mp3");

    get_table(paths);

    int cycles = 10;
    start_shan(paths, cycles);
    start_LZ775(paths, cycles);
    start_LZ7710(paths, cycles);
    start_LZ720(paths, cycles);

    return 0;
}
