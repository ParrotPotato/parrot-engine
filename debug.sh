pushd ./data > /dev/null

DRI_PRIME=1 gdb ../bin/main.out

popd > /dev/null
