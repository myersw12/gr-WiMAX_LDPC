# gr-WiMAX_LDPC

This is a GNU Radio out of tree module that makes it easy to add LDPC forward error correction codes to flowgraphs.  The code performing the LDPC encoding/decoding is from here:  [wimax_ldpc_lib](https://github.com/myersw12/wimax_ldpc_lib)

## Overview

The codes used by the OOT Module are from the WiMAX Standard (802.16e).  The 802.16e standard contains very flexible code sizes and rates, making them a good candidate for use elsewhere.  The codeword sizes range from 576 to 2304 bits.  The coderates available in this module are as follows:
  * 1/2 
  * 2/3A
  * 2/3B
  * 3/4A
  * 5/6
  
  
##  Requirements

  * GNURadio v3.7+
  * gr-mapper (used for BER example)
  
  Please see the wimax_ldpc_lib README for additional requirements.