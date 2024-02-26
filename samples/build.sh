#!/usr/bin/env bash
docker run --rm -v "$PWD":/usr/src/myapp -w /usr/src/myapp gcc gcc -g -O -c main.cpp test.cpp