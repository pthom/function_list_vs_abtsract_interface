#include "stateful_functions.h"
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


////// CameraFunctions 
struct CameraFunctions
{
  std::function<cv::Mat(void)> grab;
  std::function<double(void)> get_contrast;
  std::function<void(double)> set_contrast;
};


///// CameraMock
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


/////// AppContext
class AppContext
{
public:
  bool useCameraMock;
};


////// Factories
StatefulFunctions<CameraFunctions> FactorCamera(const AppContext & appContext)
{
  if (appContext.useCameraMock) {
    auto result = FactorCameraMock();
    return result;
  }
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