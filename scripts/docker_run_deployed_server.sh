#!/bin/sh

docker build -t httpserver deploy
docker run --rm -t -p 8080:8080 httpserver