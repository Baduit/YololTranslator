FROM baduit/my-basic-cpp-env:latest

WORKDIR /yololtranslator/core
COPY . /yololtranslator

WORKDIR /yololtranslator/core
RUN cmake -B build -DCMAKE_TOOLCHAIN_FILE="$VCPKG_TOOLCHAIN" .
RUN cmake --build build