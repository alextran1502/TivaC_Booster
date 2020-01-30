# Program Log
## 04/02/2019
* Implemented lwIP protocol to send UDP package to a specific address on the IP subnet.
* There is a problem with invoking a send function `udp_sendto()` in the `dytran_send_data()` (this requires passing udp pointer into the function -> There might be null pointer that caused the system hang). If the data buffer is filled in the `dytran_send_data()` function, the invoking call will work. 
```C
    dytran_send_data(udp_buffer);                                               // Data packaged is filled in this function

    udp_package_ptr = pbuf_alloc(PBUF_TRANSPORT, 100, PBUF_RAM);
    udp_package_ptr->payload = (void *)udp_buffer;
    udp_package_ptr->tot_len = strlen(udp_buffer);
    udp_package_ptr->len = strlen(udp_buffer);
    
    udp_sendto(local_udp_client, udp_package_ptr, &udpDestIpAddr, 2283);        // Invoking the sending method here
    pbuf_free(udp_package_ptr);
```
## 03/22/2019
* First test with Newawrk setting.
* Data is sending out using Serial since LinuxBox CAN module is having an issue.
* Implementing Watchdog timer to avoid system hang.

## 03/14/2019
* Implemented CAN BUS
* Moved away from using CMSIS DSP math library since we need to put all of the data into a buffer and the buffer size takes up a lot of space in RAM. 
* Implemented 2D array for 12 dytran sensors. Each element is an array with 3 indexes [Current value, Maximum Value, Minimum Value].

## 02/15/2019
* Optimization level 2 must be enable to use with `arm_max_q31`
* `adc_array_index` should not have `volatile` declaration otherwise program will crash
* The ADC module is polling more than 1MSPS/64 = 15.625kHZ -> Need to investigate why doesn't the rate of hardware oversampling affect the read rate.
  