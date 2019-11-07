# Neural Network - C Library
Example implementation of the library located in *src/main.c*.

### Notes
- The output of the network is stored in a wrapper struct that just allows the user to change the architecture (shape) of the array... you can directly access the output array though since it will always be a *1xn* vector.
- The *input_data[]* array is to simulate data coming in from the CAN bus that is of type **float**. In the example, the network is set up to have 5 data input values (as it is declared in the initialization of the architecture).
