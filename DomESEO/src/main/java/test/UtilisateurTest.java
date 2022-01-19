package test;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

import beans.Utilisateur;

class UtilisateurTest {
	
	private int id = 2;
	private String pswd = "test";
	private String pseudo = "le pseudo";
	private int Admin = 1;
	
	
	@Test
	void testUtilisateurIntStringStringInt() {
		Utilisateur util = new Utilisateur(id,pseudo,pswd,Admin);
		
		assertEquals(id,util.getId(),"id non correct");
		assertTrue(util.getMdp().contains(pswd),"mdp_incorect");
		assertTrue(util.getPseudo().contains(pseudo), "pseudo incorect");
		assertEquals(Admin,util.getAdmin(),"permission incorecte");
		
	}

	@Test
	void testSetId() {
		Utilisateur util = new Utilisateur();
		util.setId(id);
		assertEquals(id,util.getId(),"id non correct");
	}

	@Test
	void testSetMdp() {
		Utilisateur util = new Utilisateur();
		util.setMdp(pswd);
		assertTrue(util.getMdp().contains(pswd),"mdp_incorect");
	}

	@Test
	void testSetPermission() {
		Utilisateur util = new Utilisateur();
		util.setAdmin(Admin);
		assertEquals(Admin,util.getAdmin(),"permission incorecte");
	}

	@Test
	void testSetPseudo() {
		Utilisateur util = new Utilisateur();
		util.setPseudo(pseudo);
		assertTrue(util.getPseudo().contains(pseudo), "pseudo incorect");
	}

}