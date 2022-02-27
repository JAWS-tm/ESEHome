package beans;

public class Objet {
	private int id;
	private int type_id;
	private boolean state;
	
	public Objet(int id, int type_id, int state) {
		this.id = id;
		this.type_id = type_id;
		
		if(state == 0) {
			this.state = false;
		}else {
			this.state = true;
		}
	}
	
	public void setId(int id) {
		this.id = id;
	}
	
	public void setId_type(int id) {
		this.type_id = id;
	}
	
	public void setState(int state) {
		if(state == 0) {
			this.state = false;
		}else {
			this.state = true;
		}
	}
	
	
	public int getId() {
		return this.id;
	}
	
	public int getId_type() {
		return this.type_id;
	}
	
	public boolean getState() {
		return this.state;
	}
	
	public int[] getId_Groupe(){
		int[] intArray = new int[]{ 1,2,3,4,5,6,7,8,9,10 }; 
		
		return intArray;
	}
}
