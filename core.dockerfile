FROM baduit/my-basic-cpp-env:latest

WORKDIR /yololtranslator/core
COPY . /yololtranslator

RUN apt update
RUN apt install python3 python3-dev -y

RUN cmake -B build -DCMAKE_TOOLCHAIN_FILE="$VCPKG_TOOLCHAIN" .
RUN cmake --build build