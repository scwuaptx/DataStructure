/*Define the Coordinate class*/
public class Coordinate{
        private int row;
        private int column;
        public Coordinate(int row,int column){
                this.row = row;
                this.column = column;
        }

	public Coordinate(){ //if no giva number to coordinate,than the coordinate will be (0,0)
		this.row = 0;
		this.column = 0;
	}

        public int GetRow(){  //get the row 
                return row;
        }

        public int GetColumn(){	//get the column
                return column;
        }

	public void SetRowandColumn(int row,int column){ //set the coordinate
		this.row = row;
		this.column = column;
	}
		
	public void ShowCoordinate(){   //print the coordinate
		System.out.printf("(%d,%d)",row,column);
	}

}


