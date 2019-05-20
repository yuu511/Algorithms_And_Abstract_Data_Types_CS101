//Elijah Cordova
//ejcordov
//pa3
//Matrix.java

//Implementation file for the Matrix ADT
class Matrix{
  //The "node" of the Matrix class
  private class Entry{
  	int column;
  	double data;

    Entry (int column, double data){
    	this.column=column;
    	this.data=data;
    }

    public String toString(){
    	String toReturn="";
    	toReturn=toReturn+("column:")+column+(" data:")+data;
    	return toReturn;
    }

    public boolean equals(Object n){
      if (n instanceof Entry){
      	Entry test = (Entry) n;
      	if (column==test.column && data==test.data){
      		return true;
      	}
      }
      return false;
    }
  }
  
  List[] rows;
  
  //creates empty matrix
  Matrix (int n){
  	if (n>=1){
      rows= new List [n+1];
      for (int i=1;i<rows.length;i++){
      	rows[i]=new List();
      }
  	}
  }
  
  //returns size
  int getSize(){
    return rows.length-1;
  }
  
  //returns non zero integers
  int getNNZ(){
  	int toReturn=0;
  	for (int i=1;i<=getSize();i++){
      toReturn+=rows[i].length();
  	}
  	return toReturn;
  }
  
  //override for object equals method, compares two matrix objects.
  public boolean equals(Object subject){
    boolean equals=true;
    Matrix m = (Matrix) subject;
    equals= (this.getSize()==m.getSize());
    for (int i=1; i<=getSize();i++){
      if (!((rows[i].equals(m.rows[i])))&&(this.getNNZ()!=m.getNNZ())){
        equals=false;
        return equals;
      }
    }
    return equals;
  }
  
  //setsmatrix to zero state
  void makeZero(){
  	for (int i=1;i<=getSize();i++){
  		rows[i]=new List();
  	}
  }
  
  //copies a matrix
  //pre: size >=1
  Matrix copy(){
    Matrix copy= new Matrix(rows.length-1);
    for (int i=1;i<=getSize();i++){
      rows[i].moveFront();
      while (rows[i].index() >= 0){
      	Entry insert= (Entry) rows[i].get();
      	copy.changeEntry(i, insert.column, insert.data);
      	rows[i].moveNext();
      }
    }
    return copy;
  }
  
  //changes ith row, jth column to specified double value
  void changeEntry (int row, int col, double x){
    if (row<1 || col<1 || row>getSize() || col>getSize()){
        System.out.print("invalid changeEntry request");
    	System.exit(1);
    }
    //overwrite
    rows[row].moveFront();
    boolean overWrite=false;
    while (rows[row].index()>=0){
    	Entry test = (Entry) rows[row].get();
    	if (test.column==col){
    		overWrite=true;
    		if (x==0.0){
    			rows[row].delete();
                return;
            } else {
               test.data=x;
               return;
            }
        }
        rows[row].moveNext();
    }
    //new insert
    if (x!=0.0 && overWrite==false){
      rows[row].moveFront();
      //non-populated list
      if (rows[row].length()==0){
      	rows[row].append(new Entry(col,x));
      	return;
      } else {
      	rows[row].moveFront();
      	while (rows[row].index()>=0){
      	  Entry test = (Entry) rows[row].get();
          //list will iterate until it finds the appropriate place
          if (test.column>col){
          	rows[row].insertBefore(new Entry (col,x));
          	return;
          }
         rows[row].moveNext();
      	}
      	rows[row].append(new Entry (col,x));
      }	
    }
  }
 
 //pre: size of Matrix must be the smae
 //returns a scaled matrix
  Matrix scalarMult (double x){
    Matrix toReturn = new Matrix(getSize());
    for (int i=1;i<=getSize();i++){
      rows[i].moveFront();
      while (rows[i].index() >= 0){
      	Entry insert= (Entry) rows[i].get();
      	toReturn.changeEntry(i, insert.column, insert.data*x);
      	rows[i].moveNext();
      }
    }
    return toReturn;
  }
  
  //pre: sizes of the matrices must be the same
  //Adds two matrices together
  Matrix add (Matrix M){
  	if (getSize()!=M.getSize()){
  		System.out.print ("Invalid matrix size for add.");
  		System.exit(1);
  	}
  	Matrix add=new Matrix(getSize());
    if (this==M)
      return this.copy().scalarMult(2);
  	for (int i=1;i<=getSize();i++){
  		add.rows[i]= addFunc (rows[i],M.rows[i]);
  	}
  	return add;
  }
  
  //Helper function to add,
  //uses a stack like process to add matrix members together.
  List addFunc (List N, List M){
    List toReturn = new List();
    N.moveFront();
    M.moveFront();
    while (N.index() >= 0 || M.index() >= 0){
    	if(N.index() >= 0 && M.index() >= 0) {
			Entry one = (Entry) N.get();
			Entry two = (Entry) M.get();
      //four seperate cases for when indexes are still within bounds
			if (one.column > two.column){
				toReturn.append(new Entry(two.column,two.data));
				M.moveNext();
			} else if (one.column < two.column) {
	           toReturn.append(new Entry (one.column,one.data));
	           N.moveNext();
			} else if (one.column == two.column && one.data+two.data==0) {
				N.moveNext();
				M.moveNext();
			} else if (one.column == two.column&& one.data+two.data!=0) {
				toReturn.append(new Entry (one.column,one.data+two.data));
				N.moveNext();
				M.moveNext();
			  }
			} 
    //2 cases to deal with leftovers
		else if (N.index() >= 0 && M.index() <=0) {
			Entry one = (Entry) N.get();
			toReturn.append (new Entry(one.column,one.data));
			N.moveNext();
		} else if (M.index() >= 0 && N.index() <=0) {
		    Entry two = (Entry) M.get();
		    toReturn.append (new Entry (two.column,two.data));
		    M.moveNext();
		}    
    }   
    return toReturn; 
  }
 
  //essentially the add function, except the second member is scaled by -1 to "subtract"
  Matrix sub (Matrix M){
  	if (getSize()!=M.getSize()){
  		System.out.print ("Invalid matrix size for add.");
  		System.exit(1);
  	}
  	Matrix sub=new Matrix(getSize());
  	M = M.scalarMult(-1);
  	for (int i=1;i<=getSize();i++){
  		sub.rows[i]= addFunc (rows[i],M.rows[i]);
  	}
  	return sub;
  }
 
 //transposes specified matrix A
  Matrix transpose(){
  	Matrix tMatrix= new Matrix(getSize()); 	
    for (int i=1;i<=getSize();i++){
    	rows[i].moveFront();
    	while (rows[i].index() >= 0){
    		Entry insert= (Entry) rows[i].get();
    		tMatrix.changeEntry(insert.column,i,insert.data);
    		rows[i].moveNext();
    	}
    }
    return tMatrix;
  }
  
  //pre: sizes of matrices must be the same
  //multiplies two matrices
  Matrix mult(Matrix N){
  	if(getSize() != N.getSize()){
  		System.out.print ("mult error.");
  		System.exit(1);
    }
  	Matrix mMatrix = new Matrix (getSize());
  	Matrix nT = N.transpose();
  	for (int i=1; i<= getSize(); i++){
  		if (rows[i].length() ==0) continue;
  		for (int j=1; j<= getSize(); j++){
  			if(nT.rows[j].length()==0) continue;
  			mMatrix.changeEntry(i,j,dot(rows[i],nT.rows[j]));
  		}
    }
    return mMatrix;
  }
  
  //helper function for mult
  double dot (List N, List M){
  	double toReturn = 0.0;
  	N.moveFront();
  	M.moveFront();
  	while(N.index()>=0 && M.index() >=0){
  		Entry one = (Entry) N.get();
  	    Entry two = (Entry) M.get();
  	    if (one.column > two.column) {
  	    	M.moveNext();
  	    } else if (one.column < two.column) {
  	    	N.moveNext();
  	    } else {
  	    	toReturn = toReturn + (one.data * two.data);
  	    	N.moveNext();
  	    	M.moveNext();
  	    }
  	}
  	return toReturn;
  }
   
  //method to override objects (toString()) method
  public String toString(){
    String matrixS = "";
    for (int i=1;i<=getSize();i++){
    	rows[i].moveFront();
    	if (rows[i].get()!=null){
    		matrixS=matrixS.concat(i+":");
	    	while (rows[i].index() >= 0){
	    		Entry insert= (Entry) rows[i].get();
	    		matrixS=matrixS.concat(" ("+insert.column + ", " + insert.data + ")");
	    		rows[i].moveNext();
	    	}
	    	matrixS=matrixS.concat("\n");
        }
    }
    return matrixS;
  }



}