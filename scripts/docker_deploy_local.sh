#!/bin/sh

docker build -t httpserver.build .
docker run httpserver.build > binary.tar

tar -xf binary.tar -C ./deploy
rm -f binary.tar

# TODO: move static files and config file with deploy command