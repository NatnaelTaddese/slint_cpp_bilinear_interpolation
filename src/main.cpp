#include <opencv2/opencv.hpp>

#include "appwindow.h"
#include "utils/file_dialog.cpp"

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

int main(int argc, char **argv)
{
    // Initialize Slint UI
    auto appwindow = AppWindow::create();

    // Connect button click signal

    // appwindow->on_clicked(load_image);
    appwindow->on_clicked([&]()
                          {
        std::string file_path = showFileDialog();
        if (!file_path.empty()) {
            // Load the image with OpenCV
            cv::Mat image = cv::imread(file_path);
            if (image.empty()) {
                std::cout << "Could not read the image: " << file_path << std::endl;
            } else {
                std::cout << "Image loaded: " << file_path << std::endl;
                appwindow->set_selected_image( slint::Image::load_from_path(file_path.c_str()));
                appwindow->set_valid_image_selected(true);

                // Display the image using OpenCV (optional)
                // cv::imshow("Selected Image", image);
                // cv::waitKey(0);
            }
        } });

    appwindow->run();
    return 0;
}