#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include "bits/stdc++.h"
#include <iostream>
#include <thread>
using namespace std;
#include <db.h>
int N = 200;
int length = 100;
int screen_size_w = 1700;
int screen_size_h = 1000;


void FillRectangle(sf::RectangleShape *rect, int i, int val)
{

    rect->setFillColor(sf::Color(0, 255, 0));
    rect->setOutlineThickness(100 / length);
    rect->setOutlineColor(sf::Color(0, 0, 0));
    // rectangle.setOrigin(0, 720);
    rect->setPosition(screen_size_w * i / length, 0);
}
void sort_call_sfml(int array[], sf::RenderWindow *window, sf::RectangleShape rectangle[])
{
    // int size = sizeof(array) / sizeof(array[0]);
    window->clear(sf::Color::Black);

    for (size_t i = 0; i < length; i++)
    {
        cout << array[i] << " ";
        rectangle[i].setSize(sf::Vector2f(screen_size_w / length, 2 * array[i]));
        FillRectangle(&rectangle[i], i, array[i]);
        window->draw(rectangle[i]);
    }
    cout << endl;
    window->display();
    if (length < 500)
    {
        this_thread::sleep_for(std::chrono::milliseconds(1000 / length));
    }
}
//Radix Sort :
int getMax(int arr[] ){
    int mx = arr[0];
    for(int i=1;i<length;i++){
        if(arr[i] > mx){
            mx = arr[i];
        }
    }
    return mx;
}
void countSort(int arr[] , int exp, sf::RenderWindow *window, sf::RectangleShape rectangle[]){
    int output[length];
    int i,count[10] = {0};

    for(i = 0;i<length;i++){
        count[(arr[i] / exp) % 10]++;
    }
    for(i = 1;i<10;i++){
        count[i] += count[i-1];
    }
    for(i = length-1;i>=0;i--){
        output[count[(arr[i]/exp)%10]-1] = arr[i];
        count[(arr[i]/exp)%10]--;
    }
    for(i=0;i<length;i++){
        arr[i] = output[i];
        sort_call_sfml(arr, window, rectangle);
    }
}
void radixSort(int arr[], sf::RenderWindow *window, sf::RectangleShape rectangle[]){
    int m = getMax(arr);
    for( int exp = 1; m / exp > 0; exp += 10){
        countSort(arr , exp,window,rectangle);
    }
}

// quick Sort::

int arrangePivot(int array[], int begin, int end, sf::RenderWindow *window, sf::RectangleShape rectangle[])
{
    int pivot = array[end];
    int i = (begin - 1); // Index of smaller element

    for (int j = begin; j <= end - 1; j++)
    {
        // If current element is smaller than or equal to pivot
        if (array[j] < pivot)
        {
            i++; // increment index of smaller element
            swap(array[i], array[j]);
        }
        sort_call_sfml(array, window, rectangle);
    }
    swap(array[i + 1], array[end]);
    return (i + 1);
}

void QuickSort(int array[], int begin, int end, sf::RenderWindow *window, sf::RectangleShape rectangle[])
{
    if (begin < end)
    {
        int pivot_index = arrangePivot(array, begin, end,window,rectangle);

        QuickSort(array, begin, pivot_index - 1,window,rectangle);
        QuickSort(array, pivot_index + 1, end,window,rectangle);
    }
}

// merge Sort::


void merge(int array[], int const left, int const mid,
           int const right, sf::RenderWindow *window, sf::RectangleShape rectangle[])
{
    int const subArrayOne = mid - left + 1;
    int const subArrayTwo = right - mid;

    // Create temp arrays
    auto *leftArray = new int[subArrayOne],
         *rightArray = new int[subArrayTwo];

    // Copy data to temp arrays leftArray[] and rightArray[]
    for (auto i = 0; i < subArrayOne; i++)
        leftArray[i] = array[left + i];
    for (auto j = 0; j < subArrayTwo; j++)
        rightArray[j] = array[mid + 1 + j];

    auto indexOfSubArrayOne = 0, indexOfSubArrayTwo = 0;
    int indexOfMergedArray = left;

    // Merge the temp arrays back into array[left..right]
    while (indexOfSubArrayOne < subArrayOne && indexOfSubArrayTwo < subArrayTwo)
    {
        if (leftArray[indexOfSubArrayOne] <= rightArray[indexOfSubArrayTwo])
        {
            array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
            indexOfSubArrayOne++;
        }
        else
        {
            array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
            indexOfSubArrayTwo++;
        }
        indexOfMergedArray++;
        sort_call_sfml(array, window, rectangle);
    }

    // Copy the remaining elements of
    // left[], if there are any
    while (indexOfSubArrayOne < subArrayOne)
    {
        array[indexOfMergedArray] = leftArray[indexOfSubArrayOne];
        indexOfSubArrayOne++;
        indexOfMergedArray++;
        sort_call_sfml(array, window, rectangle);
    }

    // Copy the remaining elements of
    // right[], if there are any
    while (indexOfSubArrayTwo < subArrayTwo)
    {
        array[indexOfMergedArray] = rightArray[indexOfSubArrayTwo];
        indexOfSubArrayTwo++;
        indexOfMergedArray++;
        sort_call_sfml(array, window, rectangle);
    }
    delete[] leftArray;
    delete[] rightArray;
}
void mergeSort(int array[], int const begin, int const end, sf::RenderWindow *window, sf::RectangleShape rectangle[])
{
    if (begin >= end)
        return;

    int mid = begin + (end - begin) / 2;
    mergeSort(array, begin, mid, window, rectangle);
    mergeSort(array, mid + 1, end, window, rectangle);
    merge(array, begin, mid, end, window, rectangle);
}
void SelectionSort(int array[], int size, sf::RenderWindow *window, sf::RectangleShape rectangle[])
{

    for (size_t i = 0; i < size; i++)
    {
        for (size_t j = i; j < length; j++)
        {
            if (array[j] <= array[i])
            {
                swap(array[j], array[i]);
            }
            window->clear(sf::Color::Black);
            for (size_t k = 0; k < size; k++)
            {
                cout << array[k] << " ";

                rectangle[k].setSize(sf::Vector2f(screen_size_w / length, 2 * array[k]));
                FillRectangle(&rectangle[k], k, array[k]);
                window->draw(rectangle[k]);
            }
            cout << endl;
            window->display();
            if (length < 500)
            {
                this_thread::sleep_for(std::chrono::milliseconds(1000 / length));
            }
        }
    }
}
void bubbleSort(int array[], int length, sf::RenderWindow *window, sf::RectangleShape rectangle[])
{
    for (int i = 0; i < length - 1; ++i)
    {
        for (int j = 0; j < length - i - 1; ++j)
        {
            if (array[j] > array[j + 1])
            {
                int temp = array[j];
                array[j] = array[j + 1];
                array[j + 1] = temp;
                window->clear(sf::Color::Black);
                for (int k = 0; k < length; ++k)
                {
                    std::cout << array[k] << " ";
                    rectangle[k].setSize(sf::Vector2f(screen_size_w / length, 2 * array[k]));
                    FillRectangle(&rectangle[k], k, array[k]);
                    window->draw(rectangle[k]);
                }
                cout << endl;
                window->display();
                if (length < 500)
                {
                    this_thread::sleep_for(std::chrono::milliseconds(1000 / length));
                }
            }
        }
    }
}

void InsertionSort(int array[], int size, sf::RenderWindow *window, sf::RectangleShape rectangle[])
{
    int j = 0;
    for (int i = 1; i < size; i++)
    {
        j = i - 1;
        int x = array[i];
        while (j > -1 && array[j] > x)
        {

            array[j + 1] = array[j];
            j--;

            window->clear(sf::Color::Black);
            for (int k = 0; k < size; ++k)
            {
                // cout << array[k] << " ";
                rectangle[k].setSize(sf::Vector2f(screen_size_w / size, 2 * array[k]));

                FillRectangle(&rectangle[k], k, array[k]);
                window->draw(rectangle[k]);
            }
            window->display();
            //    if(length < 500){
            //         this_thread::sleep_for(std::chrono::milliseconds(100 / length));
            //         }
        }
        array[j + 1] = x;
    }
}

int main()
{
    int sortType = 0;
    cin >> length;

    // int array[100] = {
    //     83, 76, 17, 28, 38, 14, 86, 21, 75, 41, 66, 29, 50, 38, 29, 90, 31, 96, 36, 81,
    //     89, 78, 69, 42, 29, 53, 35, 52, 88, 31, 88, 30, 49, 80, 25, 45, 89, 73, 71, 45,
    //     38, 83, 69, 39, 64, 69, 72, 47, 88, 44, 83, 76, 17, 28, 38, 14, 86, 21, 75, 41, 66, 29, 50, 38, 29, 90, 31, 96, 36, 81,
    //     89, 78, 69, 42, 29, 53, 35, 52, 88, 31, 88, 30, 49, 80, 25, 45, 89, 73, 71, 45,
    //     38, 83, 69, 39, 64, 69, 72, 47, 88, 44};

    int array[length];
    for (size_t i = 0; i < length; i++)
    {
        array[i] = rand() % N;
    }

    sf::RenderWindow window(sf::VideoMode(screen_size_w, screen_size_h), "Sorting algo window", sf::Style::Titlebar);
    sf::RectangleShape rectangle[length];

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }

        window.clear(sf::Color::Black);

        // bubbleSort(array, length, &window, rectangle);
        //   InsertionSort(array, length, &window, rectangle);
        //  SelectionSort(array, length, &window, rectangle);
       // mergeSort(array, 0, length - 1, &window, rectangle);
      // QuickSort(array, 0, length - 1, &window, rectangle);
       radixSort(array, &window,rectangle);
    }

    return 0;
}
