# Neural Network - C Library
Neural network library with feed forward functionality **only**

API docs have not yet been made, please refer to the header files for more information
Additionally, a basic neural network test has been placed at the top of **src/main.c**, with other code examples below that have been commented out.

### Installation
Run the following commands to install the library (local installation)
```
git clone https://github.com/josephbiwer/NeuralNetworkC.git
cd NeuralNetworkC
./install
```

To run the program, make the program and then exectute the *run* file.
```
make
./build/run
```

### Execution
A sample program can be executed with the above commands, which loads in data from a file  (*data/order.txt*), followed by loading the matricies into memory from the specified files in *data/order.txt*. The neural network then performs the feed forward algorithm on the data and prints the output to the terminal.
