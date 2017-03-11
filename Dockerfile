FROM ubuntu:14.04

RUN apt-get update
RUN apt-get install -y libboost-all-dev
RUN apt-get install -y make
RUN apt-get install -y g++
RUN apt-get install openssl
RUN apt-get install libssl-dev

WORKDIR /opt/httpserver
COPY . /opt/httpserver

RUN make clean && make

CMD tar -cf - bin/webserver

# EXPOSE 8080:8080
# CMD ["./bin/webserver", "./src/config_file"]