#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

inline cv::Mat MakeImageWithCounter(int counter, double contrast)
{
  cv::Mat m(cv::Size(640, 480), CV_8UC3);
  m = cv::Scalar(0, 0, 0);
  uchar colorIntensity = static_cast<uchar>(contrast * 255.);
  cv::Scalar textColor(colorIntensity, colorIntensity, colorIntensity);
  cv::putText(m, std::to_string(counter), cv::Point(200, 300), cv::FONT_HERSHEY_COMPLEX, 3., textColor);
  return m;
}