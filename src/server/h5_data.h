#ifndef H5DATAH
#define H5DATAH

#include <string>
#include <cassert>

#include "hdf5.h"
#include "data_config.h"

const bool debug_bool = 1;

template <size_t ConfigIndex>
class H5Data {
public:
    H5Data();
    H5Data(std::string filepath): h5fname(filepath) {}
    ~H5Data() = default;
    template<typename T>
    T read_point(const std::string &path, const size_t index);
    template<typename T>
    int read_chunk(const std::string &path, const size_t a, const size_t b, T buf[][ConfigList[ConfigIndex].Nchannels]);

private:
    std::string h5fname;

};

template<size_t ConfigIndex>
template<typename T>
T H5Data<ConfigIndex>::read_point(const std::string &path, const size_t index) {
    const hsize_t NX = 1;
    const hsize_t NX_SUB = 1;
    const hsize_t RANK_OUT = 2;


    hid_t file = H5Fopen (this->h5fname.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);
    hid_t dataset = H5Dopen (file, path.c_str(), H5P_DEFAULT);
    hid_t datatype = H5Dget_type(dataset);
    H5T_class_t dclass = H5Tget_class(datatype);
    H5T_order_t order = H5Tget_order(datatype);
    hsize_t size = H5Tget_size(datatype);
    hid_t dataspace = H5Dget_space(dataset);

    const int rank = H5Sget_simple_extent_ndims(dataspace);
    // assert(rank == 2);

    hsize_t dims[rank];
    hsize_t maxdims[rank];
    int status = H5Sget_simple_extent_dims(dataspace, dims, maxdims);
    if (status < 0) {"Error!";}

    hsize_t n_chan = dims[1];
    T data_out[NX][n_chan];

    hsize_t offset[2] = {index, 0};
    hsize_t count[2] = {NX_SUB, n_chan};
    status = H5Sselect_hyperslab(dataspace, H5S_SELECT_SET, offset, NULL, count, NULL);
    if (status < 0) {"Error!";}

    hsize_t dimsm[2] = {NX, n_chan};
    hid_t memspace = H5Screate_simple(RANK_OUT, dimsm, NULL);
    hsize_t offset_out[2] = {0, 0};
    hsize_t count_out[2] = {NX_SUB, n_chan};
    status = H5Sselect_hyperslab(memspace, H5S_SELECT_SET, offset_out, NULL, count_out, NULL);
    if (status < 0) {"Error!";}



    status = H5Dread(dataset, datatype, memspace, dataspace, H5P_DEFAULT, data_out);
    if (status < 0) {throw std::runtime_error("Error!");}

    if (debug_bool) {
        std::cout << "PATH: " << path << std::endl;
        std::cout << "dims = " << maxdims[0] << std::endl;
        std::cout << "PATH: " << path << std::endl;
        std::cout << "rank = " << rank << std::endl;
        if (dclass == H5T_INTEGER) {
            std::cout << "Dataset has Integer Type" << std::endl;
        }
        if (order == H5T_ORDER_LE) {
            std::cout << "Dataset has LE order" << std::endl;
        }
        std::cout << "nDims = " << dims[0] << std::endl;
        std::cout << "Size is " << size << std::endl;
    }
    H5Sclose(memspace);
    H5Sclose(dataspace);
    H5Tclose(datatype);
    H5Dclose(dataset);
    H5Fclose(file);

    return data_out[0][0];
    // return H5S_NULL;
}

template<size_t ConfigIndex>
template<typename T>
int H5Data<ConfigIndex>::read_chunk(const std::string &path, const size_t a, const size_t b, T buf[][ConfigList[ConfigIndex].Nchannels]) {
    if (b-a < 0) {
        throw std::runtime_error("Size of chunk[a:b] must be greater than or equal to zero.");
    }
    size_t chunk_sz = b - a;
    const hsize_t NX = chunk_sz;
    const hsize_t NX_SUB = chunk_sz;
    const hsize_t RANK_OUT = 2;

    hid_t file = H5Fopen (this->h5fname.c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);
    hid_t dataset = H5Dopen (file, path.c_str(), H5P_DEFAULT);
    hid_t datatype = H5Dget_type(dataset);
    H5T_class_t dclass = H5Tget_class(datatype);
    H5T_order_t order = H5Tget_order(datatype);
    hsize_t size = H5Tget_size(datatype);
    hid_t dataspace = H5Dget_space(dataset);

    const int rank = H5Sget_simple_extent_ndims(dataspace);
    std::cout << "rank debug: " << rank << std::endl;
    // assert(rank == 2);

    hsize_t dims[rank];
    hsize_t maxdims[rank];
    int status = H5Sget_simple_extent_dims(dataspace, dims, maxdims);
    if (status < 0) {"Error!";}

    hsize_t n_chan = dims[1];

    hsize_t offset[2] = {a, 0};
    hsize_t count[2] = {NX_SUB, n_chan};
    status = H5Sselect_hyperslab(dataspace, H5S_SELECT_SET, offset, NULL, count, NULL);
    if (status < 0) {"Error!";}

    hsize_t dimsm[2] = {NX, n_chan};
    hid_t memspace = H5Screate_simple(RANK_OUT, dimsm, NULL);
    hsize_t offset_out[2] = {0, 0};
    hsize_t count_out[2] = {NX_SUB, n_chan};
    status = H5Sselect_hyperslab(memspace, H5S_SELECT_SET, offset_out, NULL, count_out, NULL);
    if (status < 0) {"Error!";}

    status = H5Dread(dataset, datatype, memspace, dataspace, H5P_DEFAULT, buf);
    if (status < 0) {throw std::runtime_error("Error!");}

    if (debug_bool) {
        if (dclass == H5T_INTEGER) {
            std::cout << "Dataset has Integer Type" << std::endl;
        }
        if (order == H5T_ORDER_LE) {
            std::cout << "Dataset has LE order" << std::endl;
        }
        std::cout << "rank = " << rank << std::endl;
        std::cout << "nDims = " << dims[0] << std::endl;
        std::cout << "Size is " << size << std::endl;
        std::cout << "nchan " << n_chan << std::endl;
        std::cout << "dclass is " << dclass << std::endl;
    }
    H5Sclose(dataspace);
    H5Sclose(memspace);
    H5Tclose(datatype);
    H5Dclose(dataset);
    H5Fclose(file);

    return H5S_NULL;
}
#endif // H5DATAH
