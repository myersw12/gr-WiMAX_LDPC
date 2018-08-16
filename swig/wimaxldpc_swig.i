/* -*- c++ -*- */

#define WIMAXLDPC_API

%include "gnuradio.i"			// the common stuff

//load generated python docstrings
%include "wimaxldpc_swig_doc.i"

%{
#include "wimaxldpc/ldpc_encoder.h"
#include "wimaxldpc/ldpc_decoder.h"
%}


%include "wimaxldpc/ldpc_encoder.h"
GR_SWIG_BLOCK_MAGIC2(wimaxldpc, ldpc_encoder);
%include "wimaxldpc/ldpc_decoder.h"
GR_SWIG_BLOCK_MAGIC2(wimaxldpc, ldpc_decoder);
