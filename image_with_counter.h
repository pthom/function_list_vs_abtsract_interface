#include <opencv2/core/core.hpp>


inline cv::Mat MakeImageWithCounter(int counter)
{
  cv::Mat m(cv::Size(640, 480), CV_8UC3);
  m = cv::Scalar(0, 0, 0);
  cv::putText(m, std::to_string(counter), cv::Point(200, 300), cv::FONT_HERSHEY_COMPLEX, 3., cv::Scalar(255, 255, 255));
  return m;
}