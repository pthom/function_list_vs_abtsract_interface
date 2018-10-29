#include <memory>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


////// ICamera 
class ICamera
{
public:
  virtual ~ICamera() = default;
  virtual cv::Mat grab() = 0;
  virtual double get_contrast() = 0;
  virtual void set_contrast(double v) = 0;
};


///// CameraMock
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


/////// AppContext
class AppContext
{
public:
  bool useCameraMock;
};


////// Factories
std::unique_ptr<ICamera> FactorCamera(const AppContext & appContext)
{
  if (appContext.useCameraMock)
    return std::make_unique<CameraMock>();
  throw std::logic_error("Not finished");
}


AppContext MakeMockAppContext()
{
  AppContext context;
  context.useCameraMock = true;
  return context;
}


/////  Main
int main()
{
  auto appContext = MakeMockAppContext();
  auto camera = FactorCamera(appContext);
  while(true){
    auto img = camera->grab();
    cv::imshow("img", img);
    if (cv::waitKey(10) == 'q')
      break;
  }
  return 0;
}