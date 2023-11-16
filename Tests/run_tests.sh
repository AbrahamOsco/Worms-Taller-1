mkdir build
cd build
cmake -DTEST_MODE_ON=ON ..
make
./tests >test_results.txt