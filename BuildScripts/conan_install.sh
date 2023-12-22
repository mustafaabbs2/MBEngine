#!/bin/bash

# start from repo Build dir
buildDir=$(dirname $0)
cd $buildDir

export CONAN_SYSREQUIRES_MODE=enabled
export CONAN_REVISIONS_ENABLED=1
export CONAN_NON_INTERACTIVE=1

# install build tools
# echo "Installing build tools..."
# conan install conanfileBuildTools.txt --profile conanprofile.txt -if ../build/BuildTools || exit $?

echo "Installing Conan dependencies..."

if [[ $1 == "Debug" ]]
then
    conan install ../conanfile.py --profile Darwin/conanprofile.txt -if ../build/Debug --build=missing || exit $?
else
    conan install ../conanfile.py --profile Darwin/conanprofile.txt -if ../build/Release --build=missing || exit $?
fi
