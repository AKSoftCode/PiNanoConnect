#FROM ubuntu:20.04
#FROM python:2
FROM nvcr.io/nvidia/l4t-base:r32.4.3 AS base

RUN apt-get update 
RUN apt-get install git build-essential cmake -y
RUN apt-get install -y python3-pip
RUN pip3 install Jetson.GPIO

# build 
FROM base AS builder

WORKDIR /source
RUN git clone https://github.com/pjueon/JetsonGPIO.git

WORKDIR /source/JetsonGPIO
RUN mkdir build

WORKDIR /source/JetsonGPIO/build
#RUN cmake ../ -DBUILD_EXAMPLES=ON -DJETSON_GPIO_POST_INSTALL=OFF
#RUN make install

# app
FROM base AS app 

# install JetsonGPIO
#COPY --from=builder /source/JetsonGPIO/build/install/ /usr/local/
# COPY --from=builder /lib/udev/rules.d/99-gpio.rules /lib/udev/rules.d/99-gpio.rules

# copy samples and tests
#COPY --from=builder /source/JetsonGPIO/build/samples/ /gpio-cpp/samples
#COPY --from=builder /source/JetsonGPIO/build/tests/ /gpio-cpp/tests

WORKDIR /app
#COPY . .
RUN apt-get update && apt-get install -y \
    build-essential \
    autoconf \
    libtool \
    pkg-config \
    cmake \
    git \
    wget \
    protobuf-compiler


CMD ["/bin/sh", "-c", "bash"]