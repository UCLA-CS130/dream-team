#!/bin/sh

# compiles binary images and stores in webserver
docker build -t httpserver.build .
docker run httpserver.build > binary.tar
tar -xf binary.tar -C ./deploy
rm -f binary.tar

# creates image from deploy director
docker build -t httpserver --file deploy/Dockerfile.run deploy

# transfer image from deploy to aws
docker save -o `pwd`/dockerServerImage httpserver
sudo scp -i myKeyPair.pem dockerServerImage ubuntu@ec2-54-205-194-82.compute-1.amazonaws.com:~    # stores image at home directory