/* -*- c++ -*- */
/* 
 * Copyright 2018 William Myers.
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
#include "ldpc_decoder_impl.h"

namespace gr {
  namespace wimaxldpc {

    ldpc_decoder::sptr
    ldpc_decoder::make(unsigned int rate,
                       unsigned int z,
                       unsigned int max_iterations,
                       bool soft,
                       unsigned int num_threads)
    {
      return gnuradio::get_initial_sptr
        (new ldpc_decoder_impl(rate, z, max_iterations, soft, num_threads));
    }

    /*
     * The private constructor
     */
    ldpc_decoder_impl::ldpc_decoder_impl(unsigned int rate,
                                         unsigned int z,
                                         unsigned int max_iterations,
                                         bool soft,
                                         unsigned int num_threads)
      : gr::block("ldpc_decoder",
              gr::io_signature::make(0, 0, 0),
              gr::io_signature::make(0, 0, 0))
    {
        d_rate = (coderate)rate;
        d_z = z;
        d_max_iterations = max_iterations;
        d_soft = soft;
        
        d_codeword_len = (d_z / 96.0) * BASE_LDPC_BLOCK_LEN;
        
        d_in_port = pmt::mp("in");
        d_out_port = pmt::mp("out");
        
        message_port_register_in(d_in_port);
        message_port_register_out(d_out_port);
        
        set_msg_handler(d_in_port, boost::bind(&ldpc_decoder_impl::handle_codeword, this, _1));

        d_decoder = new wimax_ldpc_lib::ldpc_decoder(d_rate, z, d_max_iterations, num_threads);
        
        switch(rate)
        {
            case (HALFRATE):
            {
                d_dataword_len = d_codeword_len / 2; 
                break;
            }
            
            case (TWOTHIRDSA):
            case (TWOTHIRDSB):
            {
                d_dataword_len = (d_codeword_len * 2) / 3;
                break;
            }
            
            case (THREEQUARTERSB):
            case (THREEQUARTERSA):
            {
                d_dataword_len = (d_codeword_len * 3) / 4;
                break;
            }
            
            case (FIVESIXTHS):
            {
                d_dataword_len = (d_codeword_len * 5) / 6;
                break;
            }
            
            default:
            {
                printf("[!]test_encoder - Invalid Coderate: %d\n", rate);
                throw std::exception();
                break;
            }
        }
        
        
        if(d_soft)
            d_codeword = (int8_t*)malloc(d_codeword_len * sizeof(uint8_t));
        else
            d_soft_codeword = (float*)malloc(d_codeword_len * sizeof(float));

        
    }

    /*
     * Our virtual destructor.
     */
    ldpc_decoder_impl::~ldpc_decoder_impl()
    {
        
        if(d_soft)
            free(d_soft_codeword);
        else
            free(d_codeword);
        
        delete d_decoder;
        
    }
    
    void ldpc_decoder_impl::handle_codeword(pmt::pmt_t msg)
    {
        unsigned int packet_len = 0;
        unsigned int scale = 1;
        
        // if we are dealing with floats, divide by the size of a float
        if(d_soft)
            scale = sizeof(float);
        
        if (pmt::is_pair(msg))
        {
            pmt::pmt_t pdu_meta = pmt::car(msg);
            pmt::pmt_t pdu_data = pmt::cdr(msg);
            
            packet_len = pmt::blob_length(pdu_data);
            
            if ((packet_len/scale) != d_codeword_len)
            {
                printf("[!] ldpc_decoder_impl.cc - invalid packet len: %d\n", packet_len);
                return;
            }
            
            if(d_soft)
                d_soft_codeword = (float*)pmt::blob_data(pdu_data);
            else
                d_codeword = (int8_t*)pmt::blob_data(pdu_data);
            
            if(d_soft)
                d_decoder->decode(d_soft_codeword, d_codeword);
            else
                d_decoder->decode(d_codeword, d_codeword);
            
            pmt::pmt_t meta = pmt::make_dict();
            meta = pmt::dict_add(meta, pmt::mp("packet_len"), pmt::from_long(d_dataword_len));
            
            pmt::pmt_t payload = pmt::make_blob(d_codeword, d_dataword_len);
            
            pmt::pmt_t msg_out = pmt::cons(meta, payload);
            
            message_port_pub(d_out_port, msg_out);
            
        } 
        
    }



  } /* namespace wimaxldpc */
} /* namespace gr */

