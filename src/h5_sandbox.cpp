#include <iostream>
#include <string>
#include <vector>
#include <map>
#include "hdf5.h"
const int NX = 10;
const int NX_SUB = 5;
const int RANK_OUT = 1;

constexpr std::string_view FILENAME = "../data/outfile.h5";
constexpr std::string_view DATASET = "label";
const bool debug_bool = 1;
int run_it() {
    int data_out[NX];

    hid_t file = H5Fopen (std::string(FILENAME).c_str(), H5F_ACC_RDONLY, H5P_DEFAULT);
    hid_t dataset = H5Dopen (file, std::string(DATASET).c_str(), H5P_DEFAULT);
    hid_t datatype = H5Dget_type(dataset);
    H5T_class_t dclass = H5Tget_class(datatype);
    H5T_order_t order = H5Tget_order(datatype);
    hsize_t size = H5Tget_size(datatype);
    hid_t dataspace = H5Dget_space(dataset);

    const int rank = H5Sget_simple_extent_ndims(dataspace);
    hsize_t dims[rank];
    hsize_t maxdims[rank];
    int status = H5Sget_simple_extent_dims(dataspace, dims, maxdims);

    hsize_t offset[1] = {0};
    hsize_t count[1] = {NX_SUB};
    status = H5Sselect_hyperslab(dataspace, H5S_SELECT_SET, offset, NULL, count, NULL);

    hsize_t dimsm[1] = {NX};
    hid_t memspace = H5Screate_simple(RANK_OUT, dimsm, NULL);
    hsize_t offset_out[1] = {0};
    hsize_t count_out[1] = {NX_SUB};
    status = H5Sselect_hyperslab(memspace, H5S_SELECT_SET, offset_out, NULL, count_out, NULL);

    status = H5Dread(dataset, H5T_NATIVE_INT, memspace, dataspace, H5P_DEFAULT, data_out);

    if (debug_bool) {
        if (dclass == H5T_INTEGER) {
            std::cout << "Dataset has Integer Type" << std::endl;
        }
        if (order == H5T_ORDER_LE) {
            std::cout << "Dataset has LE order" << std::endl;
        }
        std::cout << "nDims = " << dims[0] << std::endl;
        std::cout << "Size is " << size << std::endl;
    }
    H5Sclose(dataspace);
    H5Tclose(datatype);
    H5Dclose(dataset);
    H5Fclose(file);

    return 0;
}
