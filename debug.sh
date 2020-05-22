pushd ./data > /dev/null

DRI_PRIME=1 gdb ../bin/engine.out

popd > /dev/null
