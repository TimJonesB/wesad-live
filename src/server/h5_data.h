#ifndef H5DATAH
#define H5DATAH

#include <string>

class H5Data {
public:
    H5Data();
    H5Data(std::string filepath);
    ~H5Data() = default;
    int read_point(std::string path, const size_t index);
    int read_chunk(std::string path, const size_t a, const size_t b);

private:
    std::string h5fname;

};


#endif // H5DATAH
