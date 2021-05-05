package tables;

public class Regle {

	private byte regle_id ;
	private byte regle_operand_1 ;
	private byte regle_operateur ;
	private byte regle_operand_2 ;
	private byte regle_action_parametre ;
	private byte regle_action_value ;
	private byte parametre_id ;

	public Regle(byte regle_id, byte regle_operand_1, byte regle_operateur, byte regle_operand_2, byte regle_action_parametre, byte regle_action_value, byte parametre_id) {
	
		this.regle_id = regle_id ; 
		this.regle_operand_1 = regle_operand_1 ;
		this.regle_operateur = regle_operateur ;
		this.regle_operand_2 = regle_operand_2 ;
		this.regle_action_parametre = regle_action_parametre ;
		this.regle_action_value = regle_action_value ;
		this.parametre_id = parametre_id ;
		
	}
	
	public byte getRegel_id() {
		return regle_id;
	}
	public void setRegel_id(byte regle_id) {
		this.regle_id = regle_id;
	}
	
	public byte getRegle_operand_1() {
		return regle_operand_1;
	}
	public void setRegle_operand_1(byte regle_operand_1) {
		this.regle_operand_1 = regle_operand_1;
	}
	
	public byte getRegle_operateur() {
		return regle_operateur;
	}
	public void setRegle_operateur(byte regle_operateur) {
		this.regle_operateur = regle_operateur;
	}
	
	public byte getRgle_operand_2(){
		return regle_operand_2;
	}
	public void setRegle_operand_2(byte regle_operand_2) {
		this.regle_operand_2 = regle_operand_2;
	}
	
	public byte getRegle_action_parametre() {
		return regle_action_parametre;
	}
	public void setRegle_action_parametre(byte regle_action_parametre) {
		this.regle_action_parametre = regle_action_parametre;
	}
	
	public byte getRegle_action_value() {
		return regle_action_value;
	}
	public void setRegle_action_value(byte regle_action_value) {
		this.regle_action_value = regle_action_value;
	}
	
	public byte getParametre_id() {
		return  parametre_id;
	}
	public void setParametre_id(byte parametre_id) {
		this.parametre_id = parametre_id ;
	}
}
