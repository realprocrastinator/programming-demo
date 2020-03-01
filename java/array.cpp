// compile and run java 
javac program.java
java program



//=============================================================
// define array
int[] a; // declare an array
int[] a = new int[100]; // new operator to create the array
int[] a = new int[n]; // array length does not need to be constant
String[] names = new String[10];


// array init
int[] smallprime = {1,2,5,7}; // no need to call new since it is implied
new int[] {1,2,3,4,5}; // anonymous array can be used to reinit a variable
// RHS would init an array allocate memory and the variable will be
// reference to the new array , the name of the array is not necessary
// the old array, where the variable refers to will be garbage collected
smallPrime = new int[] {3,4,5,6}; 
int[] anonymous = {3,4,5,6}; // same as above
smallPrime = anonymous;

// copy array
int[] num = smallPrime; // like assign a pointer
num[2] = 99; // now smallPrime[2] is also 99

int[] copied = Arrays.copyOf(num,num.length); // like memcopy in c
// usually used to expand the array
// if the lenght is longer than the copied array will be padded with 0
// or false if bool array
// if the length is less, then copied data will be truncated accordingly
// allocate new memory and copied the data from the old array, then
// the vairable reassigned the old array memory will be garbage collected 
luckNumbers = Arrays.copyOf(luckNumbers,2* luckNumbers.length);

// note: java array is essentially pointer , but it can not do
// pointer arithemetic

// for each loop
for(variable : collection) statement // sytax
for(int element: a): // less error prone when index is not needed
  System.out.println(element);


// sort array
import java.until.Arrays
Arrays.sort(a); // apply quick sort to the array in place

//================================================
// multi dimention array
int[][] balance; // declarea 2d array
balance = new double[NYEARS][NRATES]; // init the array
int[][] magicSqaure = { // specify values
  {1,2,3},
  {3,4,5}
};














