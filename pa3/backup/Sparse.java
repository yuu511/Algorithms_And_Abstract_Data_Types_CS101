//Elijah Cordova
//ejcordov
//pa3
//Sparse.java

//The main client of the program.
import java.io.*;
import java.util.*;
import java.lang.Object;

class Sparse{ 
    public static BufferedWriter writer;
    
    //Pre: name of input file to be interpreted
    //preformoperations() reads input from the text file. interprets it, and creates the appropriate matrices.
	public static void performOperations(String input) throws IOException{
		int matrixA;
		int matrixB;
		int lineC=0;
		String[] token= null;
		Scanner in= new Scanner (new File(input));
		String line = in.nextLine()+" ";
		token = line.split("\\s+");
		matrixA = Integer.parseInt(token[1]);
		matrixB = Integer.parseInt(token[2]) + matrixA;
        
        Matrix A=new Matrix (Integer.parseInt(token[0]));
        Matrix B=new Matrix (Integer.parseInt(token[0]));

		while (in.hasNextLine()){
			line= in.nextLine()+" ";
			token= line.split("\\s+");
			lineC++;
			if (matrixA+1 >= lineC && lineC > 1){
              A.changeEntry(Integer.parseInt(token[0]),Integer.parseInt(token[1]),Double.parseDouble(token[2]));
			}
			if (matrixB+2 >= lineC && lineC > matrixA + 2){
              B.changeEntry(Integer.parseInt(token[0]),Integer.parseInt(token[1]),Double.parseDouble(token[2]));
			}
		}

		//send out the matrices to be operated and shown off
		printOut(A,B);
	}
    
    //Pre: 2 Matrices : Matrix A, Matrix B
    //Do operations involving these matrices
    //Print out the results in the file specified previously.
	public static void printOut (Matrix A, Matrix B){
        try{
        	writer.write("A has "+ A.getNNZ() + " non-zero entries:\n");
        	writer.write(A.toString()+"\n");
        	writer.write("B has "+ B.getNNZ() + " non-zero entries:\n");
        	writer.write(B.toString()+"\n");
        	writer.write("(1.5)*A =\n");
        	writer.write(A.scalarMult(1.5).toString()+"\n");
        	writer.write("A+B =\n");
        	writer.write(A.add(B).toString()+"\n");
        	writer.write("A+A =\n");
        	writer.write(A.add(A.copy()).toString()+"\n");
        	writer.write("B-A =\n");
        	writer.write(B.sub(A).toString()+"\n");
        	writer.write("A-A =\n");
        	writer.write(A.sub(A.copy()).toString()+"\n");
        	writer.write("Transpose (A) =\n");
        	writer.write(A.transpose().toString()+"\n");
        	writer.write("A*B =\n");
        	writer.write(A.mult(B).toString()+"\n");
        	writer.write("B*B =\n");
        	writer.write(B.mult(B.copy()).toString().trim());
	    }
	    catch(Exception e){
          System.out.print("BufferedWriter error.");
        }
	}

	public static void main (String[] args){
		if (args.length == 2){
			try{
				writer=new BufferedWriter(new FileWriter(args[1]));
				performOperations(args[0]);
				writer.close();
			} catch(Exception e) {
				System.out.print("BufferedWriter error.");
			}
		} else {
			System.out.print("Please input 2 arguments.");
			System.exit(1);
		}
	} 
}