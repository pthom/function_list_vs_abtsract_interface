#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

template<class CameraImpl>
void gui_loop(CameraImpl & camera)
{
  while(true) {
    auto img = camera->grab();
    cv::putText(img, "Press q to quit, press +/- to change contrast", cv::Point(10, 30), 
                cv::FONT_HERSHEY_COMPLEX, 0.5, cv::Scalar(255, 255, 255));
    cv::imshow("img", img);
    auto c = cv::waitKey(10);
    if (c == '+')
      camera->set_contrast(camera->get_contrast() + 0.05);
    if (c == '-')
      camera->set_contrast(camera->get_contrast() - 0.05);
    if (c == 'q')
      break;
  }
}
