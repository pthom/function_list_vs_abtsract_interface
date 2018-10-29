#include <memory>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

#include "image_with_counter.h"
#include "AppSettings.h"
#include "gui_loop.h"


//////////////////////////////////////////////////////////////
// Interface as an abstract list
//////////////////////////////////////////////////////////////

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
    return MakeImageWithCounter(++frameCounter_, contrast_);
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


//////////////////////////////////////////////////////////////
// Main
//////////////////////////////////////////////////////////////
int main()
{
  auto appSettings = MakeMockAppSettings();
  auto camera = FactorCamera(appSettings);
  gui_loop(camera);
  return 0;
}
