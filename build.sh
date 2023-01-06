rm -rf build
mkdir build/ && cd build/
cmake .. -DCMAKE_INSTALL_PREFIX=/absolute/path/to/custom/install/directory | grep "err"
cmake --build . --target install | grep "err"
cmake --build build --target install --config Release | grep "err"
echo "--- Testing ---"
ctest -C Release --output-on-failure
cd ..