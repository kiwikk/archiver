//
// Created by Elizabeth Frolova
//

#include <queue>

struct node
{
    node()
    {}

    node(short offset, short length, char next) : offset(offset), length(length), next(next)
    {}

    short offset{};
    short length{};
    char next{};
};


class LZ77
{
private:

    const int pre_size;
    const int buf_size;

    ///////////////////////////////////////
    ///coding
    //////////////////////////////////////

    //+
    //ищем узел
    node find(std::vector<char> vec, int start_prev, int start_buf, int end_buf)
    {
        std::queue<node> nodes;
        int min = start_buf - start_prev;

        if (start_buf == 6)
            int asdf = 0;

        //добавляем все элементы, равные текущему
        for (int i = 1; i <= min; ++i)
        {
            if (vec[start_buf - i] == vec[start_buf])
                nodes.push(node(i, 1, vec[start_buf + 1]));
        }

        //если ничего не добавилось (т.е. не равных элементов), возвращаем нулевой код
        if (nodes.empty())
            return node(0, 0, vec[start_buf]);

        node no;

        //если после символа в ноде, есть дальнейшее совпадение, то добавляем новую ноду с длиной+1
        //иначе выкидываем ноду
        while (nodes.size() != 1)
        {
            no = nodes.front();
            if (vec[start_buf + no.length - no.offset] == vec[start_buf + no.length])
                nodes.push(node(no.offset, no.length + 1, vec[start_buf + no.length + 1]));
            nodes.pop();
        }

        no = nodes.front();

        //проверяем на возможность увеличить длину найденной последовательности
        while (start_buf + no.length != end_buf &&
               vec[start_buf + no.length] == vec[start_buf + no.length - no.offset])
        {
            ++no.length;
        }
        no.next = vec[start_buf + no.length];

        return no;
    }

    //+
    //реализация LZ77
    std::vector<node> lz77_code(std::vector<char> bytes)
    {
        std::vector<node> res;

        int start_preview = 0;
        int start_buf = 0;
        int end_buf = std::min((int) bytes.size(), buf_size);

        node no;

        while (start_buf < bytes.size())
        {
            if (no.offset == 3)
                int ertyui = 0;
            no = find(bytes, start_preview, start_buf, end_buf);
            start_buf += no.length + 1;
            start_preview = std::max(0, start_buf - pre_size);
            end_buf = std::min((int) bytes.size(), buf_size + start_buf);
            res.push_back(no);
        }

        return res;
    }

    ///////////////////////////////////////
    ///decoding
    //////////////////////////////////////

    std::vector<node> get_nodes(std::vector<char> &bytes, int &size)
    {
        std::vector<node> nodes;
        int i = 0;

        std::string str;
        char ch;
        while (ch != '\n')
        {
            ch = bytes[i++];
            str += ch;
        }
        size = std::stoi(str);

        for (int j = 0, index = i; j < size; ++j)
        {
            int lenght;
            int offset;
            str = "";
            ch = bytes[index++];
            while (ch != ' ')
            {
                str += ch;
                ch = bytes[index++];
            }
            offset = std::stoi(str);

            ch = bytes[index++];
            str = "";
            while (ch != ' ')
            {
                str += ch;
                ch = bytes[index++];
            }
            lenght = std::stoi(str);

            ch = bytes[index++];
            ++index;
            nodes.emplace_back(offset, lenght, ch);
        }
        return nodes;
    }


    std::string lz77_dec(int n, std::vector<node> &nodes)
    {
        std::string str = "";

        for (int i = 0; i < n; ++i)
        {
            int size = str.size();
            for (int k = 0; k < nodes[i].length; ++k)
            {
                int tmp = size - nodes[i].offset + k;
                str += str[tmp];
            }
            str += nodes[i].next;
        }

        return str;
    }


    ///////////////////////////////////////
    ///input-output
    //////////////////////////////////////

    //+
    // записываем в файл байты
    void write_to_file(std::string &str, std::string fileName)
    {
        std::ofstream ofs(fileName, std::ios::binary | std::ios::out);
        ofs << str;
        ofs.close();
    }

    //+
    // тут записываем в файл байты
    void write_to_file(std::vector<node> nodes, std::string fileName)
    {
        std::ofstream ofs(fileName, std::ios::binary | std::ios::out);
        ofs << nodes.size() << "\n";
        for (auto item:nodes)
        {
            ofs << item.offset << " ";
            ofs << item.length << " ";
            ofs << item.next << " ";
        }
        ofs.close();
    }

    //+
    // считать данные из файла
    std::vector<char> read_file(std::string &path)
    {
        std::ifstream ifs(path, std::ios::binary | std::ios::ate);
        std::ifstream::pos_type pos = ifs.tellg();

        std::vector<char> result(pos);
        ifs.seekg(0, std::ios::beg);
        ifs.read(&result[0], pos);

        return result;
    }

public:

    LZ77(int pre_s, int buf) : pre_size(pre_s * 1024), buf_size(buf * 1024)
    {}

    //сжатие
    void lz77_compress(std::string &fileFrom, std::string &fileTo)
    {
        auto bytes = read_file(fileFrom);
        bytes.push_back(bytes.back() + 1);
        std::vector<node> nodes = lz77_code(bytes);
        write_to_file(nodes, fileTo);
    }

    //разжатие
    void lz77_decompress(std::string &fileFrom, std::string fileTo)
    {
        int size = 0;
        auto bytes = read_file(fileFrom);
        auto nodes = get_nodes(bytes, size);
        auto str = lz77_dec(size, nodes);
        str.pop_back();
        write_to_file(str, fileTo);
    }
};


