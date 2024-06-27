# Bilinear Interpolation Image Resizer

## Introduction

![App](./screenshots/windows/Screenshot%202024-06-28%20021401.png)

This project is a simple application for resizing images using bilinear interpolation. The application uses C++ and OpenCV for image processing, SlintUI for the user interface.

## Building the Project from Source

### Prerequisites

Ensure you have the following dependencies installed on your system:

1. **CMake** (version 3.21 or higher)
2. **OpenCV**
3. **GTK3** (for Linux)
4. **Git**

### Installing Dependencies

#### Ubuntu/Linux

1. **Install CMake**:

   ```sh
   sudo apt-get update
   sudo apt-get install -y cmake
   ```

2. **Install OpenCV**:

   ```sh
   sudo apt-get install -y libopencv-dev
   ```

3. **Install GTK3**:

   ```sh
   sudo apt-get install -y libgtk-3-dev
   ```

4. **Install Git**:
   ```sh
   sudo apt-get install -y git
   ```

#### Windows

1. **Install CMake**:

   - Download and install CMake from [cmake.org](https://cmake.org/download/).

2. **Install OpenCV**:

   - Download OpenCV from [opencv.org](https://opencv.org/releases/).
   - Follow the [installation guide](https://docs.opencv.org/master/d3/d52/tutorial_windows_install.html).

3. **Install Git**:
   - Download and install Git from [git-scm.com](https://git-scm.com/download/win).

### Building the Project

1. **Clone this Repository**:

   ```sh
   git clone https://github.com/NatnaelTaddese/slint_cpp_bilinear_interpolation.git
   cd slint_cpp_bilinear_interpolation
   ```

2. **Configure and Build**:

   ```sh
   mkdir build
   ```

   If Slint is not found, it will be downloaded and built locally during the CMake configuration step.

   But to build it from source you may need [Rust](https://www.rust-lang.org/tools/install), refer to the documentaion [here](https://www.rust-lang.org/tools/install)

   if you don't want to fiddle with Rust, you can install the [Slint Binary](https://releases.slint.dev/1.6.0/docs/cpp/cmake#install-binary-packages) for your respective OS and [add it to your path](https://www3.ntu.edu.sg/home/ehchua/programming/howto/Environment_Variables.html#zz-2.6).

   - **for Linux**

   ```sh
   cmake -B build/linux
   cmake -DSLINT_STYLE="fluent" build/linux
   cmake --build build/linux
   ```

   - **for Windows**

   ```sh
   cmake -B build/windows -DCMAKE_PREFIX_PATH=" \path\to\slint\bin\ " -DOpenCV_DIR=" \path\to\openCV\opencv\build\x64\vc16\lib "

   cmake --build build/windows
   ```

## Using the Application

After building the project, you can run the application from the build directory:

- **for Linux**

```sh
./build/linux/bilinearInterpolationApp
```

- **for Windows**

```sh
build\windows\Debug\bilinearInterpolationApp.exe
```
