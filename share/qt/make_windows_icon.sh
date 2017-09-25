#!/bin/bash
# create multiresolution windows icon
ICON_DST=../../src/qt/res/icons/kurdcoin.ico

convert ../../src/qt/res/icons/kurdcoin-16.png ../../src/qt/res/icons/kurdcoin-32.png ../../src/qt/res/icons/kurdcoin-48.png ${ICON_DST}
