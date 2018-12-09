FROM ubuntu:latest
COPY . /app
WORKDIR /app/build_docker
RUN apt-get update
RUN apt-get install -yq cmake g++
ENV CXX g++
RUN cmake -G 'Unix Makefiles' ..
RUN make
RUN make test
