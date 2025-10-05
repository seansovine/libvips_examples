#!/usr/bin/env bash

set -e

SCRIPT_DIR=$( cd -- "$( dirname -- "${BASH_SOURCE[0]}" )" &> /dev/null && pwd )
ROOT_DIR="$SCRIPT_DIR/.."

# Copy spdlog shared objects.
cp $ROOT_DIR/build/Debug/thirdparty/spdlog/libspdlogd.so.1.15.3 $SCRIPT_DIR
# Note the name discrepancy.
cp $ROOT_DIR/build/Debug/thirdparty/spdlog/libspdlogd.so.1.15 $SCRIPT_DIR/libspdlog.so.1.15

# Copy libvips shared objects.
cp $ROOT_DIR/thirdparty/libvips/build/libvips/libvips.so.42 $SCRIPT_DIR
cp $ROOT_DIR/thirdparty/libvips/build/libvips/libvips.so.42.20.0 $SCRIPT_DIR
