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

class CameraMock: public ICamera
{
public:
  ~CameraMock() = default;
  cv::Mat grab() override 
  {
    cv::Mat m(cv::Size(640, 480), CV_8UC3);
    m = cv::Scalar(0, 0, 0);
    cv::putText(m, std::to_string(frameId_), cv::Point(200, 300), cv::FONT_HERSHEY_COMPLEX, 3., cv::Scalar(255, 255, 255));
    frameId_++;
    return m;
  }
  double get_contrast() override { return contrast_; };
  void set_contrast(double v) override { contrast_ = v; }
private:
  int frameId_ = 0;
  double contrast_ = 0.5;
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

struct CameraMockState : public AnyState {
  int frameId = 0;
  double contrast = 0.5; 
};


StatefulFunctions<CameraFunctions> FactorCameraMock()
{
  StatefulFunctions<CameraFunctions> r(std::make_unique<CameraMockState>());
  r->grab = [&r]() {
    cv::Mat m(cv::Size(640, 480), CV_8UC3);
    m = cv::Scalar(0, 0, 0);
    auto &id = r.state<CameraMockState>()->frameId;
    cv::putText(m, std::to_string(id), cv::Point(200, 300), cv::FONT_HERSHEY_COMPLEX, 3., cv::Scalar(255, 255, 255));
    id++;
    return m;
  };
  r->get_contrast = [&r]() { return r.state<CameraMockState>()->contrast; };
  r->set_contrast = [&r](double v) { r.state<CameraMockState>()->contrast = v; };
  return r;
};

````

## prerequisites : conan 

You need to install the conan package manager (see instructions at http://conan.io)

You will then need to add a conan remote for opencv 
`conan remote add camposs "https://conan.campar.in.tum.de/api/conan/conan-camposs"`

## build instructions

````bash
mkdir build
cd build
conan install .. --build=missing  # will download / build opencv 
cmake ..
make
````


