openblas-benchmark
==================
Starting on a fresh Ubuntu 12.04.

Install essential tools
`sudo apt-get install build-essential subversion git cmake`

Install Python if you want
`sudo apt-get install python-numpy python-scipy python-matplotlib ipython ipython-notebook`

Install OpenBLAS using the package manager
`sudo apt-get install libopenblas-dev`

Install gnuplot and htop
`sudo apt-get install gnuplot htop`

View the topology of the system
sudo apt-get install hwloc
lstopo
# how many processors are there? HOw many hyperthreads?

# Test this benchmark with 2 versions with different thread numbers
git clone https://github.com/zed/woltan-benchmark.git
export OPENBLAS_NUM_THREADS=1
make clean; make

export OPENBLAS_NUM_THREADS=
make clean; make
# compare the results; observe with htop that 2 processors are fully used.

# Download Armadillo
wget http://sourceforge.net/projects/arma/files/armadillo-4.100.2.tar.gz
tar xvf armadillo-4.100.2.tar.gz 

sudo apt-get install cmake libopenblas-dev liblapack-dev libarpack2-dev
#run cmake . in armadillo folder. Armadillo does not find OpenBLAS
sudo ln -s /usr/lib/openblas-base/libopenblas.so /usr/lib/libopenblas.so
# now Armadillo finds OpenBLAS
# build armadillo
cmake .
make
sudo make install
#enter exampes folder and build tests
make
# run tests
./example1
./example2
# for some reason Armadillo installed itself in /usr/local/lib
LD_LIBRARY_PATH=/usr/local/lib ./example1
LD_LIBRARY_PATH=/usr/local/lib ./example2

# Second benchmark from nghiaho.com
mkdir nghiaho.com
cd nghiaho.com
wget http://nghiaho.com/uploads/code/test_matrix_lib.cpp
# edit out references to Eigen and OpenCV from file
# build 
g++ test_matrix_lib.cpp -o test_matrix_lib -lopencv_core -larmadillo -lgomp -fopenmp -march=native -O3
OPENBLAS_NUM_THREADS= LD_LIBRARY_PATH=/usr/local/lib ./test_matrix_lib

