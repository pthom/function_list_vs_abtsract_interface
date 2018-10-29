# Functions list versus abstract interface

This proof of concept explores a possible alternative to pure abstract interfaces, under the form of a simple struct that will contain any number of `std::function`.

For example, an interface like 
````cpp
class ICamera {
public:
  virtual cv::Mat grab() = 0;
};
````

can be replaced by 
````cpp
struct CameraFunctions: AnyFunctionList {
  std::function<cv::Mat(void)> grab;
};
````

Then the application code, will store a `StatefulFunctionList<CameraFunctions>` instead of storing something like `std::unique_ptr<ICamera>` :  `StatefulFunctionList` is a template class which stores the state of the implementation, but hides it from inside the application code.

# Full example:
This example explores a possible use, where we need an interface and a factory that depends on the application settings (strategy pattern).


## Implementation with an abstract interface

````cpp
// Interface as an abstract class
class ICamera
{
public:
  virtual ~ICamera() = default;
  virtual cv::Mat grab() = 0;
  virtual double get_contrast() = 0;
  virtual void set_contrast(double v) = 0;
};


// Concrete implementation as a derivate
class CameraMock: public ICamera
{
public:
  ~CameraMock() = default;
  cv::Mat grab() override {
    return MakeImageWithCounter(++frameCounter_);
  }
  double get_contrast() override { return contrast_; };
  void set_contrast(double v) override { contrast_ = v; }
private:
  int frameCounter_ = 0; // The state is mixed with the concrete implementation
  double contrast_ = 0.5;
};


// Factory
std::unique_ptr<ICamera> FactorCamera(const AppSettings & appSettings)
{
  if (appSettings.useCameraMock)
    return std::make_unique<CameraMock>();
  throw std::logic_error("Not finished");
}
````

## Implementation with a function list

See [stateful_functions.h](stateful_functions.h) for the implementation of `StatefulFunctionList`.

````cpp
// Interface as a function list
struct CameraFunctions
{
  std::function<cv::Mat(void)> grab;
  std::function<double(void)> get_contrast;
  std::function<void(double)> set_contrast;
};


// Concrete implementation with a separate state
struct CameraMockState: AnyState {
  int frameCounter = 0;
  double contrast = 0.5;
};

StatefulFunctionList<CameraFunctions> FactorCameraMock()
{
  auto state = std::make_shared<CameraMockState>();
  StatefulFunctionList<CameraFunctions> r(state);
  r->grab = [state]() {
      return MakeImageWithCounter(++ state->frameCounter);
  };
  r->get_contrast = [state]() { return state->contrast; };
  r->set_contrast = [state](double v) { state->contrast = v; };
  return r;
};


// Factory
StatefulFunctionList<CameraFunctions> FactorCamera(const AppSettings & appSettings)
{
  if (appSettings.useCameraMock)
    return FactorCameraMock();
  throw std::logic_error("Not finished");
}
````

# Build instructions 
## prerequisites : conan & opencv

You need to install the conan package manager (see instructions at http://conan.io)

Opencv is a dependency that is installed via conan.

You will then need to add a conan remote for opencv 

````bash
conan remote add camposs "https://conan.campar.in.tum.de/api/conan/conan-camposs"
````

## How to build

````bash
mkdir build
cd build
conan install .. --build=missing  # will download / build opencv 
cmake ..
make
````

## How to run

Launch `./abstract_class_interface` or `./function_list_interface`


