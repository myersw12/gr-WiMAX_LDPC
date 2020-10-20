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

#ifndef INCLUDED_WIMAX_LDPC_LDPC_ENCODER_H
#define INCLUDED_WIMAX_LDPC_LDPC_ENCODER_H

#include <WiMAX_LDPC/api.h>
#include <gnuradio/block.h>

namespace gr {
  namespace WiMAX_LDPC {

    /*!
     * \brief <+description of block+>
     * \ingroup WiMAX_LDPC
     *
     */
    class WIMAX_LDPC_API ldpc_encoder : virtual public gr::block
    {
     public:
      typedef boost::shared_ptr<ldpc_encoder> sptr;

      /*!
       * \brief Return a shared_ptr to a new instance of WiMAX_LDPC::ldpc_encoder.
       *
       * To avoid accidental use of raw pointers, WiMAX_LDPC::ldpc_encoder's
       * constructor is in a private implementation
       * class. WiMAX_LDPC::ldpc_encoder::make is the public interface for
       * creating new instances.
       */
      static sptr make(unsigned int rate, unsigned int z, unsigned int num_threads);
    };

  } // namespace WiMAX_LDPC
} // namespace gr

#endif /* INCLUDED_WIMAX_LDPC_LDPC_ENCODER_H */

