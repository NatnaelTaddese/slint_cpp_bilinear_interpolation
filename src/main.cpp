#include "appwindow.h"
#include <opencv2/opencv.hpp>

int main(int argc, char **argv)
{
    auto ui = AppWindow::create();
    cv::Mat image = cv::imread("test.jpg");

    ui->on_request_increase_value([&]
                                  { ui->set_counter(ui->get_counter() + 1); });

    ui->run();
    return 0;
}
