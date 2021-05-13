#include <iostream>
#include "H5Cpp.h"
#include <string>
#include <vector>
#include <map>
#include "h5_sandbox.h"
const int NX = 900000;
const int NX_SUB = 900000;
const int RANK_OUT = 1;
int run_it() {
    std::string filepath{"../data/outfile.h5"};
    H5::H5File f{filepath, H5F_ACC_RDONLY};
    H5::DataSet dataset = f.openDataSet("label");
    H5T_class_t type_class = dataset.getTypeClass();
    std::cout << "type_class: " <<  type_class << std::endl;
    if( type_class == H5T_INTEGER ) {

        int data_out[NX];
        for (int i = 0; i < NX; i++) {
            data_out[i] = -3;
        }
        std::cout << "Data set has INTEGER type" << std::endl;
        // Get the integer datatype
        H5::IntType intype = dataset.getIntType();

        // Get order of datatype and print message if it's a little endian.
        H5std_string order_string;
        H5T_order_t order = intype.getOrder(order_string);
        std::cout << order_string << std::endl;

        // Get size of the data element stored in file and print it.
        size_t size = intype.getSize();
        std::cout << "Data size is " << size << std::endl;

        // Get dataspace of the dataset.
        H5::DataSpace dataspace = dataset.getSpace();

        // Get the number of dimensions in the dataspace.
        int rank = dataspace.getSimpleExtentNdims();

        // Get the dimension size of each dimension in the dataspace and display them.
        hsize_t dims_out[1];
        int ndims = dataspace.getSimpleExtentDims(dims_out, NULL);
        std::cout << "ndims: " << ndims << std::endl;
        std::cout << "rank " << rank << ", dimensions " << (unsigned long)(dims_out[0]) << std::endl;

        // Define hyperslab in the dataset; implicitly giving strike and block NULL.
        hsize_t offset[1];   // hyperslab offset in the file
        hsize_t count[1];    // size of the hyperslab in the file
        offset[0] = dims_out[0]-NX;
        count[0] = NX_SUB;
        dataspace.selectHyperslab(H5S_SELECT_SET, count, offset);

        //  Define the memory dataspace.
        hsize_t dimsm[1];              /* memory space dimensions */
        dimsm[0] = NX;
        H5::DataSpace memspace{RANK_OUT, dimsm};

        // Define memory hyperslab.
        hsize_t offset_out[1];   // hyperslab offset in memory
        hsize_t count_out[1];    // size of the hyperslab in memory
        offset_out[0] = 0;
        count_out[0]  = NX_SUB;
        memspace.selectHyperslab(H5S_SELECT_SET, count_out, offset_out);
        
        // Read data from hyperslab in the file into the hyperslab in memory and display the data.
        dataset.read(data_out, H5::PredType::NATIVE_INT, memspace, dataspace );
        

        std::vector<int> v (data_out, data_out + (sizeof(data_out)/sizeof(data_out[0])));
    }
    std::cout << xxxx; 
    std::cout <<"done fool" << std::endl;

    return 0;
}
