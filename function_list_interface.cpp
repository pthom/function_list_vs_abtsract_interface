#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "stateful_functions.h"
#include "image_with_counter.h"


//////////////////////////////////////////////////////////////
// AppSettings
//////////////////////////////////////////////////////////////
struct AppSettings
{
  bool useCameraMock;
};
AppSettings MakeMockAppSettings()
{
  AppSettings settings;
  settings.useCameraMock = true;
  return settings;
}

//////////////////////////////////////////////////////////////
// Interface as a function list
//////////////////////////////////////////////////////////////

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
  // The state is forcefuly hidden from the function list
  auto state = std::make_shared<CameraMockState>();
  StatefulFunctionList<CameraFunctions> r(state);

  // In the implementation, `state->` acts as a synonym of `this->'
  // if we were using an abstract class
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


//////////////////////////////////////////////////////////////
// Main
//////////////////////////////////////////////////////////////
int main()
{
  auto appSettings = MakeMockAppSettings();
  auto camera = FactorCamera(appSettings);
  while(true) {
    auto img = camera->grab();
    cv::imshow("img", img);
    if (cv::waitKey(10) == 'q')
      break;
  }
  return 0;
}