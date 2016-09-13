package learned;
/*
 * Usually we find median by sort the array and then get the len/2 one, but it takes O(nlog(n))
 * Here is the median of medians algorithm, but it seems not so good in practice, anyway, it is O(n)(best and worst)
 * A good explanation of this Algo is at https://interviewalgorithm.wordpress.com/sortingordering/median-of-medians-algorithm/
 */
/*
 *  this algo is O(n) because when we recursive get kth element, we at most take 20% of current array.
 *  because they are group of 5, so the pivot is between 30% - 70%.
 */

import java.util.Arrays;

public class MedianOfMedians {
	// this function is good to get a pivot from whole array
	// we divide array by group of 5, and choose median of each groups
	// then we choose median of medians
	// all low and high variables are index inclusive in array(at least 0 and at most arr.length - 1)
	private static int getPivot(int[] arr, int low, int high){
		// if size of array is small, return directly
		if(high - low + 1 <= 9){
			Arrays.sort(arr);
			return arr[(arr.length)/2];
		}
		// Otherwise we divide the array into groups of 5 and recursively find median
		int[] temp = null;
		int[] medians = new int[(int)Math.ceil((double)(high - low + 1) / 5)];
		int medianIndex = 0;
		while(low <= high){
			temp = new int[Math.min(5, high - low + 1)];
			for(int i = 0; i < temp.length && low <= high; i++){
				temp[i] = arr[low];
				low++;
			}
			Arrays.sort(temp);
			medians[medianIndex] = temp[temp.length/2];
			medianIndex++;
		}
		return getPivot(medians, 0, medians.length - 1);
	}
	
	// return the index of pivot
	private static int partition(int[] arr, int low, int high){
		int pivot = getPivot(arr, low, high);
		int pointer = low;
		for(int i = low; i < high; i++){
			if(arr[i] <= pivot){
				int temp = arr[i];
				arr[i] = arr[pointer];
				arr[pointer++] = temp;
			}
		}
		return pointer;
	}
	
	private static int findKth(int[] arr, int k, int low, int high){
		int m = partition(arr,low,high);
		// what we have find is just the kth element
		if (m - low + 1 == k){
			return arr[m];
		}
		// if mth is greater than kth, search its left
		if (m - low + 1 > k){
			return findKth(arr, k, low, m - 1);
		} else {
			return findKth(arr, k - (m - low + 1), m + 1, high);
		}		
	}
	
	public static void main(String[] args){
		int nElements = 10000;
		int[] arr = new int[nElements];
		for(int i = 0; i < nElements; i++){
			arr[i] = (int)(2000* Math.random());
		}
		System.out.println("Array:");
		printArray(arr, 0, nElements);
		// test findKth to find median
		double median1 = -1;
		if(nElements % 2 == 1){
			median1 = findKth(arr,(arr.length)/2 + 1, 0, arr.length - 1);
		} else{
			median1 = (findKth(arr,arr.length/2, 0, arr.length - 1) + findKth(arr, arr.length/2 + 1, 0, arr.length - 1))/2.0;
		}
		System.out.println("median1 : " + median1);
		
		Arrays.sort(arr);
		printArray(arr, 0, nElements);
		if(nElements % 2 == 1){
			System.out.println("Median using sorting : " + arr[(arr.length)/2]);
		} else{
			System.out.println("Median using sorting : " + (arr[(arr.length)/2] + arr[arr.length/2 - 1])/ 2.0);
		}
		
	}
	
	private static void printArray(int arr[],int low, int high){
        System.out.print("[  ");
        for(int i = low; i < high; i++){
            System.out.print(arr[i] + "  ");
        }
        System.out.println("]");
    }

}
