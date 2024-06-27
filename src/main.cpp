// #include <opencv2/opencv.hpp>
#include "utils/shared/random_number.cpp"
#include <filesystem>

#include "appwindow.h"
#include "My_bilinear_interpolation.cpp"

#ifdef _WIN32
#include "utils/platforms/windows/file_dialog_win.cpp"
#else
#include "utils/platforms/linux/file_dialog.cpp"
#endif

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
#ifdef DEBUG
                std::cout << "Could not read the image: " << file_path << std::endl;
#endif // DEBUG

                appwindow->set_valid_image_selected(false);
            } else {

#ifdef DEBUG
                std::cout << "Image loaded: " << file_path << std::endl;

#endif // DEBUG
                appwindow->set_selected_image( slint::Image::load_from_path(file_path.c_str()));
                appwindow->set_valid_image_selected(true);
                appwindow->set_output_image(slint::Image::load_from_path(""));

                // Displays the image using OpenCV if we didn't have our own UI
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

                                  appwindow->set_output_image(slint::Image::load_from_path(""));

                                  if (!file_path.empty())
                                  {
                                      cv::Mat image = cv::imread(file_path);
                                      if (!image.empty())
                                      {
                                          // for testing purposes this is using the out of the box openCV library to resise, for the final, I should be using the one I implemented
                                          //   cv::Mat resized_image;
                                          //   cv::resize(image, resized_image, cv::Size(desiredWidth, desiredHeight));

                                          // MY BILINEAR INTERPOLATION
                                          cv::Mat resized_image = CustomInterpolation::MyResizeImage(image, desiredWidth, desiredHeight);

                                          // Save the resized image to a temporary file
                                          std::string temp_path = "image_" + std::to_string(seed_random_number()) + "__" + std::to_string(desiredWidth) + "x" + std::to_string(desiredHeight) + ".png";
                                          cv::imwrite(temp_path, resized_image);

                                          // Update the UI with the resized image
                                          appwindow->set_output_image(slint::Image::load_from_path(temp_path.c_str()));
                                      }
                                      else
                                      {
#ifdef DEBUG
                                          std::cout << "Failed to read the image for resizing: " << file_path << std::endl;
#endif // DEBUG
                                      }
                                  }
                                  else
                                  {
#ifdef DEBUG
                                      std::cout << "No image selected to resize." << std::endl;
#endif // DEBUG
                                  } });

    appwindow->on_saveToFiles([&]()
                              {
                                  
                                    slint::SharedString raw_file_path = appwindow->get_output_image().path().value();
                                    std::string file_path = raw_file_path.data();


                                    // Convert the relative path to an absolute path
                                    std::filesystem::path absolutePath = std::filesystem::absolute(file_path);

                                    // Convert the absolute path to string and use it in saveToFileDialog
                                    std::string tempFilePath = absolutePath.string();



                                  if (!file_path.empty())
                                  {
                                      bool success = saveToFileDialog(tempFilePath);

#ifdef DEBUG
                                      if (success)
                                      {
                                          std::cout << "File saved successfully" << std::endl;
                                      }
                                      else
                                      {
                                          std::cout << "Failed to save file" << std::endl;
                                      }

#endif // DEBUG
                                      
                                      
                                  } });

    appwindow->run();
    return 0;
}