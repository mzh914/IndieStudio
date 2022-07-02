mkdir build
cmake -S . -B build/
cd build && (make -j4 || make && ./bomberman)
