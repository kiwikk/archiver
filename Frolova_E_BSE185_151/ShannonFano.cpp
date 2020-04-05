#include <bitset>
#include <iostream>
#include <map>
#include <vector>
#include <algorithm>
#include <fstream>

struct FanoNode
{
    FanoNode(char symbol, int frequency, const std::string &code) : symbol(symbol), frequency(frequency), code(code)
    {}

    char symbol;
    int frequency;
    std::string code;
};

class ShannonFano
{
private:
    std::vector<FanoNode> fanoCodes;
    int data_size;

    ///////////////////////////////////////
    ///coding
    //////////////////////////////////////

    //+
    // считаем частоту встреч каждого символа
    std::map<char, int> build_table(std::vector<char> &data)
    {
        std::map<char, int> frequency_table;

        for (auto item : data)
        {
            std::map<char, int>::iterator iter;
            iter = frequency_table.find(item);
            if (iter == frequency_table.end())
            {
                frequency_table.insert({item, 1});
            } else
            {
                ++frequency_table[item];
            }
        }

        return frequency_table;
    }

    //+
    //инициализация вектора нод
    void initialize_fano_codes(std::vector<FanoNode> &fanoVec, std::map<char, int> &frecTable)
    {
        for (auto item:frecTable)
        {
            fanoVec.emplace_back(item.first, item.second, "");
        }
    }

    //+
    //высчитывание медианы
    std::vector<FanoNode>::iterator get_index(std::vector<FanoNode>::iterator iter_begin,
                                              std::vector<FanoNode>::iterator iter_end)
    {
        int tmp = 0;
        int probability = 0;

        for (auto i = iter_begin; i != iter_end; ++i)
        {
            probability += i->frequency;
        }

        while (tmp * 2 < probability)
        {
            tmp += iter_begin->frequency;
            ++iter_begin;
        }

        if (tmp + iter_begin->frequency < probability - tmp)
        {
            iter_begin = prev(iter_begin);
        }

        return iter_begin;
    }

    //+
    //алгоритм Фано
    void Shannon_Fano_code(__gnu_cxx::__normal_iterator<FanoNode *, std::vector<FanoNode>> iter_begin,
                           __gnu_cxx::__normal_iterator<FanoNode *, std::vector<FanoNode>> iter_end)
    {
        auto mid_iter = get_index(iter_begin, iter_end);

        if ((next(iter_begin) != iter_end && iter_begin != iter_end) || data_size != 0)
        {

            for (auto it = iter_begin; it != mid_iter; ++it)
            {
                it->code += "0";
            }

            for (auto it = mid_iter; it != iter_end; ++it)
            {
                it->code += "1";
            }

            data_size = 0;

            Shannon_Fano_code(iter_begin, mid_iter);
            Shannon_Fano_code(mid_iter, iter_end);
        } else return;
    }

    //+
    // находим коды для каждого символа (основная часть, где применяется алгоритм Фано)
    std::map<char, std::string> get_codes(std::map<char, int> &frequencyTable)
    {
        std::map<char, std::string> codes;

        initialize_fano_codes(fanoCodes, frequencyTable);

        std::sort(fanoCodes.begin(), fanoCodes.end(),
                  [](const FanoNode &l, const FanoNode &r)
                  {
                      return l.frequency > r.frequency;
                  });

        Shannon_Fano_code(fanoCodes.begin(), fanoCodes.end());
        for (const auto &item:fanoCodes)
        {
            codes[item.symbol] = item.code;
        }

        return codes;
    }

    void bytes_to_str(std::string &basicString,
                      std::map<char, std::string> &map,
                      const std::vector<char> &data)
    {
        for (auto symbol:data)
        {
            basicString += map[symbol];
        }
    }

    //+
    // преобразовать бинарную строку в байт
    char binary_string_to_char(std::string &binary)
    {
        return static_cast<char>(std::bitset<8>(binary).to_ulong());
    }

    //преобразуем строку из байтов в чары, в конце дописываем position символов, чтобы всё хорошо записывалось по 8
    void bytes_to_chars(const std::string &str, std::string &chars, int position, int size)
    {
        std::string buffer;

        for (int i = 0; i < size + position; ++i)
        {
            if (i >= size)
            {
                buffer += "1";
            } else buffer += str[i];
            if (buffer.size() == 8)
            {
                chars += binary_string_to_char(buffer);
                buffer = "";
            }
        }
    }

    ///////////////////////////////////////
    ///decoding
    //////////////////////////////////////

    //+
    //таблица кодов
    std::map<std::string, char> get_table(std::vector<char> bytes, int &_fakes, int &position)
    {
        int i;

        std::string fakes;
        for (i = 0; bytes[i] != '\n'; ++i)
            fakes += bytes[i];
        _fakes = std::stoi(fakes);
        ++i;

        std::string _symb;
        for (; bytes[i] != '\n'; ++i)
            _symb += bytes[i];
        int symbols = std::stoi(_symb);
        ++i;

        std::map<std::string, char> table;
        for (int j = 0, index = i; j < symbols; ++j)
        {
            char tmp = bytes[index++];
            char ch = bytes[index++];
            std::string str;
            while (ch != '\n')
            {
                str += ch;
                ch = bytes[index++];
            }
            table[str] = tmp;
            position = index;
        }

        return table;
    }

    //+
    // преобразовать байт в строку из 0 и 1
    std::string from_char_to_bin_string(char c)
    {
        return std::bitset<8>(c).to_string();
    }

    //+
    // тут мы по считанному файлу создаем словарь и бинарную строку, в которой у нас закодированный текст (с конца строки должны быть убраны лишние символы)
    typedef std::map<std::string, char> dictionary;

    std::pair<dictionary, std::string> get_dictionary_and_binary_code(std::vector<char> data)
    {
        int fakes;
        int position;
        std::map<std::string, char> table = get_table(data, fakes, position);

        std::vector<char> data_without_codes(data.size() - position);
        std::copy(next(data.begin(), position), data.end(), data_without_codes.begin());

        std::string byte_string;
        for (auto item:data_without_codes)
        {
            byte_string += from_char_to_bin_string(item);
        }
        byte_string.erase(prev(byte_string.end(), fakes), byte_string.end());

        return std::pair<dictionary, std::string>{table, byte_string};
    }

    //получаем строку чаров из байтов
    std::string get_string(std::string &byte_string, std::map<std::string, char> dict)
    {
        std::string result;

        std::string code;
        for (int i = 0; i < byte_string.size(); ++i)
        {
            code += byte_string[i];
            if (dict.find(code) != dict.end())
            {
                result+=dict[code];
                code="";
            }
        }

        return result;
    }


    ///////////////////////////////////////
    ///input-output
    //////////////////////////////////////
    //
    // тут записываем в файл байты
    void write_to_file(std::string &str, std::string fileName)
    {
        std::ofstream ofs(fileName, std::ios::binary | std::ios::out);
        ofs << str;
        ofs.close();
    }

    //+
    // мы имеем считанные из файла data, коды каждого символа codes и файл куда надо записать filename
    void write_to_file(std::map<char, std::string> codes, std::string &fileName, std::vector<char> &data)
    {
        std::string str;
        bytes_to_str(str, codes, data);

        int position = (str.size() % 8) == 0 ? 0 : 8 - str.size() % 8;
        int size = str.size();
        std::string addition = std::to_string(position);

        std::string chars;
        bytes_to_chars(str, chars, position, size);

        std::ofstream ofs(fileName, std::ios::binary | std::ios::out);
        ofs << addition << "\n";
        ofs << codes.size() << "\n";
        for (auto item:codes)
        {
            ofs << item.first;
            ofs << item.second << "\n";
        }

        ofs << chars;

        ofs.close();
    }

    //+
    // считать данные из файла (записывает байты в outputString и возвращает длину)
    std::vector<char> read_file(std::string &path)
    {
        std::ifstream ifs(path, std::ios::binary | std::ios::ate);
        std::ifstream::pos_type pos = ifs.tellg();

        std::vector<char> result(pos);
        ifs.seekg(0, std::ios::beg);
        ifs.read(&result[0], pos);

        data_size = result.size();
        return result;
    }

public:
    //сжатие
    void fano_compress(std::string &fileFrom, std::string &fileTo)
    {
        auto bytes = read_file(fileFrom);
        std::map<char, int> table = build_table(bytes);
        std::map<char, std::string> codes = get_codes(table);
        write_to_file(codes, fileTo, bytes);
    }

    //разжатие
    void fano_decompress(std::string &fileFrom, std::string fileTo)
    {
        auto bytes = read_file(fileFrom);
        std::pair<dictionary, std::string> data = get_dictionary_and_binary_code(bytes);
        std::string result = get_string(data.second, data.first);
        write_to_file(result, fileTo);
    }
};