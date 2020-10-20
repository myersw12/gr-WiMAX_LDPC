/* -*- c++ -*- */
/*
 * Copyright 2020 gr-WiMAX_LDPC author.
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

#ifndef INCLUDED_WIMAX_LDPC_LDPC_ENCODER_IMPL_H
#define INCLUDED_WIMAX_LDPC_LDPC_ENCODER_IMPL_H

#include <WiMAX_LDPC/ldpc_encoder.h>

#include <wimax_ldpc_lib/ldpc_encoder.h>

namespace gr {
  namespace WiMAX_LDPC {

    class ldpc_encoder_impl : public ldpc_encoder
    {
        private:
            uint8_t* d_dataword;
            uint8_t* d_codeword;
            
            unsigned int d_codeword_len;
            unsigned int d_dataword_len;
            
            coderate d_rate;
            unsigned int d_z;
            
            pmt::pmt_t d_in_port;
            pmt::pmt_t d_out_port;
            
            wimax_ldpc_lib::ldpc_encoder *d_encoder;
            
        public:
            ldpc_encoder_impl(unsigned int rate, unsigned int z, unsigned int num_threads);
            ~ldpc_encoder_impl();
            
            void handle_dataword(pmt::pmt_t msg);

    };

  } // namespace WiMAX_LDPC
} // namespace gr

#endif /* INCLUDED_WIMAX_LDPC_LDPC_ENCODER_IMPL_H */

