#include <iostream>

class ArrTest {
private:
    int *arr;
    int len;
public: 
    ArrTest(int size) :len(size) {
        arr = new int[size]; 
    }
    ~ArrTest() {
        delete arr;  // deleted
    }
    int length();
    int& operator[](int idx);
    ArrTest& append(int size);
    ArrTest& append(ArrTest& arr1);
};

int ArrTest::length(){
    return len;
}

//calling sequence : arr[n], &-> reference variable 
int& ArrTest::operator[](int idx) {
    if (idx < 0 || idx >= len) {
        // exit(1) can terminate program if there is error
        std::cout << "Out of bound" << std::endl; //exit(1);
        //return -1; can return any number '-1'
    }
    //return *(arr + idx);
    //pointer type <- arternative of return below;
    //array type, read only -> data return only
    return arr[idx];
}

ArrTest& ArrTest::append(int size) {
    int* arr1 = new int[len+size];
    memcpy(arr1, arr, len * sizeof(int));
    delete arr;
    arr = arr1;
    len += size;
    return *this;
}

ArrTest& ArrTest::append(ArrTest& arr1) {
    int new_length = this->len + arr1.length();
    int* arr2 = new int[new_length];
    for (int i = 0; i < this->len; i++) { arr2[i] = arr[i]; }
    for (int i = this->len; i < new_length; i++) { arr2[i] = arr1[i-(this->len)]; }
    delete arr;
    arr = arr2;
    this->len += arr1.length();
    return *this;
}

//ArrTest& ArrTest::append(ArrTest& brr) {
//    int *arr1 = new int[this->len + brr.length()];
//    memcpy(arr1, arr, len * sizeof(int));
//    memcpy(arr1 + len, brr.arr, brr.length() * sizeof(int));
//    delete arr; 
//    this->arr = arr1;
//    len += brr.length();
//    return *this;
//}


int main()
{   
    // a1 declared to test 
    
    ArrTest arr(5), arr1(5);
    
    int a1[] = { 1, 2, 3, 4, 5 };

    for (int i = 0; i < 5; i++) {
        arr[i] = a1[i];
    }

    int a2[] = { 6, 7, 8, 9, 10 };

    for (int i = 0; i < 5; i++) {
        arr1[i] = a2[i];
    }

    arr.append(arr1);
    
    for (int i = 0; i < arr.length(); i++) {
        printf("arr[%d] =  %d\n",i, arr[i]);
    }
    return 0;
}
