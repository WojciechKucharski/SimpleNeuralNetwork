# SimpleNeuralNetwork

# Build
mkdir build/ && cd build/
cmake .. -DCMAKE_INSTALL_PREFIX=/absolute/path/to/custom/install/directory
cmake --build . --target install

# Install
cmake --build build --target install --config Release
cmake --build <build_directory> --target install --config <desired_config>

# Run test

cd build          # if not in the build directory already
ctest -C Release  # or `ctest -C Debug` or any other configuration you wish to test
#GoogleTest output as well)