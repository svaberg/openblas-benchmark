OPENBLAS_RUNTIME_PATH=/opt/OpenBLAS/lib:/usr/local/lib
NUMBER_OF_CORES=$(shell nproc)

$(info OPENBLAS_RUNTIME_PATH=$(OPENBLAS_RUNTIME_PATH))
$(info NUMBER_OF_CORES=$(NUMBER_OF_CORES))

NUMBERS := $(shell seq 1 ${NUMBER_OF_CORES})
RESULTS := $(addprefix results/results_,${NUMBERS})

plot: $(addsuffix .data, $(RESULTS))
	gnuplot -persist -e "max_threads=$(NUMBER_OF_CORES)" gnuplot/plot.gplt

$(addsuffix .data,$(RESULTS)): bin/main results
	OPENBLAS_NUM_THREADS=$(subst .data,,$(subst results/results_,,$(@))) LD_LIBRARY_PATH=$(OPENBLAS_RUNTIME_PATH) ./bin/main

bin/main: src/main.cpp bin
	g++ src/main.cpp -o bin/main -larmadillo

bin:
	mkdir bin

results:
	mkdir results

clean:
	rm -rf results
	rm -rf bin
