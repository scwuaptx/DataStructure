/*EightQueen Problem*/
import java.util.Stack;
import java.util.Scanner;

public class eightqueen{

	public static void main(String args[]){

	Scanner scanner = new Scanner(System.in);
	int BoardSize,row = 1, column = 0 ,Step = 0, Numberofelement = 0; //initialize the variable.

	System.out.print("How many boardsize:");
	BoardSize = scanner.nextInt();		//User Input which is the size of Board.
	if(BoardSize<4){
		System.out.println("Please enter a number >= 4");	//If user enter a number <4,print the error message.
	}else{
		System.out.printf("\n");
		Stack <Coordinate> PathStack  = new Stack<Coordinate>();	//create a stack to save the Path of queen.
		Coordinate Location[] = new Coordinate[BoardSize+1];	//create a coordinate array in order to save coordinate of queen,that is the elemnet of stack.
		for(int i = 0; i<= BoardSize;i++)
		Location[i]= new Coordinate(0,0); //initialize the coordinate array
		System.out.printf("Step %d\n",Step);	//the 0-th step
		PrinttheBoard(BoardSize,Location);
		System.out.printf("\n");
		Step++;
		PrinttheStack(Numberofelement,Location);
		System.out.printf("-------------------------------------\n");
			while(row <= BoardSize){
				column ++;
				if (!guarded(row,column,Location)){	//determine the queen whether guarded
				Location[row].SetRowandColumn(row,column); //if the queen not be guarded,then push to stack and save the coordinate to array.
				PathStack.push(Location[row]);
				Numberofelement++;	//add 1 to number of the element of stack
				System.out.printf("Step %d\n",Step);
				PrinttheBoard(BoardSize,Location);	//print the board
				System.out.printf("\n");
				PrinttheStack(Numberofelement,Location); //print all of elemnt in the stack
				System.out.printf("-------------------------------------\n");
				row ++;
				column = 0;
				Step ++;
				}
			
				while(column >= BoardSize){	//when the queen can't be put in the row,then pop stack,and change the coordinate.
					Coordinate xy =  PathStack.pop();
					Numberofelement--;
					row = xy.GetRow();
					column = xy.GetColumn();
					Location[row].SetRowandColumn(0,0); //remove queen at (row,column)
				}
			}
		}
	
	}


	public static boolean guarded(int row,int column,Coordinate[] Location){  //the function will determine whether the queen be guarded.
        int RowofQueen,ColofQueen,i=row;	//which i is the i-th queen
         while(i>1){
               RowofQueen= Location[i-1].GetRow();		//read the queen's coordinate on the board.
               ColofQueen= Location[i-1].GetColumn();
               if( (row == RowofQueen) || (column == ColofQueen) || (ColofQueen-RowofQueen)==(column-row) || (column+row) == (RowofQueen+ColofQueen))
               return true;	//determine whether the queen be guarded.
               else
               i--;
                }
                return false;
        }

	public static void PrinttheBoard(int BoardSize,Coordinate[] Location){  //the function will print the board
		int i,j;
		for(i=1;i<=BoardSize;i++){
			for(j=1;j<=BoardSize;j++){
				if(j==Location[i].GetColumn())	//if there is a queen in the coordinate, print "1" 
				System.out.print("1");
				else	
				System.out.print("0");	//if there is no queen in the coordinate ,print "0"
			}
			System.out.printf("\n");
		}
	}

	public static void PrinttheStack(int Numberofelement,Coordinate[] Location){  //the function wiil print all of the element of stack from up to bottom.
		int i;
		System.out.print("Stack<up to bottom>:");
		if(Numberofelement==0)		//if no element in stack, print "null";
			System.out.print("null\n\n");
		else{	
			for(i=Numberofelement;i>0;i--){
			Location[i].ShowCoordinate();
			if(i!=1)
			System.out.print("|");
			else
			System.out.printf("\n\n");
			}
		}		
	}

}


