#!/bin/sh

docker build -t httpserver --file deploy/Dockerfile.run deploy
docker run --rm -t -p 8080:8080 httpserver