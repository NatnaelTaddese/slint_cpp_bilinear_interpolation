#include <opencv2/opencv.hpp>
#include "utils/shared/random_number.cpp"
#include <filesystem>

#include "appwindow.h"

#ifdef _WIN32
#include "utils/platforms/windows/file_dialog_win.cpp"
#else
#include "utils/platforms/linux/file_dialog.cpp"
#endif

void load_image()
{
    std::string file_path = showFileDialog();
    if (!file_path.empty())
    {
        // Load the image with OpenCV, as a matrix of course
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
    // TODO: remove the anon function with the load_image function and figure out how to pass the appwindow object
    // appwindow->on_clicked(load_image);
    appwindow->on_clicked([&]()
                          {
        std::string file_path = showFileDialog();
        if (!file_path.empty()) {
            // Load the image with OpenCV
            cv::Mat image = cv::imread(file_path);

            if (image.empty()) {
                std::cout << "Could not read the image: " << file_path << std::endl;
                appwindow->set_valid_image_selected(false);
            } else {
                std::cout << "Image loaded: " << file_path << std::endl;
                appwindow->set_selected_image( slint::Image::load_from_path(file_path.c_str()));
                appwindow->set_valid_image_selected(true);
                appwindow->set_output_image(slint::Image::load_from_path(""));

                // Display the image using OpenCV (optional)
                // cv::imshow("Selected Image", image);
                // cv::waitKey(0);
            }
        }
        else{
            appwindow->set_selected_image( slint::Image::load_from_path(""));
            appwindow->set_valid_image_selected(false);
        } });

    if (argc > 1)
    {
        appwindow->set_selected_image(slint::Image::load_from_path(argv[1]));
        appwindow->set_valid_image_selected(true);
    }

    appwindow->on_resizeImage([&](int desiredWidth, int desiredHeight)
                              {
                                  slint::SharedString raw_file_path = appwindow->get_selected_image().path().value();
                                  std::string file_path = raw_file_path.data();

                                  std::cout << "original path: " << file_path << std::endl;
                                  appwindow->set_output_image(slint::Image::load_from_path(""));

                                  if (!file_path.empty())
                                  {
                                      cv::Mat image = cv::imread(file_path);
                                      if (!image.empty())
                                      {
                                          cv::Mat resized_image;
                                          cv::resize(image, resized_image, cv::Size(desiredWidth, desiredHeight));

                                          // Save the resized image to a temporary file
                                          std::string temp_path = "image_" + std::to_string(seed_random_number()) + "__" + std::to_string(desiredWidth) + "x" + std::to_string(desiredHeight) + ".png";
                                          cv::imwrite(temp_path, resized_image);

                                          // Update the UI with the resized image

                                          appwindow->set_output_image(slint::Image::load_from_path(temp_path.c_str()));
                                      }
                                      else
                                      {
                                          std::cout << "Failed to read the image for resizing: " << file_path << std::endl;
                                      }
                                  }
                                  else
                                  {
                                      std::cout << "No image selected to resize." << std::endl;
                                  }

                                  std::cout << desiredWidth << " : " << desiredHeight << std::endl;
                                  // sets the appwindow->set_output_image to the resized image from the opencv
                              });

    appwindow->on_saveToFiles([&]()
                              {
                                  std::cout << "ready to save to file" << std::endl;
                                  slint::SharedString raw_file_path = appwindow->get_output_image().path().value();
                                  std::string file_path = raw_file_path.data();

                                  std::cout << file_path << std::endl;

                                  // Convert the relative path to an absolute path
                                    std::filesystem::path absolutePath = std::filesystem::absolute(file_path);

                                // Convert the absolute path to string and use it in saveToFileDialog
                                    std::string tempFilePath = absolutePath.string();

                                    std::cout << tempFilePath << std::endl;


                                  if (!file_path.empty())
                                  {
                                      bool success = saveToFileDialog(tempFilePath);
                                      if (success)
                                      {
                                          std::cout << "File saved" << std::endl;
                                      }
                                      else
                                      {
                                          std::cout << "Failed to save file" << std::endl;
                                      }
                                  } });

    appwindow->run();
    return 0;
}