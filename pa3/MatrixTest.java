//Elijah Cordova
//ejcordov
//pa3
//MatrixTest.java

//Small test module to check to test the various functions of Matrix.
//Expected results below.
class MatrixTest{
  public static void main (String[] args){
  	Matrix a= new Matrix (5);
  	for (int i=1;i<6;i++){
  	  for (int j=1;j<6;j++){	
  	    a.changeEntry(i,j,i);
  	  }
    }
 
  	a.changeEntry(5,3,300);
  	a.changeEntry(5,2,200);
  	a.changeEntry(5,4,400);
  	a.changeEntry(5,5,500);
  	a.changeEntry(5,1,100);
    a.changeEntry(5,3,5.0);
  	a.changeEntry(5,2,5.0);
  	a.changeEntry(5,4,5.0);
  	a.changeEntry(5,5,5.0);
  	a.changeEntry(5,1,5.0);
  	Matrix b = a.scalarMult(3);
  	Matrix c = b.add(a);
    Matrix d = a.sub(b);
    Matrix e = a.transpose();
    Matrix f = a.sub(a);
    Matrix g = f.copy();
    Matrix h = a.mult(a);
    Matrix i = h.copy();


    
    System.out.println ("A has " + a.getNNZ() + " non-zero entries and is " + a.getSize() + "x"+ a.getSize() );
    System.out.println (a.toString());
    System.out.println ("B has " + b.getNNZ() + " non-zero entries");
    System.out.println ("and is (3)*A:");
    System.out.println (b.toString());
    System.out.println ("B+A:");
    System.out.println (c.toString());
  	System.out.println ("A-B:");
  	System.out.println (d.toString());
  	System.out.println ("Transpose A:");
  	System.out.println (e.toString());
    System.out.println ("A-A");
  	System.out.println (f.toString());
  	System.out.println ("emptycopy:");
  	System.out.println (g.toString());
    System.out.println ("A*A");
    System.out.println (h.toString());
    System.out.println ("normalcopy:");
  	System.out.println (i.toString());
  	 

  }
}

//expected output:


// A has 25 non-zero entries and is 5x5
// 1: (1, 1.0) (2, 1.0) (3, 1.0) (4, 1.0) (5, 1.0)
// 2: (1, 2.0) (2, 2.0) (3, 2.0) (4, 2.0) (5, 2.0)
// 3: (1, 3.0) (2, 3.0) (3, 3.0) (4, 3.0) (5, 3.0)
// 4: (1, 4.0) (2, 4.0) (3, 4.0) (4, 4.0) (5, 4.0)
// 5: (1, 5.0) (2, 5.0) (3, 5.0) (4, 5.0) (5, 5.0)

// B has 25 non-zero entries
// and is (3)*A:
// 1: (1, 3.0) (2, 3.0) (3, 3.0) (4, 3.0) (5, 3.0)
// 2: (1, 6.0) (2, 6.0) (3, 6.0) (4, 6.0) (5, 6.0)
// 3: (1, 9.0) (2, 9.0) (3, 9.0) (4, 9.0) (5, 9.0)
// 4: (1, 12.0) (2, 12.0) (3, 12.0) (4, 12.0) (5, 12.0)
// 5: (1, 15.0) (2, 15.0) (3, 15.0) (4, 15.0) (5, 15.0)

// B+A:
// 1: (1, 4.0) (2, 4.0) (3, 4.0) (4, 4.0) (5, 4.0)
// 2: (1, 8.0) (2, 8.0) (3, 8.0) (4, 8.0) (5, 8.0)
// 3: (1, 12.0) (2, 12.0) (3, 12.0) (4, 12.0) (5, 12.0)
// 4: (1, 16.0) (2, 16.0) (3, 16.0) (4, 16.0) (5, 16.0)
// 5: (1, 20.0) (2, 20.0) (3, 20.0) (4, 20.0) (5, 20.0)

// A-B:
// 1: (1, -2.0) (2, -2.0) (3, -2.0) (4, -2.0) (5, -2.0)
// 2: (1, -4.0) (2, -4.0) (3, -4.0) (4, -4.0) (5, -4.0)
// 3: (1, -6.0) (2, -6.0) (3, -6.0) (4, -6.0) (5, -6.0)
// 4: (1, -8.0) (2, -8.0) (3, -8.0) (4, -8.0) (5, -8.0)
// 5: (1, -10.0) (2, -10.0) (3, -10.0) (4, -10.0) (5, -10.0)

// Transpose A:
// 1: (1, 1.0) (2, 2.0) (3, 3.0) (4, 4.0) (5, 5.0)
// 2: (1, 1.0) (2, 2.0) (3, 3.0) (4, 4.0) (5, 5.0)
// 3: (1, 1.0) (2, 2.0) (3, 3.0) (4, 4.0) (5, 5.0)
// 4: (1, 1.0) (2, 2.0) (3, 3.0) (4, 4.0) (5, 5.0)
// 5: (1, 1.0) (2, 2.0) (3, 3.0) (4, 4.0) (5, 5.0)

// A-A

// emptycopy:

// A*A
// 1: (1, 15.0) (2, 15.0) (3, 15.0) (4, 15.0) (5, 15.0)
// 2: (1, 30.0) (2, 30.0) (3, 30.0) (4, 30.0) (5, 30.0)
// 3: (1, 45.0) (2, 45.0) (3, 45.0) (4, 45.0) (5, 45.0)
// 4: (1, 60.0) (2, 60.0) (3, 60.0) (4, 60.0) (5, 60.0)
// 5: (1, 75.0) (2, 75.0) (3, 75.0) (4, 75.0) (5, 75.0)

// normalcopy:
// 1: (1, 15.0) (2, 15.0) (3, 15.0) (4, 15.0) (5, 15.0)
// 2: (1, 30.0) (2, 30.0) (3, 30.0) (4, 30.0) (5, 30.0)
// 3: (1, 45.0) (2, 45.0) (3, 45.0) (4, 45.0) (5, 45.0)
// 4: (1, 60.0) (2, 60.0) (3, 60.0) (4, 60.0) (5, 60.0)
// 5: (1, 75.0) (2, 75.0) (3, 75.0) (4, 75.0) (5, 75.0)