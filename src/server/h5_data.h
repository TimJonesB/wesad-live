#ifndef H5DATAH
#define H5DATAH

#include <string>
#include "H5Cpp.h"

class H5Data {
public:
    H5Data();
    H5Data(std::string filepath);
    ~H5Data() = default;
    int read_point(std::string path, const size_t index);
    int read_chunk(std::string path, const size_t a, const size_t b);

private:
    H5::H5File h5f = H5S_NULL;

};


#endif // H5DATAH
