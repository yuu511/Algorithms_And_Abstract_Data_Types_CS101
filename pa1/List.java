class List{
    
  private class Node{
  int data;
  Node next;
  Node previous;
   
    Node(int data){
      this.data= data;
  	  next=null;
  	  previous=null;
  	}

    public String toString(){
    	String toReturn;
    	toReturn= ("Node with data: "+data);
    	return toReturn;
    }
  }

//pointers to the front and back elements of list, and a cursor
//int to store size of list and index of cursor.
private Node cursor;
private Node front;
private Node back;
private int size;
private int cursorIndex;

//Creates empty List
  List (){
  cursor=null;
  front=null;
  back=null;
  size=0;
  }

//Access Functions

//returns length of list
  int length(){
    return size;
  }

//returns index of cursor
  int index(){
    if (cursor != null){
     return cursorIndex;
    }
    return -1;
  }

/**
 * front(): returns front
 * preconditions : length()>0
 * postconditions: returns data from front
 */

  int front(){
  	Node test= front;
  	if (size>0)
  	return  test.data;
    //case for if front is called on empty list
  	System.out.println("front called on empty list!");
  	return -1;
  }

/**
 * back(): returns back
 * preconditions : length()>0
 * postconditions: returns data from back
 */

  int back(){
  	Node test= back;
  	if (size>0)
    return test.data;
    //case for if back is called on empty list
  	System.out.println("back called on empty list!");
  	return -1;
  }
  
 /**
  * returns data of cursor
  * precondtions: length()>0, index()>=0
  * postconditions: returns data of cursor
  */
  int get(){
    if (size!=0 && cursor !=null)
    return cursor.data;
    //case for if get is called on empty list or cursor is undefined
    return -1;
  }

/**
 * equals(List)
 * compares two lists to see if they are the same
 * precondtions: another List L
 * postconditions: returns true or false for if the two lists are the same
 */

  boolean equals(List L){
  	//if the two lists are of the same size and their front element is the same,
  	//make the comparison.
    if (L.length()==size){
    Node firstFront = front;
    Node secondFront = L.front;
      for (moveFront();index()>=0;moveNext()){
      	if (firstFront.data!=secondFront.data){
      		return false;
      	}
      	firstFront=firstFront.next;
      	secondFront=secondFront.next;
      }
      return true;
    }
    return false;
  }

// Manipulation procedures

//resets list
  void clear(){
  	front=null;
  	back=null;
  	cursor=null;
  	size=0;
  }
  
//moves cursor to front
  void moveFront(){
  	if(size>0){
    cursor=front;
    }
    cursorIndex=0;
  }

//moves cursor to back
  void moveBack(){
  	if(size>0)
  	cursor=back;
    cursorIndex=size-1;
  }

// moves cursor one step towards the front, if at front, moves cursor
// to undefined,if cursor is undefined, does nothing
  void movePrev(){
  	if (cursor != null){
  		Node test= cursor;
  		if(test == front){
  			cursor=null;
  		}
  	    else{
  	      cursor=test.previous;
  	      cursorIndex--;
  	    }
  	}
  }


// moves cursor one step towards the back, if at back, moves cursor
// to undefined,if cursor is undefined, does nothing
  void moveNext(){
  	if (cursor != null){
  		Node test= cursor;
  		if(test == back){
  			cursor=null;
  		}
  		else{
  	      cursor=test.next;
  	      cursorIndex++;
  	    }
  	}
  }

/**
 * prepend(int)
 * preconditions: list must be created, paramater int for data to be inserted
 * postconditions: inserts data before front element, if list
 * is empty places data at the front and back (because size=1 after insertion)
 */
  void prepend(int data){
  	//case for list not having any elements
  	if(size==0){
    Node newN = new Node (data);
    front = newN;
    back= newN;
    size++;
    }
    else{
    Node n= new Node (data);
    front.previous=n;
    n.next=front;
    front=n;
    size++;
    cursorIndex++;
    }
  }

/**
 * append(int)
 * preconditions: list must be created, paramater int for data to be inserted
 * postconditions: inserts data after back element, if list
 * is empty places data at front and back (because size=1 after insertion)
 */

  void append(int data){
  	//case for list not having any elements
  	if(size==0){
    Node newN = new Node (data);
    front = newN;
    back= newN;
    size++;
    }
    else{
    Node n= new Node (data);
    back.next=n;
    n.previous=back;
    back=n;
    size++;
    }
  }

/** 
 * void insertBefore(int)
 * preconditions: length()>0 index >=0
 * postconditions: inserts new element before cursor.
 */
  void insertBefore(int data){
  	if (cursor != null && size > 0){
      Node n= new Node (data);
      if (cursor==front){
      	prepend(data);
      }
      else{
        cursor.previous.next=n;
        n.previous=cursor.previous;
        n.next=cursor;
        cursor.previous=n;
        size++;
        cursorIndex++;
      }
  	}
  }


/**
 * void insertAfter(int)
 * preconditions: length()>0 index >=0
 * postconditions: inserts new element after cursor.
 */
  void insertAfter(int data){
  	if (cursor != null && size > 0){
      Node n= new Node (data);
      if (cursor==back){
        append(data);
      }
      else{
        cursor.next.previous=n;
        n.next=cursor.next;
        n.previous=cursor;
        cursor.next=n;
        size++;
      }
  	}
  }
/**
 * void deleteFront()
 * preconditions: length()>0
 * postconditions: delete front number 
 */
  void deleteFront(){
    if (cursor==front){
      cursor=null;
    }

    if (size >0){
      if (size > 1){
       front=front.next;
       front.previous.next=null;
       front.previous=null;
       size--;
       cursorIndex--;
      }
      else{
        front=null;
        size--;
      }
      

    }
  }

/**
 *  void deleteBack() 
 *
 *  preconditions: length()>0
 *  postconditions: delete back number 
 */

  void deleteBack(){
     if (cursor==back){
      cursor=null;
    } 

    if( size>0){
      if (size > 1){
       back=back.previous;
       back.next.previous=null;
       back.next=null;
      }
      else{
        back=null;
      }
      size--;
     }	
  }

/** void delete()
 *  preconditions: length()>0 index()>0
 *  postconditions: delete current cursor
 */
  void delete(){
  	if (cursor !=null && size > 0){
      //must include case for if cursor is at front or back
  	  if(cursor==front){
  	  	deleteFront();
  	  }
  	  else if (cursor==back){
  	   	deleteBack();
  	  }
  	  //normal case
  	  else{
        cursor.previous.next=cursor.next;
        cursor.next.previous=cursor.previous;
        cursor=null;
        size--;
      }
  	}
  }

  //OTHER METHODS

/** toString() 
 * preconditions: length()>0
 * postconditions: returns string representation of list.
 */
  public String toString(){
  	String toReturn=("");
  	if(size>0){
      for(moveFront();index()>=0;moveNext()){

            toReturn=toReturn+get()+(" ");
       }
    }
    toReturn= toReturn.trim();
     return toReturn;
  }
  
/**
 * copy()
 * precondtions: 
 * postcondtions: returns copy of list.
 */
  List copy() {
    //stores place of cursor and index before cursor is used 
    Node cursorCopy=cursor;
    int indexCopy=cursorIndex;
    List copy=new List();
    if (size > 0){
     for(moveFront();index()>=0;moveNext()){
       copy.append(get());
     }
    }
    else{
    copy=new List();
    }

    //reset cursor and index 
    cursorIndex=indexCopy;
    cursor=cursorCopy;
    return copy;
  }




}