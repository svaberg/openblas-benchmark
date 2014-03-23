openblas-benchmark
==================

### Installation
Clone the repository, enter the folder and say `make`. A plot should appear showing the execution time for 1 thread and for 2 threads. If things don't work consider following some of the instructions below.

### Possible prerequisites
Starting on a fresh Ubuntu 12.04.

Install essential tools:
`sudo apt-get install build-essential subversion git cmake`

Install Python if you want (try without, it should not be needed):
`sudo apt-get install python-numpy python-scipy python-matplotlib ipython ipython-notebook`

Install OpenBLAS using the package manager:
`sudo apt-get install libopenblas-dev`

Install gnuplot and htop:
`sudo apt-get install gnuplot htop`

View the topology of the system:
```
sudo apt-get install hwloc
lstopo
```
How many processors are there? How many hyperthreads?

Download Armadillo:
```
wget http://sourceforge.net/projects/arma/files/armadillo-4.100.2.tar.gz
tar xvf armadillo-4.100.2.tar.gz 
```

Install Armadillo required packages:
```
sudo apt-get install cmake libopenblas-dev liblapack-dev libarpack2-dev
```
Run `cmake .` in armadillo folder. Armadillo does not find OpenBLAS
```
sudo ln -s /usr/lib/openblas-base/libopenblas.so /usr/lib/libopenblas.so
```
now Armadillo finds OpenBLAS.

Build armadillo:
```
cmake .
make
sudo make install
```

Enter exampes folder and build and run tests:
```
make
./example1
./example2
# for some reason Armadillo installed itself in /usr/local/lib
LD_LIBRARY_PATH=/usr/local/lib ./example1
LD_LIBRARY_PATH=/usr/local/lib ./example2
```

If all of this works it should be possible to go back to the start and run the program.
