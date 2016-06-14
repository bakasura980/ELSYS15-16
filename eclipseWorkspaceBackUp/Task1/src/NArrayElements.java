
public class NArrayElements {
	
	public static int getMax(int[] arr) {
		int max = arr[0];
		for(int i = 1; i < arr.length; i++) {
			if(arr[i] > max) {
				max = arr[i];
			}
		}
		return max;
	}
	
	public static int getMin(int[] arr) {
		int min = arr[0];
		for(int i = 1; i < arr.length; i++) {
			if(arr[i] < min) {
				min = arr[i];
			}
		}
		return min;
	}
	
	
	public static double getSqrt(int[] arr) {
		return Math.sqrt(getMax(arr) - getMin(arr));
	}
	
	public static boolean canDivideBy3(int num) {
		return num % 3 == 0;
	}
		
	public static boolean contains3(int num) {
		return String.valueOf(num).contains("3");
	}
	
	public static void main(String[] args) {
		int[] arr = {1,2,3,4,78,26,23};
		System.out.println("1----------------");
		System.out.println("sqrt: " + getSqrt(arr));
		
		System.out.println("2----------------");
		for(int i = 0; i < arr.length;i++) {
			if(canDivideBy3(arr[i])) {
				System.out.println(arr[i]);
			}
		}
		
		System.out.println("3-----------------");
		for(int i = 0; i < arr.length;i++) {
			if(contains3(arr[i])) {
				System.out.println(arr[i]);
			}
		}
		
		
	}

}
