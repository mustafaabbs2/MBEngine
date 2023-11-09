from conans import ConanFile, CMake, tools
import os

class MyLibraryConan(ConanFile):
    name = "my server"
    license = "MIT"
    author = "Mustafa Bhotvawala"
    description = "A simple server"

    _isLocal = os.environ.get('BUILD_VERSION') == None

    _installDirBin = "build/install/bin"
    _installDirInc = "build/install/include"
    _installDirLib = "build/install/lib"

    def requirements(self):
        self.requires("gtest/1.10.0")
        self.requires("boost/1.71.0")
        self.requires("protobuf/3.21.9")
        self.requires("grpc/1.47.1")
        self.requires("zlib/1.3")

    def configure(self):
        self.generators = ["cmake_find_package", "virtualenv", "cmake"]

    def set_version(self):
        if self._isLocal == True:
            self.version = "local-dev"
        else:
            self.version = os.environ.get('BUILD_VERSION')

#copy to the lib, bin and include folders of the project
    def package(self):
        self.copy("*.h", dst="include", src=self._installDirInc)
        self.copy("*.lib", dst="lib", src=self._installDirLib, keep_path=False)
        self.copy("*.dll", dst="bin", src=self._installDirBin, keep_path=False)
        self.copy("*.so", dst="lib", src=self._installDirLib, keep_path=False)
        self.copy("*.dylib", dst="lib", src=self._installDirLib, keep_path=False)
        self.copy("*.a", dst="lib", src=self._installDirLib, keep_path=False)
        if self._isLocal == True:
            self.copy("*.pdb", dst="bin", src=self._installDirBin, keep_path=False)

# Add all the lib files to LD_LIBRARY_PATH for the package
    def package_info(self):
        self.cpp_info.libs = tools.collect_libs(self)
        self.env_info.LD_LIBRARY_PATH.append(os.path.join(self.package_folder, "lib"))
