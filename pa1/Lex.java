import java.io.*;
import java.util.*;
import java.lang.Object;
class Lex{

public static BufferedWriter writer;
public static String[] token = null;
public static int lineNumber = 0;

/*
 * readInput(String)
 * precondtions : string containing name of input file
 * postconditions: Reads inputs from file and stores inputs in an array (declared above as a global variable)
 */

  static void readInput(String input){
    try{
      String line ="";   
      LinkedList<String> linkedList = new LinkedList<String>();
      BufferedReader in = new BufferedReader(new FileReader(input));
        while((line = in.readLine()) != null){
          linkedList.add(line);
          lineNumber++;     
        }
      token= linkedList.toArray(new String[linkedList.size()]);
    }
    catch(Exception e){
      System.out.print("Scanner error.");
    }	
  }

/**
  * performOperations (String[])
  * preconditions: String array containing words to be sorted.
  * postconditions: reads an array, sorts the indices into a list, then prints it out on the specified 
  * output file in lexical order.
  */
  static void performOperations(String[] data){
    //Creation of list with indices
    List list= new List();
    String[] subA = new String[data.length];

    //Sort indices into list

    //add the first element of the list and subarray (so the for loop has something to compare to)         
    list.append(0);
    subA[0]=data[0];
    for (int i=1;i<data.length;i++){
      list.moveBack();
      String key= data[i];
      int j; 
    //decrement cursor position until the value of key is more than the number the cursor is pointing to
      for (j=i-1; j>=0 && key.compareTo(data[list.get()])<0;j--){
       list.movePrev();
      } 
    //the cursor will be defined at 0 if the key goes through all the numbers and turns out to
    //be the lowest one, so add to the front of the list
      if (list.get()==-1){
         list.prepend(i);
      }
    //otherwise insert the key after the number found by the cursor in the for loop,
    //which is a value less than the key.
      else{
        list.insertAfter(i);
      }
    }



   //Print out the list in order
    try{
      
        for (list.moveFront();list.index()>=0;list.moveNext()){
          writer.write(data[list.get()]+"\n");
        }
    }
    catch(Exception e){
        System.out.print("BufferedWriter error.");
    }
 }

  public static void main (String[] args){
    if (args.length == 2){
      try{
       writer=new BufferedWriter(new FileWriter(args[1]));
       readInput(args[0]);
       performOperations(token);
       writer.close();
      }
      catch(Exception e){
        System.out.print("BufferedWriter error.");
      }
    }
    else{
  	  System.out.print("Please input 2 arguments.");
  	  System.exit(1);
    }
  } 
}