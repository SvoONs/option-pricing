# Pull stable Debian image
FROM debian:stable

ARG USER
ARG UID
ARG GID

# Install cmake, g++, ...
RUN set -ex;                                                                      \
    apt-get update;                                                               \
    apt-get install -y cmake g++ build-essential git;                \
    mkdir -p /usr/src;                                                            \
    cd /usr/src;

# Copy files into the specified directory in the image
# and set that as the working location
COPY . /usr/src/option-pricing
WORKDIR /usr/src/option-pricing

# Build application
RUN set -ex;                                                                      \
    cd /usr/src/option-pricing/build;                                             \
    cmake ..; make;

# Start terminal
CMD ["/bin/bash"]

LABEL Name=optionpricing Version=0.0.1
