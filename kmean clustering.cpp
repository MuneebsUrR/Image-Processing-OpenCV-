#include <P:\Data structures 3rd sem\New folder\opencv\build\include\opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;
void assign(int**& ptr, cv::Mat& image, int row, int col) {        /*A function to assigning values i.e making a clone*/
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            int x = image.at<uchar>(i, j);
            ptr[i][j] = x;
        }
    }
}

void print(int** ptr, int row, int col) {      /*A function to print the pixel values of array*/
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            cout << ptr[i][j];
        }
        cout << endl;
    }
}


int average(int* array, int size) {    /*A function that return the average of the centroids*/
    int sum = 0;
    for (int i = 0; i < size; i++) {
        sum += array[i];
    }
    return sum / size;
}


int** KMEAN(int**& array, int row, int col) {   //K-mean clustering
    srand(time(0));

    int c1 = 18, c2 = 120; int ans1 = 0, ans2 = 0;

    int* low_centroid = new int[500000]{ 0 };
    long int index_low = 0;
    int* high_centroid = new int[500000]{ 0 };
    long  int index_high = 0;

    int mean[4]{ 0 }; static int mean_index = 0; bool flag = false;

    int number = 0;
    do {


        index_high = 0;
        index_low = 0;

        for (int i = 0; i < row; i++) {
            for (int j = 0; j < col; j++) {
                number = array[i][j];
                ans1 = abs(c1 - number);
                ans2 = abs(c2 - number);
                if (ans1 < ans2) {
                    low_centroid[index_low] = number;
                    index_low++;
                }
                else if (ans1 > ans2) {
                    high_centroid[index_high] = number;
                    index_high++;
                }
            }
        }

        mean[mean_index] = average(low_centroid, index_low);
        mean_index++;
        mean[mean_index] = average(high_centroid, index_high);

        if (mean[0] == mean[2] and mean[1] == mean[3]) {
            flag = true;
        }


        if (mean_index == 1) {
            c1 = rand() % 50;
            c2 = 100 + rand() % 100;
            if (c1 == 0 || c2 == 0)
            {
                c1 += 1;
            }
        }

        if (mean_index == 3) {
            mean_index = 0;
            c1 = rand() % 50;
            c2 = 100 + rand() % 100;
            if (c1 == 0 || c2 == 0)
            {
                c1 += 1;
            }
        }


    } while (!flag);

    cout << endl << "means = " << mean[0] << " , " << mean[1] << " , " << mean[2] << " , " << mean[3];
    cout << endl << "clusters = " << c1 << " , " << c2 << endl;
    cout << index_low << " " << index_high;



    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            for (int k = 0; k <= index_low; k++) {
                if (array[i][j] == low_centroid[k]) {
                    array[i][j] = 0;
                }
            }
        }
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            for (int k = 0; k <= index_high; k++) {
                if (array[i][j] == high_centroid[k]) {
                    array[i][j] = 255;
                }
            }
        }
    }


    delete[]low_centroid;
    delete[]high_centroid;
    return array;

}


int main()
{
    cv::Mat img = cv::imread("", 0); //Img path #originalimg
    cv::namedWindow("First OpenCV Application", cv::WINDOW_AUTOSIZE);
    cv::imshow("First OpenCV Application", img);
    cv::moveWindow("First OpenCV Application", 0, 45);
    cv::waitKey(0);
    cv::destroyAllWindows();
    int** arr = new  int* [img.rows];
    //Clone Array
    for (int i = 0; i < img.rows; i++)
        arr[i] = new  int[img.cols];

    cout << "The rows of image = " << img.rows << endl << "The img.colsumns of the Image is = " << img.cols << endl;// Checking the rows and img.colsumns of the pic

    assign(arr, img, img.rows, img.cols);

   int** check = KMEAN(arr, img.rows, img.cols);
   //print(check, img.rows, img.cols);

   for (int i = 0; i < img.rows; i++) {
       for (int j = 0; j < img.cols; j++) {
           img.at<uchar>(i, j) = check[i][j];
       }
   }
   imwrite("ok.bmp", img);

  

    for (int i = 0; i < img.rows; i++) {
        delete[]arr[i];

    }
    delete[]arr;



    return 0;
}
