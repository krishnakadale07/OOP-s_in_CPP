# include <iostream>
# include <algorithm>
using namespace std;

int main(){
    int n , i , j , c;
    int arr[100];


    cout << "Enter the Size of the array : ";
    cin >> n;

    cout << "Enter " << n << " numbers : ";
    for(i = 0 ; i < n ; i++){
    cin >> arr[i];
    }
    cout << "Your Entered Array is : \n";
    for(i = 0 ; i < n ; i++){
    cout << arr[i] << " ";
    }


    cout << "Enter 1 , 2 or 3 for preffered sorting type:\n 1] Bubble Sort\n 2] Selection Sort\n 3] Insertion Sort\n";
    cin >> c;

    //-----Bubble Sort-----
    if( c == 1){
        for(int i = 0 ; i < n - 1 ; i++)
        {
            for(int j = 0 ; j < n - 1 - i ; j++)
            {
                if(arr[j] > arr[j + 1])
                {
                    swap(arr[j],arr[j + 1]);
                }
            }
        }
    }

    //-----Selection Sort-----
    if( c == 2 ){
        for(i = 0; i < n - 1; i++){
           int min_idx = i;
           for(j = i + 1; j < n; j++){
               if(arr[j] < arr[min_idx]){
                   min_idx = j;
               }
           }
           swap(arr[i], arr[min_idx]);
        }
    }
    cout << "The Sorted Array is : ";
    for (i = 0 ; i < n ; i++)
    {
        cout << arr[i] << " ";
    }

    //-----Insertion Sort------
    if( c == 3 ){
        for(i = 1; i < n; i++){
            int key = arr[i];
            j = i - 1;
            while(j >= 0 && arr[j] > key){
                arr[j + 1] = arr[j];
                j = j - 1;
            }
            arr[j + 1] = key;
        }
    }
}
