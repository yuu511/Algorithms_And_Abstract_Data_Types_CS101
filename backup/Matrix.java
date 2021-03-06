class Matrix{
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

  Matrix (int n){
  	if (n>=1){
      rows= new List [n+1];
      for (int i=1;i<rows.length;i++){
      	rows[i]=new List();
      }
  	}
  }

  int getSize(){
    return rows.length-1;
  }

  int getNNZ(){
  	int toReturn=0;
  	for (int i=1;i<=getSize();i++){
      toReturn=+rows[i].length();
  	}
  	return toReturn;
  }

  void makeZero(){
  	for (int i=1;i<=getSize();i++){
  		rows[i]=new List();
  	}
  }

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
      if (rows[row].length()==0){
      	rows[row].append(new Entry(col,x));
      	return;
      } else{
      	rows[row].moveFront();
      	while (rows[row].index()>=0){
      	  Entry test = (Entry) rows[row].get();
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

  Matrix scalarMult (double x){
    Matrix toReturn = copy();
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

  Matrix add (Matrix M){
  	if (getSize()!=M.getSize()){
  		System.out.print ("Invalid matrix size for add.");
  		System.exit(1);
  	}
  	Matrix add=copy();
  	for (int i=1;i<=getSize();i++){
  		add.rows[i]= addFunc (rows[i],M.rows[i]);
  	}
  	return add;
  }

  List addFunc (List N, List M){
    List toReturn = new List();
    N.moveFront();
    M.moveFront();
    while (N.index() >= 0 || M.index() >= 0){
    	if (N.index() >= 0 || M.index() >= 0){
    		Entry one = (Entry) N.get();
    		Entry two = (Entry) M.get();
    		if (one.column > two.column){
    			toReturn.append(new Entry(two.column,two.data));
    			M.moveNext();
    		} else if (one.column < two.column) {
               toReturn.append(new Entry (one.column,one.data));
               N.moveNext();
    		} else if (one.column == two.column) {
    			toReturn.append(new Entry (one.column,one.data+two.data));
    			N.moveNext();
    			M.moveNext();
    		} else if (N.index() >= 0) {
    			Entry leftoverN = (Entry) N.get();
    			toReturn.append (new Entry(leftoverN.column,leftoverN.data));
    			N.moveNext();
    	    } else if (M.index() >=0) {
    	    	Entry leftoverM= (Entry) M.get();
    	    	toReturn.append (new Entry (leftoverM.column,leftoverM.data));
    	    }
    	} 
    }
    return toReturn; 
  }

  Matrix sub (Matrix M){
  	if (getSize()!=M.getSize()){
  		System.out.print ("Invalid matrix size for add.");
  		System.exit(1);
  	}
  	Matrix sub=copy();
  	M = M.scalarMult(-1);
  	for (int i=1;i<=getSize();i++){
  		sub.rows[i]= addFunc (rows[i],M.rows[i]);
  	}
  	return sub;
  }

  Matrix transpose (){
  	Matrix tMatrix= copy(); 	
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

  public String toString(){
    String toReturn = "";
    for (int i=1; i<=getSize();i++){
    	if (rows[i].length() > 0){
    		toReturn = toReturn+ (i + ": " + rows[i] + "\n");
    	}
    }
    return toReturn;
  }
}