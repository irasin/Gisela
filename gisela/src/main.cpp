// #if defined(USE_CLHPP)
#include <CL/opencl.hpp>
// #else
// #    include <CL/cl.hpp>
// #endif
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace gisela {

extern const std::map<std::string, std::vector<unsigned char>> cl_src;

}

int main() {
    cl_int err = CL_SUCCESS;

    std::vector<cl::Platform> platforms;
    cl::Platform::get(&platforms);
    if (platforms.size() == 0) {
        std::cout << "Platform size 0\n";
        return -1;
    }
    cl_context_properties properties[] = {
        CL_CONTEXT_PLATFORM, (cl_context_properties)(platforms[0])(), 0};
    cl::Context context(CL_DEVICE_TYPE_GPU, properties);

    std::vector<cl::Device> devices = context.getInfo<CL_CONTEXT_DEVICES>();

    std::string program_name = "hello";

    std::string helloStr(gisela::cl_src.find(program_name)->second.begin(),
                         gisela::cl_src.find(program_name)->second.end());

    // std::string helloStr(cl_src.find(program_name)->second.begin(),
    //                      cl_src.find(program_name)->second.end());
    std::cout << helloStr << std::endl;
    cl::Program program_ = cl::Program(context, helloStr);
    program_.build(devices);

    cl::Kernel kernel(program_, "hello", &err);

    cl::Event        event;
    cl::CommandQueue queue(context, devices[0], 0, &err);
    queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(2, 2),
                               cl::NullRange, NULL, &event);

    event.wait();

    return EXIT_SUCCESS;
}

// const char* helloStr = "__kernel void "
//                        "hello(void) "
//                        "{ "
//                        "  printf(\"hello world\\n\");"
//                        "} ";

// int main(void) {
//     cl_int                    err = CL_SUCCESS;
//     std::vector<cl::Platform> platforms;
//     cl::Platform::get(&platforms);
//     if (platforms.size() == 0) {
//         std::cout << "Platform size 0\n";
//         return -1;
//     }
//     cl_context_properties properties[] = {
//         CL_CONTEXT_PLATFORM, (cl_context_properties)(platforms[0])(), 0};
//     cl::Context context(CL_DEVICE_TYPE_GPU, properties);

//     std::vector<cl::Device> devices = context.getInfo<CL_CONTEXT_DEVICES>();

//     cl::Program program_ = cl::Program(context, std::string(helloStr));
//     program_.build(devices);

//     cl::Kernel kernel(program_, "hello", &err);

//     cl::Event        event;
//     cl::CommandQueue queue(context, devices[0], 0, &err);
//     queue.enqueueNDRangeKernel(kernel, cl::NullRange, cl::NDRange(2, 2),
//                                cl::NullRange, NULL, &event);

//     event.wait();

//     return EXIT_SUCCESS;
// }

// #include <algorithm>
// #include <cstdlib>
// #include <fstream>
// #include <iostream>
// #include <vector>

// #define LENGTH (1024)
// #define TOL (0.001)

// // pick up device type from compiler command line or from the default type
// #ifndef DEVICE
// #    define DEVICE CL_DEVICE_TYPE_DEFAULT
// #endif

// float gen_random() {
//     return rand() / (float)RAND_MAX;
// }

// std::string load_program(std::string input) {
//     std::ifstream stream(input.c_str());
//     if (!stream.is_open()) {
//         std::cout << "Cannot open file: " << input << std::endl;
//         exit(1);
//     }
//     return std::string(std::istreambuf_iterator<char>(stream),
//                        (std::istreambuf_iterator<char>()));
// }

// int main() {
//     // declare host containers
//     std::vector<float> h_a(LENGTH);
//     std::vector<float> h_b(LENGTH);
//     std::vector<float> h_c(LENGTH);

//     // declare device containers
//     cl::Buffer d_a;
//     cl::Buffer d_b;
//     cl::Buffer d_c;

//     // fill host containers with random numbers
//     std::generate(h_a.begin(), h_a.end(), gen_random);
//     std::generate(h_b.begin(), h_b.end(), gen_random);

//     // create a context
//     cl::Context context(DEVICE);

//     // load in kernel source, creating a program object for the context
//     cl::Program program(
//         context, load_program("D://Code//test_opencl//gisela//src//vadd.cl"),
//         true);

//     // get the command queue
//     cl::CommandQueue queue(context);

//     // create the kernel functor
//     auto vadd =
//         cl::compatibility::make_kernel<cl::Buffer, cl::Buffer, cl::Buffer,
//         int>(
//             program, "vadd");

//     // copy data to device
//     d_a = cl::Buffer(context, begin(h_a), end(h_a), true);
//     d_b = cl::Buffer(context, begin(h_b), end(h_b), true);

//     // allocate results container
//     d_c = cl::Buffer(context, CL_MEM_WRITE_ONLY, sizeof(float) * LENGTH);

//     // run calculations
//     vadd(cl::EnqueueArgs(queue, cl::NDRange(LENGTH)), d_a, d_b, d_c, LENGTH);

//     queue.finish();

//     cl::copy(queue, d_c, begin(h_c), end(h_c));

//     // test the results
//     int   correct = 0;
//     float tmp;
//     for (int i = 0; i < LENGTH; i++) {
//         tmp = h_a[i] + h_b[i];        // expected value for d_c[i]
//         tmp -= h_c[i];                // compute errors
//         if (tmp * tmp < TOL * TOL) {  // correct if square deviation is less
//             correct++;                //  than tolerance squared
//         } else {
//             printf(" tmp %f h_a %f h_b %f  h_c %f \n", tmp, h_a[i], h_b[i],
//                    h_c[i]);
//         }
//     }

//     printf("vector add to find C = A+B:  %d out of %d results were
//     correct.\n",
//            correct, LENGTH);

//     return 0;
// }

// // // vadd.cl
// // __kernel void vadd(
// //    __global float* a,
// //    __global float* b,
// //    __global float* c,
// //    const unsigned int count)
// // {
// //    int i = get_global_id(0);
// //    if(i < count)  {
// //        c[i] = a[i] + b[i];
// //    }
// // }
