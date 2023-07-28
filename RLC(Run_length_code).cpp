#include <P:\Data structures 3rd sem\New folder\opencv\build\include\opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <iostream>
//using namespace cv;
using namespace std;


template<class T>
class Node {  //creating linked list
public:
    T data;
    Node* next;

    Node(T val) {
        data = val;
        next = NULL;

    }
};
template<class T>
void insertatend(Node<T>*& head, T val) { //insert into linked list
    Node<T>* n = new Node<T>(val);

    if (head == NULL) {
        head = n;
        return;
    }
    Node<T>* temp = head;
    while (temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = n;

}


template<class T>
void print(Node<T>*& head) {
    Node<T>* temp = head;
    while (temp != NULL) {
        cout << temp->data << " ";
        if (temp->data == -1)
            cout << endl;

        temp = temp->next;

    }
}

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
int main() {
    cv::Mat img = cv::imread("", 0);   //Img path #segmentedimg
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


    Node<int>* head = NULL;



    int start = 0, High = 0, row = 0;
    bool color = false;

    for (int i = 0; i < img.rows; i++) {
        bool flag = false;
        bool check2 = false;
        bool check3 = false;
        for (int j = 0; j < img.cols; j++) {

            if (arr[row][j] == 255) {
                flag = true;

            }
            if (arr[row][j] == 0) {
                if (color == false) {
                    start = j;
                    insertatend(head, start);
                    color = true;
                    check2 = true;

                }
                High = j;
                if (arr[row][j + 1] != 0) {
                    color = false;
                    check3 = true;
                }
                if (check3)
                    insertatend(head, High);

            }

        }
        insertatend(head, -1);

        row++;
    }

    print(head);

    for (int i = 0; i < img.rows; i++) {
        delete[]arr[i];

    }
    delete[]arr;
    return 0;
}
