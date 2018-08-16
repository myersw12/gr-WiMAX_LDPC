/* -*- c++ -*- */
/* 
 * Copyright 2018 myersw12.
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

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include <gnuradio/io_signature.h>
#include "ldpc_encoder_impl.h"

#define NUM_THREADS 4

namespace gr {
  namespace wimaxldpc {

    ldpc_encoder::sptr
    ldpc_encoder::make(unsigned int rate , unsigned int z)
    {
      return gnuradio::get_initial_sptr
        (new ldpc_encoder_impl(rate, z));
    }

    /*
     * The private constructor
     */
    ldpc_encoder_impl::ldpc_encoder_impl(unsigned int rate, unsigned int z)
      : gr::block("ldpc_encoder",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0))
    {
        d_rate = (coderate)rate;
        d_z = z;
        
        d_codeword_len = (d_z / 96.0) * BASE_LDPC_BLOCK_LEN;
        unsigned int dataword_len = 0;
             
        d_in_port = pmt::mp("in");
        d_out_port = pmt::mp("out"); 
        
        message_port_register_in(d_in_port);
        message_port_register_out(d_out_port);
        
        set_msg_handler(d_in_port, boost::bind(&ldpc_encoder_impl::handle_dataword, this, _1));
        
        d_encoder = ldpc_encoder(rate, z, NUM_THREADS);
        
        switch(d_rate)
        {
            case (HALFRATE):
            {
                dataword_len = d_codeword_len / 2; 
                break;
            }
            
            case (TWOTHIRDSA):
            case (TWOTHIRDSB):
            {
                dataword_len = (d_codeword_len * 2) / 3;
                break;
            }
            
            case (THREEQUARTERSA):
            case (THREEQUARTERSB):
            {
                dataword_len = (d_codeword_len * 3) / 4;
                break;
            }
            
            case (FIVESIXTHS):
            {
                dataword_len = (d_codeword_len * 5) / 6;
                break;
            }
            
            default:
            {
                printf("[!]test_encoder - Invalid Coderate: %d\n", rate);
                throw std::exception();
                break;
            }
        }
        
        d_dataword = (uint8_t*)malloc(dataword_len * sizeof(uint8_t));
        d_codeword = (uint8_t*)malloc(d_codeword_len * sizeof(uint8_t));
        
    }

    /*
     * Our virtual destructor.
     */
    ldpc_encoder_impl::~ldpc_encoder_impl()
    {
        free(d_dataword);
        free(d_codeword);
    }

    void ldpc_encoder_impl::handle_dataword(pmt::pmt_t msg)
    {
        
        unsigned int packet_len = 0;
        
        if (pmt::is_pair(msg))
        {
            pmt::pmt_t r_packet_len = pmt::dict_ref(pmt::car(msg), pmt::mp("packet_len"), pmt::PMT_NIL);
        
            if (pmt::is_integer(r_packet_len)
                packet_len = pmt::to_long(r_packet_len);
            else
            {
                printf("[!] ldpc_encoder_impl.cc - invalid packet len\n");
                return;
            }
            
            pmt::pmt_t r_data_blob = pmt::cdr(msg);
            
            if (pmt::is_blob(r_data_blob))
                d_dataword = (uint8_t*)pmt::blob_data(r_data_blob);
            else
            {
                printf("[!] ldpc_encoder_impl.cc - invalid data blob\n");
                return;
            }
            
            d_encoder.encode_data(d_dataword, d_codeword);
            
            pmt::pmt_t meta = pmt::make_dict();
            meta = pmt::dict_add(meta, pmt::mp("packet_len"), pmt::from_long(d_codeword_len));
            
            pmt::pmt_t payload - pmt::make_blob(d_codeword, d_codeword_len);
            
            pmt::pmt_t msg_out = pmt::cons(meta, payload);
            
        }
        
    }
    
  } /* namespace wimaxldpc */
} /* namespace gr */

