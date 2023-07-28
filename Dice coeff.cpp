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

void replace(int**& array, int row, int col, int val, int label) {/*A function to replace the larger elements in labeling*/
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (array[i][j] == val) {
                array[i][j] = label;
            }
        }
    }

}

 int** Connected_Components( int** array, int rows , int cols) {     /*A function to check the neighbour and found the connectd component of the array*/
    int number=1;  
   

     int** check = new  int* [rows]{0};
                                                                      /*Clone Array*/
    for (int i = 0; i < rows; i++)
        check[i] = new  int[cols]{0};


    for (int i = 0; i < rows; i++) {

        for (int j = 0; j < cols; j++) {
            if (array[i][j] == 255) {
                check[i][j] = 1;
            }
        }
    }

    bool flag = false;
    //Conditions to check the neighbours of the array//
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {

            flag = false;

            if ((j - 1 >= 0)) {

                if (array[i][j] != 0 and array[i][j - 1] != 0) {
                    if (check[i][j] > check[i][j - 1]) {
                        replace(check, rows, cols, check[i][j], check[i][j - 1]);
                        number--;
                    }

                    check[i][j] = check[i][j - 1];



                    flag = true;
                }
            }

            if ((i - 1 >= 0 and j + 1 < cols)) {

                if (array[i - 1][j + 1] != 0 and array[i][j] != 0) {
                    if (check[i][j] > check[i - 1][j + 1]) {
                        replace(check, rows, cols, check[i][j], check[i - 1][j + 1]);
                        number--;
                    }
                    check[i][j] = check[i - 1][j + 1];




                    flag = true;

                }

            }

            if (i - 1 >= 0) {

                if (array[i - 1][j] != 0 and array[i][j] != 0) {
                    if (check[i][j] > check[i - 1][j]) {
                        replace(check, rows, cols, check[i][j], check[i - 1][j]);
                        number--;
                    }
                    check[i][j] = check[i - 1][j];



                    flag = true;

                }

            }
            if ((i - 1 >= 0 and j - 1 >= 0)) {

                if (array[i - 1][j - 1] != 0 and array[i][j] != 0) {
                    if (check[i][j] > check[i - 1][j - 1]) {
                        replace(check, rows, cols, check[i][j], check[i - 1][j - 1]);
                        number--;
                    }
                    check[i][j] = check[i - 1][j - 1];


                    flag = true;
                }
            }

            if (flag == false and array[i][j] != 0) {

                check[i][j] = number;
                number++;
            }
        }
    }


    return check;

}

int big_lesion_element( int**&check,int rows, int cols) {        /*A function to check the element that forms the biggest lesion */
    int max = check[0][0];
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            if (max < check[i][j])
                max = check[i][j];
        }
    }

   const int SIZE = max;
    int* frequency = new int[SIZE]{0};
    int count = 0;

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < rows; j++)
            for (int k = 0; k < cols; k++) {
                if (i + 1 == check[j][k])
                {
                    count++;
                    frequency[i] = count;
                }
            }
        count = 0;
    }

    max = frequency[0];
    int lesion=NULL;
    for (int j = 0+1; j < SIZE; j++) {
        if (max < frequency[j])
        {
            max = frequency[j];

        }

    }

    for (int j = 0; j < SIZE; j++) {
        if (max == frequency[j])
        {
            lesion = j + 1;
            break;
        }

    }

    return lesion;
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

    //cout << endl << "means = " << mean[0] << " , " << mean[1] << " , " << mean[2] << " , " << mean[3];
   // cout << endl << "clusters = " << c1 << " , " << c2 << endl;
    //cout << index_low << " " << index_high;



    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            for (int k = 0; k <= index_low; k++) {
                if (array[i][j] == low_centroid[k]) {
                    array[i][j] = 255;
                }
            }
        }
    }

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            for (int k = 0; k <= index_high; k++) {
                if (array[i][j] == high_centroid[k]) {
                    array[i][j] = 0;
                }
            }
        }
    }


    delete[]low_centroid;
    delete[]high_centroid;
    return array;

}

float Dice_Coefficient(cv::Mat& obj1, cv::Mat& obj2, int row, int col) {
    float TP = 0, FN = 0, FP = 0;

    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            if (obj1.at<uchar>(i, j) == 255 and obj2.at<uchar>(i, j) == 255)
                ++TP;
            if (obj1.at<uchar>(i, j) == 255 and obj2.at<uchar>(i, j) == 0)
                ++FN;
            if (obj1.at<uchar>(i, j) == 0 and obj2.at<uchar>(i, j) == 255)
                ++FP;
        }
    }

    float ans = (2.0 * TP) / (FN + (2 * TP) + FP);

    return ans;
}



int main()
{

  //  cv::Mat img = cv::imread("", 0);  //Img path #segmentedoutput for checking kmean dice coeff
    cv::Mat img = cv::imread("", 0); //img path #originalimg for checking ccl dice coeff
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
    
    //ccl for checking dice coeff
    int** check = Connected_Components(arr, img.rows, img.cols);             //Clone array after connected componenet labeling

     float lesion_element = big_lesion_element(check, img.rows, img.cols);
     //cout << "Lesion element is = " << lesion_element << endl;

     for (int i = 0; i < img.rows; i++) {
         for (int j = 0; j < img.cols; j++) {
             if (check[i][j] == lesion_element) {
                 check[i][j] = 255;
             }
             else
                 check[i][j] = 0;
         }
     }


     for (int i = 0; i < img.rows; i++) {
         for (int j = 0; j < img.cols; j++) {
            img.at<uchar>(i, j) = check[i][j];
         }
     }

     //cout << "Equality = " << istrue(check, img, img.rows, img.cols) << endl;
    imwrite("ok1.bmp", img);

  // print(arr, img.rows, img.cols);
    //print(check, img.rows, img.cols);
   

   //Kmean Clustering for checking dice coeff
   
   //int** check = KMEAN(arr, img.rows, img.cols);
   ////print(check, img.rows, img.cols);

   //for (int i = 0; i < img.rows; i++) {
   //    for (int j = 0; j < img.cols; j++) {
   //        img.at<uchar>(i, j) = check[i][j];
   //    }
   //}
   //imwrite("ok1.bmp", img);

   

   //Dice coefficient
   
   cv::Mat G_T = cv::imread("C:/Users/Muneeb/Desktop/IMD063_lesion.bmp", 0); //img path #groundtruth

  float Dice_C =  Dice_Coefficient(G_T, img, img.rows, img.cols);

  cout << "The dice coeffcient = " << Dice_C << endl;
  

    for (int i = 0; i < img.rows; i++) {
        delete[]arr[i];

    }
    delete[]arr;



    return 0;
}
