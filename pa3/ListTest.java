//Elijah Cordova
//ejcordov
//pa3
//ListTest.java


//Sample test file for the List ADT.
//Expected results below.
class ListTest{
  public static void main (String[] args){
    List A= new List();
    List B= new List();
    for (int i=0;i<1;i++){
      Object bloop=new Object();
      A.append(bloop);
      B.append(bloop);
    }
    System.out.println (A.length());
    System.out.println (B.length());
    System.out.println (A.front());
    System.out.println (A.back());
    B.clear();
    System.out.println(B.toString());
    A.moveFront();
    Object bloop2=new Object();
    A.insertBefore(bloop2);
    System.out.println(A.toString());
    A.moveBack();
    System.out.println(A.get());
    Object bloop3 =new Object();
    A.insertAfter(bloop3);
    System.out.println(A.toString());
    A.movePrev();
    System.out.println(A.get());
     A.moveNext();
    System.out.println(A.get());
    A.moveFront();
    A.deleteFront();
    System.out.println(A.get());
    A.moveBack();
    A.deleteBack();
    System.out.println(A.get());
    A.moveFront();
    A.moveNext();
    A.delete();
    System.out.println(A.toString());
  }

}

//Expected output

// 1
// 1
// (Object memory address)
// (Object memory address)
// Cleared List
// (Object memory addresses (length 2)
// (Object memory address)
// (Object memory addresses) (Length 3)
// null
// null
// null
// null
// (Object memory address)