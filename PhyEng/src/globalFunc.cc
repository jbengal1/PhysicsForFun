#include <SFML/Graphics.hpp>
#include <iostream>
#include <cmath>
#include "../include/globalFunc.hh"
#include <stdio.h>

// This function pushing each element of a given double array one index backward (removing the first element), and adds a new number to the end.
void cyclicArr(double array[], double new_number, int arr_size){
    for(int n = 0; n<arr_size-1; n++){
        array[n] = array[n+1];
    }
    array[arr_size-1] = new_number;
}

double mean(double array[], int arr_size){
    double mean_array = 0;
    for(int n = 0; n<arr_size-1; n++){
        mean_array += array[n];
    }
    mean_array /= arr_size;
    return mean_array;
}

int sign(double x){
    if(x>0) return 1;
    if(x>0) return -1;
}