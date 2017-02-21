#ifndef STD_ARITHCODE_H
#define STD_ARITHCODE_H

#include "ac.h"
#include <vector>

typedef unsigned char uchar;
typedef std::vector<uchar> Stream;

inline void calc_cdf(Stream& input, std::vector<real>& cdf){
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
inline void encode(Stream& input, Stream& output, std::vector<real>& cdf){
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

inline void decode(Stream& input, Stream& output, std::vector<real>& cdf){
    uchar *in = &input[0];
    uchar *out=0;      // output buffer
    size_t countof_input = input.size();
    size_t countof_output = 0; // number of symbols in output buffer

    decode_u8_u8( &out,&countof_output,
                   in, countof_input,
                   &cdf[0], cdf.size()-1);

    // save result
    output.resize(countof_output);
    for(size_t i=0; i<countof_output; i++){
        output[i] = out[i];
    }
    free(out);
}


#endif // STD_ARITHCODE_H
