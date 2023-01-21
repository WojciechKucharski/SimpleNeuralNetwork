set(sources
    src/main.cpp
)

set(exe_sources
		src/main.cpp
		${sources}
)

set(headers
    include/SimpleNeuralNetwork/Matrix.hpp
    include/SimpleNeuralNetwork/Model.hpp
)

set(test_sources
  src/Matrix_test.cpp
  src/Model_test.cpp
)
