package learned;


public class QuickSort {
	// all low and high variables are index of array inclusively(means the length of array is high + 1)
	private static void qsort(int[] arr, int low, int high){
		if(low >= high){
			return;
		}
		// get the real index of pivot, we need minus one
		int index = partition(arr, low, high) - 1;
		qsort(arr,low, index - 1);
		qsort(arr, index + 1, high);
		
	}
	
	// return the index + 1 of pivot, because at the end of loop, the pointer has increment one more 
	private static int partition(int[] arr, int low, int high){
		int pivot = arr[high];
		int pointer = low;
		for(int i = low; i <= high; i++){
			if(arr[i] <= pivot){
				swap(arr, i, pointer);
				pointer++;
			}
		}
		return pointer;
	}
	private static void swap(int[] arr, int i, int j){
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
	
	public static void main(String[] args){
		int nElements = 100;
		int[] arr = new int[nElements];
		for(int i = 0; i < nElements; i++){
			arr[i] = (int)(65* Math.random());
		}
		System.out.println("Array:");
		printArray(arr, 0, nElements);
		qsort(arr, 0, arr.length - 1);
		System.out.println("Array after quicksort:");
		printArray(arr, 0, nElements);
		
	}
	
	private static void printArray(int arr[],int low, int high){
        System.out.print("[  ");
        for(int i = low; i < high; i++){
            System.out.print(arr[i] + "  ");
        }
        System.out.println("]");
    }
}
