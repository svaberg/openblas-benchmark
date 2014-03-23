plot: results/results_1.data results/results_2.data
	gnuplot -persist gnuplot/plot.gplt

results/results_1.data: bin/main results
	OPENBLAS_NUM_THREADS=1 LD_LIBRARY_PATH=/usr/local/lib ./bin/main

results/results_2.data: bin/main results
	OPENBLAS_NUM_THREADS=2 LD_LIBRARY_PATH=/usr/local/lib ./bin/main

bin/main: src/main.cpp bin
	g++ src/main.cpp -o bin/main -larmadillo

bin:
	mkdir bin

results:
	mkdir results

clean:
	rm -rf results
	rm -rf bin
