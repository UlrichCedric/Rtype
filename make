#!/bin/bash

cd build && make -j 4 && cp bin/r-type_server .. && cp bin/r-type_client .. && echo Done
