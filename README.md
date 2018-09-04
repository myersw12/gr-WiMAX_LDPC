# gr-WiMAX_LDPC

This is a GNU Radio out of tree module that makes it easy to add LDPC forward error correction codes to flowgraphs.  The code performing the LDPC encoding/decoding is from here: [wimax_ldpc_lib](https://github.com/myersw12/wimax_ldpc_lib)

## Overview

The codes provided by this project are from the WiMAX Standard (802.16e).  The 802.16e standard contains very flexible code sizes and rates, making them a good candidate for use elsewhere.  The codeword sizes range from 576 to 2304 bits.  The coderates available in this module are as follows:
  * 1/2 
  * 2/3A
  * 2/3B
  * 3/4A
  * 5/6

##  Requirements

  * GNURadio v3.7.10+
  * gr-mapper (used for BER example)
  
  Please see the wimax_ldpc_lib [README](https://github.com/myersw12/wimax_ldpc_lib/blob/master/README.md) for additional requirements.
  
 ## Examples
 
 Example flowgraphs are contained in the `/examples` directory.
 
 * ldpc_encoder_example.grc - Simple example of using the ldpc_encoder block to encode pdu messages
 * ldpc_encoder_decoder_example.grc - Similar to the above example, adds the ldpc_decoder block.
 * ldpc_BER_example.grc - Requires the gr-mapper OOT module.  This is a modified version of the prbs_test.grc flowgraph found within the gr-mapper OOT module.  The ldpc_encoder and ldpc_decoder blocks are added to give the flowgraph some FEC.  It is fun to compare the Bit Error Rate (BER) with and without LDPC as well as between different LDPC rates.
 
 ## Installation
 
 To install the OOT module, perform the following steps:

   * clone the repository: git clone git@github.com:myersw12/gr-WiMAX_LDPC.git
   * create the build directory: cd gr-WiMAX_LDPC && mkdir build && cd build
   * run cmake: cmake ../
   * run make: make -j4
   * install: sudo make install && sudo ldconfig
