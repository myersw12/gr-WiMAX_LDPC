/* -*- c++ -*- */

#define WIMAX_LDPC_API

%include "gnuradio.i"           // the common stuff

//load generated python docstrings
%include "WiMAX_LDPC_swig_doc.i"

%{
#include "WiMAX_LDPC/ldpc_decoder.h"
#include "WiMAX_LDPC/ldpc_encoder.h"
%}

%include "WiMAX_LDPC/ldpc_decoder.h"
GR_SWIG_BLOCK_MAGIC2(WiMAX_LDPC, ldpc_decoder);
%include "WiMAX_LDPC/ldpc_encoder.h"
GR_SWIG_BLOCK_MAGIC2(WiMAX_LDPC, ldpc_encoder);
