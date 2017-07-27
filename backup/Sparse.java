import java.io.*;
import java.util.*;
import java.lang.Object;
class Sparse{

	public static void readInput(String args) throws IOException{

		int matrixA;
		int matrixB;
		int lineC=0;
		String[] token= null;

		Scanner in= new Scanner (new File(args));
		String line = in.nextLine()+" ";
		token = line.split("\\s+");
		matrixA = Integer.parseInt(token[1]);
		matrixB = Integer.parseInt(token[2]) + matrixA;
		while (in.hasNextLine()){
			line= in.nextLine()+" ";
			token= line.split("\\s+");
			lineC++;
			if (matrixA+1 >= lineC && lineC > 1){

			}
			if (matrixB+2 >= lineC && lineC > matrixA + 2){

			}
		}

	}

	public static void main (String[] args){
		if (args.length == 2){
			try{
				readInput(args[0]);
			} catch(Exception e) {
				System.out.print("BufferedWriter error.");
			}
		} else {
			System.out.print("Please input 2 arguments.");
			System.exit(1);
		}
	} 
}