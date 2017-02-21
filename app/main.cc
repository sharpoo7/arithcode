#include "ac.h"

#include <vector>
#include <iostream>

using namespace std;

typedef unsigned char uchar;
typedef std::vector<uchar> Stream;

inline void calc_cdf(Stream& input, std::vector<float>& cdf){
    uchar *in = &input[0];
    size_t countof_input = input.size();

    float *c = 0;
    size_t nsym = 0;            // number of symbols in the input alphabet
    // somehow load the data into input array
    cdf_build_8u(&c,&nsym,in,countof_input);  // get the symbol statistics

    cdf.resize(nsym+1);
    for(size_t i=0; i<=nsym; i++){
        cdf[i] = c[i];
    }

    free(c);
}

// input uchar and output uchar stream
inline void encode(Stream& input, Stream& output, std::vector<float>& cdf){
    uchar *in = &input[0];
    uchar *out=0;      // output buffer
    size_t countof_input = input.size();
    size_t countof_output = 0; // number of symbols in output buffer

    encode_u8_u8( // encode unsigned chars to a string of bits (1 bit per output symbol)
                  (void**)&out,&countof_output,
                   in, countof_input,
                   &cdf[0], cdf.size());

    // save result
    output.resize(countof_output);
    for(size_t i=0; i<countof_output; i++){
        output[i] = out[i];
    }

    free(out);
}

template<typename T>
void printf_vec(std::vector<T>& v){
    for(auto it : v){
        std::cout << it << " ";
    }
    std::cout << "\n";
}

int main(int argc, char** argv){
    Stream input = {2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0,
                  2,1,0,0,0,0,0,0,0,0,0,0,3,3,2,3,2,1,0};



    std::vector<float> cdf;
    calc_cdf(input, cdf);

    printf_vec(cdf);

    Stream output;
    encode(input, output, cdf);
    printf_vec(output);
    std::cout << "compression ratio: " << (double)output.size() / input.size() << std::endl;



    return 0;
}
