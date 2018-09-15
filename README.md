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

  * [GNURadio v3.7.10+](https://github.com/gnuradio/gnuradio)
  * [gr-mapper](https://github.com/gr-vt/gr-mapper) (used for BER example)
  
  Please see the wimax_ldpc_lib [README](https://github.com/myersw12/wimax_ldpc_lib/blob/master/README.md) for additional requirements.
  
 ## Examples
 
 Example flowgraphs are contained in the `/examples` directory.
 
 * ldpc_encoder_example.grc - Simple example of using the ldpc_encoder block to encode pdu messages
 * ldpc_encoder_decoder_example.grc - Similar to the above example, adds the ldpc_decoder block.
 * ldpc_mapper_BER_example.grc - Requires the gr-mapper OOT module.  This is a modified version of the prbs_test.grc flowgraph found within the gr-mapper OOT module.  The ldpc_encoder and ldpc_decoder blocks are added to give the flowgraph some FEC.  It is fun to compare the Bit Error Rate (BER) with and without LDPC as well as between different LDPC rates.
 * ldpc_BER_example.grc - Requires the gr-mapper OOT module.  Example flowgraph to play around with BER rates.  The receiver from the flowgraph above is removed so that only the LDPC codes are tested.
 * QPSK_BER_example.grc - Requires the gr-mapper OOT module.  This is a plain QPSK reference for the above flowgraph.  Compare the results of the two to see the improvement given by the LDPC FEC.
 * gnuradio_ldpc_BER_example.grc - Requires the gr-mapper OOT module.  BER rates using the default LDPC encoder/decoder provided by GNURadio.  
 
## BER Theory
The Bit Error Rate (BER) of a digital transmission system is the rate at which errors occur during transmission.  These errors are caused due to noise, interference, and imperfections in either the transmitter or receiver.  The BER of a system is one of the most fundamental ways to measure performance.
 
There are two types of examples provided with this project that give BER results for the LDPC codes.  The first, ldpc_mapper_BER_example.grc, provides an example of a simple transmitter/receiver over a channel.  The BER measurements from this flowgraph are with respect to SNR and show the performance of the receiver and LDPC codes.

The second (ldpc_BER_example.grc, QPSK_BER_example.grc, and gnuradio_ldpc_BER_example) provides an example of QPSK over Additive Gaussian White Noise (AWGN).  There are no imperfections in the transmitter or receiver, so these provide an results that closely match the theoretical predictions.  For reference, theoretical BER plots are shown below.
 ![alt text](https://github.com/myersw12/gr-WiMAX_LDPC/blob/master/docs/ber_plots.png)
 
The plots are given by the following equations:

![alt text](https://github.com/myersw12/gr-WiMAX_LDPC/blob/master/docs/bpsk.gif)

![alt text](https://github.com/myersw12/gr-WiMAX_LDPC/blob/master/docs/qpsk.gif)

![alt text](https://github.com/myersw12/gr-WiMAX_LDPC/blob/master/docs/mqam.gif)

![alt text](https://github.com/myersw12/gr-WiMAX_LDPC/blob/master/docs/erfc.gif)

![alt text](https://github.com/myersw12/gr-WiMAX_LDPC/blob/master/docs/bits_per_sym.gif)
 
 ## Installation
 
 To install the OOT module, perform the following steps:

   * clone the repository: git clone https://github.com/myersw12/gr-WiMAX_LDPC.git
   * create the build directory: cd gr-WiMAX_LDPC && mkdir build && cd build
   * run cmake: cmake ../
   * run make: make -j4
   * install: sudo make install && sudo ldconfig
