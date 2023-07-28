#include <P:\Data structures 3rd sem\New folder\opencv\build\include\opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
using namespace cv;
using namespace std;

void assign( int**& ptr,cv::Mat &image, int row, int col) {        /*A function to assigning values i.e making a clone*/
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            int x = image.at<uchar>(i, j);
            ptr[i][j] = x;
        }
    }
}

bool istrue( int**ptr,cv::Mat &image, int row, int col) {        /*A function to check whether the pixel values are same or not  */
    for (int i = 0; i < row; i++) {
        for (int j = 0; j < col; j++) {
            int x = image.at<uchar>(i, j);
            if (ptr[i][j] != x)
                return false;
        }
    }
    return true;
}

void print( int**ptr,int row, int col) {      /*A function to print the pixel values of array*/
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



int main()
{
    
    cv::Mat img = cv::imread("",0); //Img path #segmentedoutput
    cv::namedWindow("First OpenCV Application", cv::WINDOW_AUTOSIZE);
    cv::imshow("First OpenCV Application", img);
    cv::moveWindow("First OpenCV Application", 0, 45);
    cv::waitKey(0);
    cv::destroyAllWindows();
     int** arr = new  int*[img.rows];         
                                        //Clone Array
    for (int i = 0; i < img.rows; i++)
        arr[i] = new  int[img.cols];

    cout << "The rows of image = " << img.rows << endl << "The img.columns of the Image is = " << img.cols << endl;// Checking the rows and img.colsumns of the pic
    
    assign(arr, img, img.rows, img.cols);
   //cout << istrue(arr, img, img.rows, img.cols)<<endl;
   
    int** check = Connected_Components(arr, img.rows, img.cols);             //Clone array after connected componenet labeling
   
    float lesion_element = big_lesion_element(check, img.rows, img.cols);
    cout << "Lesion element is = " << lesion_element << endl;            

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
   
  
   imwrite("img.bmp", img);

  //print(arr, img.rows, img.cols);
  // print(check, img.rows, img.cols);
  
    for (int i = 0; i < img.rows; i++) {
        delete[]arr[i];

    }
    delete[]arr;

    

    return 0;
}
