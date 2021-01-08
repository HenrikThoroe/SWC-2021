#!/bin/bash

# Convert all JSON files in assets to includable header files and copy them to /app/include/assets

for path in ./assets/*.json; do
    # Extract file name from path
    name=${path##*/}

    # Create asset directory in ./app/include
    mkdir -p "./app/include/assets/"

    # Copy all .json files from ./assets into ./app/include/assets as .json.hpp
    # Overwrite when the file already exists
    yes | cp -rf $path "./app/include/assets/$name.hpp"

    # Add R"( as prefix and )" as suffix
    gawk -i inplace '{ print "R\"("$0")\"" }' RS='^$' "./app/include/assets/$name.hpp"
done