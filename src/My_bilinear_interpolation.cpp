#include <opencv2/opencv.hpp>
#include <cmath>

namespace CustomInterpolation
{
    cv::Vec3b bilinearInterpolate(const cv::Mat &image, float x, float y)
    {
        int x1 = static_cast<int>(x);
        int y1 = static_cast<int>(y);
        int x2 = std::min(x1 + 1, image.cols - 1);
        int y2 = std::min(y1 + 1, image.rows - 1);

        float dx = x - x1;
        float dy = y - y1;

        cv::Vec3b pixel1 = image.at<cv::Vec3b>(y1, x1);
        cv::Vec3b pixel2 = image.at<cv::Vec3b>(y1, x2);
        cv::Vec3b pixel3 = image.at<cv::Vec3b>(y2, x1);
        cv::Vec3b pixel4 = image.at<cv::Vec3b>(y2, x2);

        cv::Vec3b result;
        for (int i = 0; i < 3; i++)
        {
            result[i] = static_cast<uchar>(
                (1 - dx) * (1 - dy) * pixel1[i] +
                dx * (1 - dy) * pixel2[i] +
                (1 - dx) * dy * pixel3[i] +
                dx * dy * pixel4[i]);
        }

        return result;
    }

    cv::Mat MyResizeImage(const cv::Mat &image, int targetWidth, int targetHeight)
    {
        cv::Mat resizedImage(targetHeight, targetWidth, image.type());

        float xRatio = static_cast<float>(image.cols) / targetWidth;
        float yRatio = static_cast<float>(image.rows) / targetHeight;

        for (int y = 0; y < targetHeight; y++)
        {
            for (int x = 0; x < targetWidth; x++)
            {
                float px = x * xRatio;
                float py = y * yRatio;
                resizedImage.at<cv::Vec3b>(y, x) = bilinearInterpolate(image, px, py);
            }
        }

        return resizedImage;
    }

}
