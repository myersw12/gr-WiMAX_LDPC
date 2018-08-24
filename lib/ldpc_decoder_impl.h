/* -*- c++ -*- */
/* 
 * Copyright 2018 <+YOU OR YOUR COMPANY+>.
 * 
 * This is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3, or (at your option)
 * any later version.
 * 
 * This software is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this software; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 51 Franklin Street,
 * Boston, MA 02110-1301, USA.
 */

#ifndef INCLUDED_WIMAXLDPC_LDPC_DECODER_IMPL_H
#define INCLUDED_WIMAXLDPC_LDPC_DECODER_IMPL_H

#include <wimaxldpc/ldpc_decoder.h>
#include <wimax_ldpc_lib/include/enums.h>
#include <wimax_ldpc_lib/include/ldpc_decoder.h>

namespace gr {
  namespace wimaxldpc {

    class ldpc_decoder_impl : public ldpc_decoder
    {
        private:
            uint8_t* d_dataword;
            uint8_t* d_codeword;
            float*   d_soft_codeword;
            
            unsigned int d_dataword_len;
            unsigned int d_max_iterations;
            unsigned int  d_z;
            
            bool     d_soft;
            
            coderate    d_rate;
            
            pmt::pmt_t d_in_port;
            pmt::pmt_t d_out_port;
            
            wimax_ldpc_lib::ldpc_decoder *d_decoder;

        public:
            ldpc_decoder_impl(unsigned int rate, unsigned int z,
                              unsigned int max_iterations,
                              bool soft,
                              unsigned int num_threads);
            
            ~ldpc_decoder_impl();
            
            void handle_codeword(pmt::pmt_t msg);

    };

  } // namespace wimaxldpc
} // namespace gr

#endif /* INCLUDED_WIMAXLDPC_LDPC_DECODER_IMPL_H */

