#include <opencv2/opencv.hpp>

#include "appwindow.h"
#include "utils/file_dialog.cpp"

// #include <opencv2/opencv.hpp>

// int main(int argc, char **argv)
// {
//     auto ui = AppWindow::create();
//     cv::Mat image = cv::imread("test.jpg");

//     ui->on_request_increase_value([&]
//                                   { ui->set_counter(ui->get_counter() + 1); });

//     ui->run();
//     return 0;
// }

void load_image()
{
    std::string file_path = showFileDialog();
    if (!file_path.empty())
    {
        // Load the image with OpenCV
        cv::Mat image = cv::imread(file_path);
        if (image.empty())
        {
            std::cout << "Could not read the image: " << file_path << std::endl;
        }
        else
        {
            std::cout << "Image loaded: " << file_path << std::endl;
            // appwindow->set_selected_image(file_path.c_str());

            // Display the image using OpenCV (optional)
            cv::imshow("Selected Image", image);
            cv::waitKey(0);
        }
    }
}

int main()
{
    // Initialize Slint UI
    auto appwindow = AppWindow::create();

    // Connect button click signal
    appwindow->on_clicked(load_image);

    appwindow->run();
    return 0;
}