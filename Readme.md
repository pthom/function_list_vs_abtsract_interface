# struct_vs_interface

````cpp
class ICamera
{
public:
  virtual ~ICamera() = default;
  virtual cv::Mat grab() = 0;
  virtual double get_contrast() = 0;
  virtual void set_contrast(double v) = 0;
};
````

vs

````cpp
struct CameraFunctions
{
  std::function<cv::Mat(void)> grab;
  std::function<double(void)> get_contrast;
  std::function<void(double)> set_contrast;
};
````

## prerequisites : conan 

`conan remote add camposs "https://conan.campar.in.tum.de/api/conan/conan-camposs"`

## build instructions

````bash
mkdir build
cd build
conan install ..
cmake ..
make
````


