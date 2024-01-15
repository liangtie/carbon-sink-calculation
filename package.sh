#!/bin/bash
cp build/carbon-sink-calculation.exe installer/packages/com.vendor.product/data/carbon-sink-calculation.exe
cd installer
binarycreator.exe -c config/config.xml -p packages 城市建筑碳汇量计算.exe