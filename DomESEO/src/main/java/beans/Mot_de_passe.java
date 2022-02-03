package beans;

import java.nio.charset.StandardCharsets;
import java.security.MessageDigest;

public class Mot_de_passe {

	private String mdp;
	
	public Mot_de_passe(String mdp) {
		this.mdp = mdp;
	}
	
	public void setMdp(String mdp) {
		this.mdp = mdp;
	}
	
	public String getMdp() {
		return this.mdp;
	}
	
	public String hashMdp() throws Exception {
		MessageDigest msg = MessageDigest.getInstance("SHA-256");
        byte[] hash = msg.digest(this.mdp.getBytes(StandardCharsets.UTF_8));
        
        StringBuilder s = new StringBuilder();
        for (byte b : hash) {
            s.append(Integer.toString((b & 0xff) + 0x100, 16).substring(1));
        }
		
		return s.toString();
	}
}
